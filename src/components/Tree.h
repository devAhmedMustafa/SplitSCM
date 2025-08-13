//
// Created by Ahmed Mustafa on 8/13/2025.
//

#ifndef TREE_H
#define TREE_H

#include <string>
#include <map>

namespace Split {

    class Tree {
        std::map<std::string, std::string> entries; // Maps file paths to their hashes
    public:
        std::byte* serialize() {
            return nullptr; // Placeholder for serialization logic
        }

        static Tree deserialize(const std::byte* data, size_t size) {
            Tree tree;
            return tree;
        }
    };

}

#endif //TREE_H
