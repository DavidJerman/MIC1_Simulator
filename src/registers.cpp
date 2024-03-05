//
// Created by david on 1/7/2023.
//

#include "registers.h"

registers::registers()
        : _enc(ACTIVATE::NO), _a(REGISTER::PC), _b(REGISTER::PC), _c(REGISTER::PC) {
    reset();
}

void registers::reset() {
    for (unsigned short &i: reg)
        i = 0;
    reg[REGISTER::N1] = 0xFFFF;
    reg[REGISTER::P1] = 0x0001;
    reg[REGISTER::Z] = 0x0000;
    reg[REGISTER::AMASK] = 0x0FFF;
    reg[REGISTER::SMASK] = 0x00FF;
    _a = REGISTER::PC;
    _b = REGISTER::PC;
    _c = REGISTER::PC;
    _enc = ACTIVATE::NO;
}

ACTIVATE registers::getEnc() const {
    return _enc;
}

void registers::setEnc(ACTIVATE enc) {
    _enc = enc;
}

REGISTER registers::getA() const {
    return _a;
}

void registers::setA(REGISTER a) {
    _a = a;
}

REGISTER registers::getB() const {
    return _b;
}

void registers::setB(REGISTER b) {
    _b = b;
}

REGISTER registers::getC() const {
    return _c;
}

void registers::setC(REGISTER c) {
    _c = c;
}

void registers::setValue(word value) {
    // Warning: This is a hack to prevent the user from writing to the N1, P1, Z, AMASK, and SMASK registers.
    if (_c == REGISTER::N1 || _c == REGISTER::P1 || _c == REGISTER::Z || _c == REGISTER::AMASK || _c == REGISTER::SMASK)
        return;
    if (_enc == ACTIVATE::YES)
        reg[_c] = value;
}

word registers::getAValue() const {
    return reg[_a];
}

word registers::getBValue() const {
    return reg[_b];
}

void registers::printState() {
    for (int i = 0; i < REG_SIZE; i++) {
        std::cout << "R" << i << ": " << std::hex << reg[i] << std::endl;
    }
}
