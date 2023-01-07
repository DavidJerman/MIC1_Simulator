//
// Created by david on 1/7/2023.
//

#ifndef HOMICSIM_CONSTANTS_H
#define HOMICSIM_CONSTANTS_H

typedef unsigned short word;

#define MEM_SIZE 4096
#define REG_SIZE 16

enum class IO_MODE {
    READ,
    WRITE
};

enum class IO_STATE {
    BUSY,
    READY
};

enum REGISTER {
    PC,
    AC,
    SP,
    IR,
    TIR,
    Z,
    P1,
    N1,
    AMASK,
    SMASK,
    A,
    B,
    C,
    D,
    E,
    F
};

#endif //HOMICSIM_CONSTANTS_H
