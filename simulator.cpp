//
// Created by david on 1/8/2023.
//

#include "simulator.h"

simulator::simulator() {
    mem = memory();
    reg = registers();
}

void simulator::next() {
    // Will execute the next clock cycle

}

void simulator::test_memory() {
    std::cout << "===> Testing memory <===" << std::endl;
    // Read/write from memory
    mem.setMar(0); mem.setMbr(0x1234); mem.write();
    mem.write();
    mem.setMar(0); mem.read();
    mem.read();
    auto mbr = mem.getMbr();
    std::cout << "mbr = " << getHexStr(mbr) << std::endl;
    // Another test_memory
    mem.setMar(1); mem.read();
    mem.read();
    mbr = mem.getMbr();
    std::cout << "mbr = " << getHexStr(mbr) << std::endl;
    // Error test_memory 1
    try {
        mem.setMar(0x1000); mem.read();
        mem.read();
    } catch (memory_out_of_bounds_exception &e) {
        std::cout << "Caught memory_out_of_bounds_exception" << std::endl;
    }
    // Error test_memory 2
    try {
        mem.setMar(0); mem.setMbr(0x1234); mem.write();
        mem.setMar(0); mem.setMbr(0x1234); mem.write();
    } catch (memory_bus_exception &e) {
        std::cout << "Caught memory_bus_exception" << std::endl;
    }
    // Error test_memory 3
    try {
        mem.setMar(0); mem.setMbr(0x1234); mem.write();
        mem.read();
    } catch (memory_bus_exception &e) {
        std::cout << "Caught memory_bus_exception" << std::endl;
    }
}

void simulator::printHex(word value) {
    std::cout << getHexStr(value) << std::endl;
}

std::string simulator::getHexStr(word value) {
    std::stringstream ss;
    ss << "0x" << std::hex << value;
    return ss.str();
}
