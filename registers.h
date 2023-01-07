//
// Created by david on 1/7/2023.
//

#ifndef HOMICSIM_REGISTERS_H
#define HOMICSIM_REGISTERS_H

#include "constants.h"

class registers {
public:
    registers();

    word getReg(REGISTER _reg);

private:
    word reg[REG_SIZE]{};
};



#endif //HOMICSIM_REGISTERS_H
