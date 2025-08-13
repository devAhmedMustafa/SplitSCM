//
// Created by Ahmed Mustafa on 8/13/2025.
//

#ifndef INDEX_H
#define INDEX_H

#include <string>
#include <map>

namespace Split {

    class Index {

        std::string path;
        std::map<std::string, std::string> entries; // Maps file paths to their base version hashes

    public:
        void stageFile(const std::string& filepath, const std::string& baseVersionHash);
        std::map<std::string, std::string> getStagedFiles() const;
        void removeStagedFile(const std::string& filepath);

    };

}

#endif //INDEX_H
