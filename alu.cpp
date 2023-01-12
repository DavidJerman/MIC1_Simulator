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
