//
// Created by david on 1/7/2023.
//

#include "registers.h"

registers::registers()
        : _enc(ACTIVATE::NO), _a(REGISTER::PC), _b(REGISTER::PC), _c(REGISTER::PC) {
    for (unsigned short &i: reg)
        i = 0;
}

void registers::reset() {
    for (unsigned short &i: reg)
        i = 0;
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
    if (_enc == ACTIVATE::YES)
        reg[_c] = value;
}

word registers::getAValue() const {
    return reg[_a];
}

word registers::getBValue() const {
    return reg[_b];
}
