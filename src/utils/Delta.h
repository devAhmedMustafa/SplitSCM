//
// Created by Ahmed Mustafa on 8/13/2025.
//

#ifndef DELTA_H
#define DELTA_H

#include <queue>

#include "DeltaInstruction.h"

namespace Split {
    class Delta {
        std::queue<DeltaInstruction> instructions;
    public:
        std::queue<DeltaInstruction>& getInstructions() {
            return instructions;
        }
    };
}

#endif //DELTA_H
