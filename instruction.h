//
// Created by pinkynyte on 1/12/23.
//

#ifndef HOMICSIM_INSTRUCTION_H
#define HOMICSIM_INSTRUCTION_H


#include "constants.h"

class instruction {
public:
    instruction();

    explicit instruction(dword value);

    void setCode(dword value);

    [[nodiscard]] dword getCode() const;


private:
    int amux;
    int cond;
    int alu;
    int sh;
    int mbr;
    int mar;
    int rd;
    int wr;
    int enc;
    int busC;
    int busB;
    int busA;
    byte address;
};


#endif //HOMICSIM_INSTRUCTION_H
