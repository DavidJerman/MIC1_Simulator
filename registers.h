//
// Created by david on 1/7/2023.
//

#ifndef HOMICSIM_REGISTERS_H
#define HOMICSIM_REGISTERS_H

#include "constants.h"

class registers {
public:
    registers();

    void setValue(word value);

    [[nodiscard]] word getAValue() const;

    [[nodiscard]] word getBValue() const;

    void reset();

    [[nodiscard]] ACTIVATE getEnc() const;

    void setEnc(ACTIVATE enc);

    [[nodiscard]] REGISTER getA() const;

    void setA(REGISTER a);

    [[nodiscard]] REGISTER getB() const;

    void setB(REGISTER b);

    [[nodiscard]] REGISTER getC() const;

    void setC(REGISTER c);

private:
    word reg[REG_SIZE]{};

    enum ACTIVATE _enc;
    enum REGISTER _a;
    enum REGISTER _b;
    enum REGISTER _c;
};

#endif //HOMICSIM_REGISTERS_H
