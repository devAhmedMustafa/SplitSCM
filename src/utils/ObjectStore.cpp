//
// Created by Ahmed Mustafa on 8/12/2025.
//

#include "ObjectStore.h"

#include <stdexcept>
#include <fstream>
#include <filesystem>

#include "Hashing.h"

namespace Split {

    ObjectStore::ObjectStore(const std::string & path) : path( "/.split/objects" + path) {
        std::filesystem::create_directories(this->path);
    }


    bool ObjectStore::hasObject(const std::string &hash) const {
        const std::string objectPath = path + "/" + hash;
        const std::ifstream file(objectPath, std::ios::binary);
        return file.good();
    }

    std::string ObjectStore::storeFileObject(const std::string &filePath) const {
        std::ifstream file(filePath, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Failed to open file: " + filePath);
        }

        std::string hash = Hashing::computeHash(filePath);
        const std::string objectPath = path + "/" + hash;

        if (hasObject(hash)) {
            return hash;
        }

        std::ofstream outFile(objectPath, std::ios::binary);
        if (!outFile) {
            throw std::runtime_error("Failed to create object file: " + objectPath);
        }

        outFile << file.rdbuf();
        outFile.close();

        return hash;
    }

    std::fstream * ObjectStore::loadObject(const std::string &hash) const {
        const std::string objectPath = path + "/" + hash;
        auto *fileStream = new std::fstream(objectPath, std::ios::in | std::ios::binary);
        if (!fileStream->is_open()) {
            delete fileStream;
            throw std::runtime_error("Failed to open object file: " + objectPath);
        }
        return fileStream;
    }
}
