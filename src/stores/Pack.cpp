//
// Created by Ahmed Mustafa on 8/15/2025.
//

#include "Pack.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <utils/DeltaCompressor.h>
#include "ObjectStore.h"

namespace Split {

    Pack::Pack(const str& rootPath) : path(rootPath + "/.split/refs/packs"), rootPath(rootPath) {

        // Ensure the directory exists
        std::filesystem::create_directories(path);

        // Load existing packs from the directory
        for (const auto &entry : std::filesystem::directory_iterator(path)) {
            if (entry.is_regular_file()) {
                str hash = entry.path().stem().string();

                str baseHash;
                std::queue<str> objectQueue;

                std::ifstream file(entry.path());
                str objectHash;

                if (!file.is_open()) {
                    throw std::runtime_error("Failed to open pack file: " + entry.path().string());
                }

                if (std::getline(file, baseHash)) {
                    if (baseHash.empty()) {
                        throw std::runtime_error("Base hash is empty in pack file: " + entry.path().string());
                    }
                } else {
                    throw std::runtime_error("Failed to read base hash from pack file: " + entry.path().string());
                }

                while (std::getline(file, objectHash)) {
                    if (!objectHash.empty()) {
                        objectQueue.push(objectHash);
                    }
                }

                packs[hash].first = baseHash;
                packs[hash].second = objectQueue;
            }
        }
    }

    std::queue<str> Pack::getPack(const str &baseHash) const {
        auto it = packs.find(baseHash);
        if (it != packs.end()) {
            return it->second.second;
        }
        return {};
    }

    void Pack::savePack(const str &hash) const {
        auto it = packs.find(hash);
        if (it == packs.end()) {
            return;
        }

        str filePath = rootPath + "/.split/refs/packs/" + hash + ".pack";
        std::ofstream file(filePath);

        if (!file.is_open()) {
            throw std::runtime_error("Failed to open pack file for writing: " + filePath);
        }

        const str &baseHashStr = it->second.first;
        file << baseHashStr << "\n";

        const std::queue<str> &objectQueue = it->second.second;
        std::queue<str> tempQueue = objectQueue;

        while (!tempQueue.empty()) {
            file << tempQueue.front() << "\n";
            tempQueue.pop();
        }

        file.close();
    }

    str Pack::getDecodedContent(const str& hash) {
        auto it = packs.find(hash);
        if (it == packs.end() || it->second.second.empty()) {
            return "\n";
        }

        const str &baseHash = it->second.first;
        const std::queue<str> &objectQueue = packs[hash].second;

        std::queue<str> tempQueue = objectQueue;

        const ObjectStore blobsObjectStore(rootPath, "/blobs");
        const ObjectStore deltasObjectStore(rootPath, "/deltas");

        DeltaCompressor compressor;

        if (!blobsObjectStore.hasObject(baseHash)) {
            throw std::runtime_error("Base object not found: " + hash);
        }

        std::ostringstream oss;
        oss << blobsObjectStore.loadObject(baseHash).rdbuf();
        str content = oss.str();

        while (!tempQueue.empty()) {
            str objectHash = tempQueue.front();
            tempQueue.pop();

            if (!deltasObjectStore.hasObject(objectHash)) {
                throw std::runtime_error("Object not found in deltas: " + objectHash);
            }

            std::ostringstream deltaStream;
            deltaStream << deltasObjectStore.loadObject(objectHash).rdbuf();
            str deltaContent = deltaStream.str();

            try {
                content = compressor.decode(content, deltaContent);
            } catch (const std::runtime_error &e) {
                throw std::runtime_error("Failed to decode delta for object " + objectHash + ": " + e.what());
            }
        }

        return content;
    }

    str Pack::encodeDelta(const str& baseBytes, const str& targetBytes, const str& baseHash, const str& targetHash) {
        DeltaCompressor compressor;
        auto delta = compressor.encode(baseBytes, targetBytes);
        if (delta.empty()) {
            throw std::runtime_error("Failed to encode delta.");
        }

        // Save the delta to the deltas object store
        ObjectStore deltasObjectStore(rootPath, "/deltas");
        str deltaHash = deltasObjectStore.storeBytesObject(delta);
        if (deltaHash.empty()) {
            throw std::runtime_error("Failed to store delta object.");
        }

        // Add the delta to the pack
        const auto packIt = packs.find(targetHash);
        if (packIt != packs.end()) {
            packIt->second.second.push(deltaHash);
        } else {
            packs[targetHash].first = baseHash;
            std::queue<str> newQueue;
            newQueue.push(deltaHash);
            packs[targetHash].second = newQueue;
        }

        savePack(targetHash);
        return deltaHash;
    }

}
