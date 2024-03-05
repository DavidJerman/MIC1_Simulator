//
// Created by david on 1/7/2023.
//

#ifndef HOMICSIM_REGISTERS_H
#define HOMICSIM_REGISTERS_H

#include "constants.h"
#include <string>
#include <iostream>

class registers {
public:
    registers();

    void setValue(word value);

    word getAValue() const;

    word getBValue() const;

    void reset();

    ACTIVATE getEnc() const;

    void setEnc(ACTIVATE enc);

    REGISTER getA() const;

    void setA(REGISTER a);

    REGISTER getB() const;

    void setB(REGISTER b);

    REGISTER getC() const;

    void setC(REGISTER c);

    // Visualization
    void printState();

private:
    word reg[REG_SIZE]{};

    enum ACTIVATE _enc;
    enum REGISTER _a;
    enum REGISTER _b;
    enum REGISTER _c;
};

#endif //HOMICSIM_REGISTERS_H
