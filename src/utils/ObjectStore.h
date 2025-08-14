//
// Created by Ahmed Mustafa on 8/12/2025.
//

#ifndef OBJECTSTORE_H
#define OBJECTSTORE_H

#include <string>

namespace Split {

    class ObjectStore {

        std::string basePath = ".split/objects";
        std::string path;

    public:

        ObjectStore(const std::string& );

        bool hasObject(const std::string& hash) const;
        std::string storeFileObject(const std::string& filePath) const;
        std::fstream* loadObject(const std::string& hash) const;
    };

}



#endif //OBJECTSTORE_H
