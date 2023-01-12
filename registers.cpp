//
// Created by david on 1/7/2023.
//

#include "registers.h"

registers::registers() {
    for (unsigned short &i: reg)
        i = 0;
}

word registers::getReg(REGISTER _reg) {
    return this->reg[_reg];
}

void registers::setReg(REGISTER _reg, word value) {
    this->reg[_reg] = value;
}

void registers::reset() {
    for (unsigned short &i: reg)
        i = 0;
}
