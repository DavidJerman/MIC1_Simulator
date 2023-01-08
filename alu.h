//
// Created by david on 1/8/2023.
//

#ifndef HOMICSIM_ALU_H
#define HOMICSIM_ALU_H

#include "constants.h"

class alu {
public:
    alu();

    [[nodiscard]] bool getZ() const;

    [[nodiscard]] bool getN() const;

    word addOp(word a, word b);

    word andOp(word a, word b);

    word posOp(word a);

    word negOp(word a);

private:
    bool flagZ;
    bool flagN;
};


#endif //HOMICSIM_ALU_H
