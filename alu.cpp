//
// Created by david on 1/8/2023.
//

#include "alu.h"

alu::alu() {

}

bool alu::getZ() const {
    return flagZ;
}

bool alu::getN() const {
    return flagN;
}

word alu::addOp(word a, word b) {
    word result = a + b;
    flagZ = result == 0;
    flagN = (result & 0x8000) != 0;
    return result;
}

word alu::andOp(word a, word b) {
    word result = a & b;
    flagZ = result == 0;
    flagN = (result & 0x8000) != 0;
    return result;
}

word alu::posOp(word a) {
    flagZ = a == 0;
    flagN = (a & 0x8000) != 0;
    return a;
}

word alu::negOp(word a) {
    word result = ~a; // One's complement - TODO: have to check if this is correct
    flagZ = result == 0;
    flagN = (result & 0x8000) != 0;
    return result;
}

void alu::setA(word value) {
    A = value;
}

void alu::setB(word value) {
    B = value;
}

void alu::setOp(enum ALU newOp) {
    op = newOp;
}

word alu::wordOut() {
    switch (op) {
        case ALU::A_PLUS_B:
            return addOp(A, B);
        case ALU::A_AND_B:
            return andOp(A, B);
        case ALU::POS_A:
            return posOp(A);
        case ALU::NEG_A:
            return negOp(A);
        default:
            return 0;
    }
}
