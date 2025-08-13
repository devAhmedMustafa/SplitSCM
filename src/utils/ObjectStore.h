//
// Created by Ahmed Mustafa on 8/12/2025.
//

#ifndef OBJECTSTORE_H
#define OBJECTSTORE_H

#include <string>

namespace Split {

    class ObjectStore {

        std::string path;
    public:
        bool hasObject(const std::string& hash) const;
        std::string storeObject(const std::byte[], size_t);
        std::byte* loadObject(const std::string& hash, size_t& size) const;
        std::string findBaseVersion(const std::string& filepath) const;
    };

}



#endif //OBJECTSTORE_H
