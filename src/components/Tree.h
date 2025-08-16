//
// Created by Ahmed Mustafa on 8/13/2025.
//

#ifndef TREE_H
#define TREE_H

#include <string>
#include <map>
#include <utility>

#include "core/Alias.h"

namespace Split {

    class Tree {
        std::map<std::string, std::string> entries; // Maps file paths to their hashes
    public:
        explicit Tree(std::map<std::string, std::string> entries = {}) : entries(std::move(entries)) {}
        str serialize() const;
        str getEntry(const str& file) { return this->entries[file]; }
        static Tree deserialize(std::istream& in);
    };

}

#endif //TREE_H
