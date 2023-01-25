//
// Created by david on 1/7/2023.
//

#include <cstring>
#include "memory.h"

memory::memory() {
    _mar = 0;
    _mbr = 0;
}

memory::~memory() = default;

void memory::read() {
    if (_ioState == IO_STATE::BUSY) {
        if (_ioMode != IO_MODE::READ) {
            throw memory_bus_exception();
        }
        if (_mar >= MEM_SIZE) {
            throw memory_out_of_bounds_exception();
        }
        _mbr = read_word(_mar);
        _ioState = IO_STATE::READY;
    } else {
        _ioState = IO_STATE::BUSY;
        _ioMode = IO_MODE::READ;
    }
}

void memory::write() {
    if (_ioState == IO_STATE::BUSY) {
        if (_ioMode != IO_MODE::WRITE) {
            throw memory_bus_exception();
        }
        if (_mar >= MEM_SIZE) {
            throw memory_out_of_bounds_exception();
        }
        write_word(_mar, _mbr);
        _ioState = IO_STATE::READY;
    } else {
        _ioState = IO_STATE::BUSY;
        _ioMode = IO_MODE::WRITE;
    }
}

word memory::read_word(word address) {
    if (address >= MEM_SIZE) {
        throw memory_out_of_bounds_exception();
    }
    return _mem[address];
}

void memory::write_word(word address, word value) {
    if (address >= MEM_SIZE) {
        throw memory_out_of_bounds_exception();
    }
    _mem[address] = value;
}

word memory::getMbr() const {
    return _mbr;
}

void memory::setMbr(word mbr) {
    this->_mbr = mbr;
}

void memory::setMar(word mar) {
    if (_ioState == IO_STATE::BUSY) {
        throw memory_bus_exception();
    }
    this->_mar = mar;
}

void memory::reset() {
    memset(_mem, 0, sizeof(_mem));
    _mar = 0;
    _mbr = 0;
    _ioState = IO_STATE::READY;
    _ioMode = IO_MODE::READ;
}

ACTIVATE memory::getSetMar() const {
    return _setMar;
}

void memory::setSetMar(ACTIVATE setMar) {
    _setMar = setMar;
}

ACTIVATE memory::getSetMbr() const {
    return _setMbr;
}

void memory::setSetMbr(ACTIVATE setMbr) {
    _setMbr = setMbr;
}

ACTIVATE memory::getRead() const {
    return _read;
}

void memory::setRd(ACTIVATE read) {
    _read = read;
}

ACTIVATE memory::getWrite() const {
    return _write;
}

void memory::setWr(ACTIVATE write) {
    _write = write;
}
