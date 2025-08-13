//
// Created by Ahmed Mustafa on 8/13/2025.
//

#ifndef DELTAINSTRUCTION_H
#define DELTAINSTRUCTION_H

#include <string>

namespace Split {

    struct DeltaInstruction {
        std::string type;
        uint64_t offset;
        uint64_t length;
        std::byte* data;
    };

}

#endif //DELTAINSTRUCTION_H
