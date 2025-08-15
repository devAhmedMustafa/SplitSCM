//
// Created by Ahmed Mustafa on 8/15/2025.
//

#include "Pack.h"
#include <filesystem>
#include <fstream>
#include <utils/DeltaCompressor.h>
#include <utils/ObjectStore.h>

namespace Split {

    Pack::Pack(const std::string& rootPath) : path(rootPath + "/.split/refs/packs"), rootPath(rootPath) {

        // Ensure the directory exists
        std::filesystem::create_directories(path);

        // Load existing packs from the directory
        for (const auto &entry : std::filesystem::directory_iterator(path)) {
            if (entry.is_regular_file()) {
                std::string baseHash = entry.path().stem().string();
                std::queue<std::string> objectQueue;

                std::ifstream file(entry.path());
                std::string objectHash;
                while (std::getline(file, objectHash)) {
                    if (!objectHash.empty()) {
                        objectQueue.push(objectHash);
                    }
                }
                packs[baseHash] = objectQueue;
            }
        }
    }

    std::queue<std::string> Pack::getPack(const std::string &baseHash) const {
        auto it = packs.find(baseHash);
        if (it != packs.end()) {
            return it->second;
        }
        return {};
    }

    void Pack::savePack(const std::string &baseHash) const {
        auto it = packs.find(baseHash);
        if (it == packs.end()) {
            return;
        }

        std::string filePath = rootPath + "/.split/refs/packs/" + baseHash + ".pack";
        std::ofstream file(filePath);

        if (!file.is_open()) {
            throw std::runtime_error("Failed to open pack file for writing: " + filePath);
        }

        const std::queue<std::string> &objectQueue = it->second;
        std::queue<std::string> tempQueue = objectQueue;

        while (!tempQueue.empty()) {
            file << tempQueue.front() << "\n";
            tempQueue.pop();
        }

        file.close();
    }

    std::string Pack::getDecodedContent(const std::string& baseHash) const {
        auto it = packs.find(baseHash);
        if (it == packs.end() || it->second.empty()) {
            return {};
        }

        const std::queue<std::string> &objectQueue = it->second;
        std::queue<std::string> tempQueue = objectQueue;

        const ObjectStore blobsObjectStore(rootPath, "/blobs");
        const ObjectStore deltasObjectStore(rootPath, "/deltas");
        DeltaCompressor compressor;

        if (!blobsObjectStore.hasObject(baseHash)) {
            throw std::runtime_error("Base object not found: " + baseHash);
        }

        std::ostringstream oss;
        oss << blobsObjectStore.loadObject(baseHash).rdbuf();
        std::string content = oss.str();

        while (!tempQueue.empty()) {
            std::string objectHash = tempQueue.front();
            tempQueue.pop();

            if (!deltasObjectStore.hasObject(objectHash)) {
                throw std::runtime_error("Object not found in deltas: " + objectHash);
            }
            std::ostringstream deltaStream;
            deltaStream << deltasObjectStore.loadObject(objectHash).rdbuf();
            std::string deltaContent = deltaStream.str();
            try {
                content = compressor.decode(content, deltaContent);
            } catch (const std::runtime_error &e) {
                throw std::runtime_error("Failed to decode delta for object " + objectHash + ": " + e.what());
            }
        }

        return content;
    }

    std::string Pack::encodeDelta(const std::string& baseBytes, const std::string& targetBytes, const std::string& baseHash) {
        DeltaCompressor compressor;
        auto delta = compressor.encode(baseBytes, targetBytes);
        if (delta.empty()) {
            throw std::runtime_error("Failed to encode delta.");
        }

        // Save the delta to the deltas object store
        ObjectStore deltasObjectStore(rootPath, "/deltas");
        std::string deltaHash = deltasObjectStore.storeBytesObject(delta);
        if (deltaHash.empty()) {
            throw std::runtime_error("Failed to store delta object.");
        }

        // Add the delta to the pack
        const auto packIt = packs.find(baseHash);
        if (packIt != packs.end()) {
            packIt->second.push(deltaHash);
        } else {
            std::queue<std::string> newQueue;
            newQueue.push(deltaHash);
            packs[baseHash] = newQueue;
        }

        savePack(baseHash);
        return deltaHash;
    }

}
