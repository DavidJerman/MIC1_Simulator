//
// Created by david on 1/7/2023.
//

#ifndef HOMICSIM_CONSTANTS_H
#define HOMICSIM_CONSTANTS_H

typedef unsigned short word;

#define MEM_SIZE 4096
#define REG_SIZE 16
#define NO_REGISTERS 16

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

// Instruction flags enums

enum AMUX {
    A_LATCH,
    MBR
};

enum COND {
    NO_JUMP,
    N_JUMP,
    Z_JUMP,
    JUMP
};

enum ALU {
    A_PLUS_B,
    A_AND_B,
    POS_A,
    NEG_A
};

enum SH {
    NO_SHIFT,
    RIGHT_SHIFT,
    LEFT_SHIFT,
    INVALLID
};

// On/off flags

enum ACTIVATE {
    NO,
    YES
};

#endif //HOMICSIM_CONSTANTS_H
