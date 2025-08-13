//
// Created by Ahmed Mustafa on 8/13/2025.
//

#ifndef DELTACOMPRESSOR_H
#define DELTACOMPRESSOR_H

#include <string>
#include "Delta.h"

namespace Split {
    class DeltaCompressor {

    public:
        Delta compress(const std::string& baseFile, const std::string& modifiedFile);

        void decompress(const Delta& delta, const std::string& baseFile, std::string& outputFile) const;

    };
}

#endif //DELTACOMPRESSOR_H
