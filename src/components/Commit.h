//
// Created by Ahmed Mustafa on 8/13/2025.
//

#ifndef COMMIT_H
#define COMMIT_H

#include <string>
#include <vector>

namespace Split {

    class Commit {

        std::string treeHash;
        std::string parentHash;
        std::string message;
        std::string author;
        std::string timestamp;

    public:

        std::byte* serialize() {
            // Placeholder for serialization logic
            return nullptr;
        }

        static Commit deserialize(const std::byte* data, size_t size) {
            Commit commit;
            // Placeholder for deserialization logic
            return commit;
        }

    };

}

#endif //COMMIT_H
