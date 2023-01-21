//
// Created by david on 1/7/2023.
//

#ifndef HOMICSIM_CONSTANTS_H
#define HOMICSIM_CONSTANTS_H

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int dword;

#define MEM_SIZE 4096
#define REG_SIZE 16
#define NO_REGISTERS 16

// Instruction bit shifts
#define ADDRESS_SH 0
#define BUS_A_SH 8
#define BUS_B_SH 12
#define BUS_C_SH 16
#define ENC_SH 20
#define WR_SH 21
#define RD_SH 22
#define MAR_SH 23
#define MBR_SH 24
#define SH_SH 25
#define ALU_SH 27
#define COND_SH 29
#define AMUX_SH 31

// Instruction masks
#define ADDRESS_MASK 0xFF
#define BUS_A_MASK 0xF
#define BUS_B_MASK 0xF
#define BUS_C_MASK 0xF
#define ENC_MASK 0x1
#define WR_MASK 0x1
#define RD_MASK 0x1
#define MAR_MASK 0x1
#define MBR_MASK 0x1
#define SH_MASK 0x3
#define ALU_MASK 0x3
#define COND_MASK 0x3
#define AMUX_MASK 0x1

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
    F,
    MAR,
    MBR,
    ALU,
    INVALID
};

// Instruction flags enums

enum AMUX {
    A_LATCH,
    MBR_LATCH
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

// Markers for instruction parts
enum MARK {
    MAMUX,
    MCOND,
    MALU,
    MSH,
    MMBR,
    MMAR,
    MRD,
    MWR,
    MENC,
    MC,
    MB,
    MA,
    MADDR
};

#endif //HOMICSIM_CONSTANTS_H
