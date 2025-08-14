//
// Created by Ahmed Mustafa on 8/13/2025.
//

#ifndef DELTACOMPRESSOR_H
#define DELTACOMPRESSOR_H

#include <string>

namespace Split {
    class DeltaCompressor {

    public:
        static std::string encode(const std::string& , const std::string& );
        static std::string decode( const std::string& , std::string&);

    };
}

#endif //DELTACOMPRESSOR_H
