//
// Created by Ahmed Mustafa on 8/15/2025.
//

#ifndef PACK_H
#define PACK_H

#include <map>
#include <queue>
#include <string>

#include "core/Alias.h"

namespace Split {

    class Pack {

        std::string rootPath;
        std::string path;
        std::map<str, std::pair<str, std::queue<str>>> packs;

    public:

        Pack(const str& rootPath);
        std::queue<str> getPack(const str &baseHash) const;
        void savePack(const str &hash) const;
        str getDecodedContent(const str&);
        str encodeDelta(const str& baseBytes, const str& targetBytes, const str& baseHash, const str& targetHash);
    };

}



#endif //PACK_H
