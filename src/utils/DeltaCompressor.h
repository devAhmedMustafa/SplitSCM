//
// Created by Ahmed Mustafa on 8/13/2025.
//

#ifndef DELTACOMPRESSOR_H
#define DELTACOMPRESSOR_H

#include <string>

namespace Split {
    class DeltaCompressor {

    public:
        std::string encode(const std::string& , const std::string& );
        std::string decode( const std::string& , std::string&);
    };
}

#endif //DELTACOMPRESSOR_H
