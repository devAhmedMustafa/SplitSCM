
#include "Index.h"

#include <utility>
#include <fstream>
#include <filesystem>

#include "../utils/Hashing.h"

namespace Split {

    Index::Index(std::string rootPath) : path(std::move(rootPath) + "/.split/index") {
        std::fstream fs;
        fs.open(this->path, std::ios::in | std::ios::binary);

        if (!fs.is_open()) {
            fs.open(this->path, std::ios::out | std::ios::binary);
            fs.close();
        } else {
            IndexEntry entry;
            while (fs.read(reinterpret_cast<char*>(&entry), sizeof(IndexEntry))) {
                entries[entry.filePath] = entry;
            }
            fs.close();
        }
    }

    void Index::stageFile(const std::string &filepath) {
        IndexEntry entry = {
            filepath, "", 0, 0, 0, false
        };

        std::fstream originalFs(filepath, std::ios::in | std::ios::binary);
        if (originalFs.is_open()) {
            originalFs.seekg(0, std::ios::end);
            entry.size = originalFs.tellg();
            originalFs.seekg(0, std::ios::beg);
            entry.mtime = std::filesystem::last_write_time(filepath).time_since_epoch().count();
            originalFs.close();
        }

        const std::string blobHash = Hashing::computeHash(filepath);
        entry.blobHash = blobHash;

        entries[filepath] = entry;

        // Write the updated index to disk
        std::fstream fs(this->path, std::ios::out | std::ios::binary);

        for (const auto &pair : entries) {
            const IndexEntry &e = pair.second;

            // Serialize filePath
            uint32_t pathLen = e.filePath.size();
            fs.write(reinterpret_cast<const char*>(&pathLen), sizeof(pathLen));
            fs.write(e.filePath.data(), pathLen);

            // Serialize blobHash
            uint32_t hashLen = e.blobHash.size();
            fs.write(reinterpret_cast<const char*>(&hashLen), sizeof(hashLen));
            fs.write(e.blobHash.data(), hashLen);

            // Serialize other fields
            fs.write(reinterpret_cast<const char*>(&e.mode), sizeof(e.mode));
            fs.write(reinterpret_cast<const char*>(&e.size), sizeof(e.size));
            fs.write(reinterpret_cast<const char*>(&e.mtime), sizeof(e.mtime));
            fs.write(reinterpret_cast<const char*>(&e.isDeleted), sizeof(e.isDeleted));
        }

        fs.close();
    }




}
