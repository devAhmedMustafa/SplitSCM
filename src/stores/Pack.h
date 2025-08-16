//
// Created by Ahmed Mustafa on 8/15/2025.
//

#ifndef PACK_H
#define PACK_H

#include <map>
#include <queue>
#include <string>

namespace Split {

    class Pack {

        std::string rootPath;
        std::string path;
        std::map<std::string, std::queue<std::string>> packs;

    public:

        Pack(const std::string& rootPath);
        std::queue<std::string> getPack(const std::string &baseHash) const;
        void savePack(const std::string &baseHash) const;
        std::string getDecodedContent(const std::string&);
        std::string encodeDelta(const std::string& baseBytes, const std::string& targetBytes, const std::string& baseHash);
    };

}



#endif //PACK_H
