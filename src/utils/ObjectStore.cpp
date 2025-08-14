//
// Created by Ahmed Mustafa on 8/12/2025.
//

#include "ObjectStore.h"

#include <stdexcept>

namespace Split {
    bool ObjectStore::hasObject(const std::string &hash) const {
        throw std::logic_error("Not implemented yet");
    }

    std::string ObjectStore::storeObject(const std::byte[], size_t) {
        throw std::logic_error("Not implemented yet");
    }

    std::byte * ObjectStore::loadObject(const std::string &hash, size_t &size) const {
        throw std::logic_error("Not implemented yet");
    }

    std::string ObjectStore::findBaseVersion(const std::string &filepath) const {
        throw std::logic_error("Not implemented yet");
    }
}
