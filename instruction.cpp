//
// Created by pinkynyte on 1/12/23.
//

#include "instruction.h"

instruction::instruction() {
    amux = 0;
    cond = 0;
    alu = 0;
    sh = 0;
    mbr = 0;
    mar = 0;
    rd = 0;
    wr = 0;
    enc = 0;
    busC = 0;
    busB = 0;
    busA = 0;
    address = 0;
}

instruction::instruction(dword value) {
    auto cast = (int) value;
    address = cast & 0xFF;
    busA = (cast >> 8) & 0XF;
    busB = (cast >> 12) & 0XF;
    busC = (cast >> 16) & 0XF;
    enc = (cast >> 20) & 0X1;
    wr = (cast >> 21) & 0X1;
    rd = (cast >> 22) & 0X1;
    mar = (cast >> 23) & 0X1;
    mbr = (cast >> 24) & 0X1;
    sh = (cast >> 25) & 0X3;
    alu = (cast >> 27) & 0X3;
    cond = (cast >> 29) & 0X3;
    amux = (cast >> 31) & 0X1;
}

void instruction::setCode(dword value) {
    auto cast = (int) value;
    address = cast & 0xFF;
    busA = (cast >> 8) & 0XF;
    busB = (cast >> 12) & 0XF;
    busC = (cast >> 16) & 0XF;
    enc = (cast >> 20) & 0X1;
    wr = (cast >> 21) & 0X1;
    rd = (cast >> 22) & 0X1;
    mar = (cast >> 23) & 0X1;
    mbr = (cast >> 24) & 0X1;
    sh = (cast >> 25) & 0X3;
    alu = (cast >> 27) & 0X3;
    cond = (cast >> 29) & 0X3;
    amux = (cast >> 31) & 0X1;
}

dword instruction::getCode() const {
    return (dword) (amux << 31 | cond << 29 | alu << 27 | sh << 25 | mbr << 24 | mar << 23 | rd << 22 | wr << 21 |
                    enc << 20 | busC << 16 | busB << 12 | busA << 8 | address);
}
