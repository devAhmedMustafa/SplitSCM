//
// Created by Ahmed Mustafa on 8/16/2025.
//


#include "Tree.h"
#include <fstream>

namespace Split {

    str Tree::serialize() const {
        std::string result;
        for (const auto& entry : entries) {
            result += entry.first + ':' + entry.second + '\n';
        }
        return result;
    }

    Tree Tree::deserialize(std::istream& in) {
        Tree tree;
        std::string line;
        while (std::getline(in, line)) {
            size_t pos = line.find(':');
            if (pos != std::string::npos) {
                std::string path = line.substr(0, pos);
                std::string hash = line.substr(pos + 1);
                tree.entries[path] = hash;
            }
        }
        return tree;
    }

}