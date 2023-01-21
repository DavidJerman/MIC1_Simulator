//
// Created by david on 1/7/2023.
//

#include <cstring>
#include "memory.h"

memory::memory() {
    mar = 0;
    mbr = 0;
}

memory::~memory() = default;

void memory::read() {
    if (io_state == IO_STATE::BUSY) {
        if (io_mode != IO_MODE::READ) {
            throw memory_bus_exception();
        }
        if (mar >= MEM_SIZE) {
            throw memory_out_of_bounds_exception();
        }
        mbr = read_word(mar);
        io_state = IO_STATE::READY;
    } else {
        io_state = IO_STATE::BUSY;
        io_mode = IO_MODE::READ;
    }
}

void memory::write() {
    if (io_state == IO_STATE::BUSY) {
        if (io_mode != IO_MODE::WRITE) {
            throw memory_bus_exception();
        }
        if (mar >= MEM_SIZE) {
            throw memory_out_of_bounds_exception();
        }
        write_word(mar, mbr);
        io_state = IO_STATE::READY;
    } else {
        io_state = IO_STATE::BUSY;
        io_mode = IO_MODE::WRITE;
    }
}

word memory::read_word(word address) {
    if (address >= MEM_SIZE) {
        throw memory_out_of_bounds_exception();
    }
    return mem[address];
}

void memory::write_word(word address, word value) {
    if (address >= MEM_SIZE) {
        throw memory_out_of_bounds_exception();
    }
    mem[address] = value;
}

word memory::getMbr() const {
    return mbr;
}

void memory::setMbr(word _mbr) {
    this->mbr = _mbr;
}

void memory::setMar(word _mar) {
    if (io_state == IO_STATE::BUSY) {
        throw memory_bus_exception();
    }
    this->mar = _mar;
}

void memory::reset() {
    memset(mem, 0, sizeof(mem));
    mar = 0;
    mbr = 0;
    io_state = IO_STATE::READY;
    io_mode = IO_MODE::READ;
}
