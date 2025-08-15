//
// Created by Ahmed Mustafa on 8/13/2025.
//

#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <string>

#include "CommitHistory.h"
#include "Index.h"
#include "../Utils/ObjectStore.h"

namespace Split {
    class Repository {

        std::string name;
        std::string rootPath;
        Index index;
        CommitHistory history;

    public:
        Repository(std::string  name, const std::string& rootPath);

        void init() const;
        void add(const std::string& filepath);
        void commit(const std::string& message, const std::string& author);
        void checkout(const std::string& commitHash);

    };
}

#endif //REPOSITORY_H
