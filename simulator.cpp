//
// Created by david on 1/8/2023.
//

#include "simulator.h"

simulator::simulator() {
    _memory = memory();
    _registers = registers();
}

void simulator::next() {
    // Will execute the next clock cycle

}

void simulator::test_memory() {
    std::cout << "===> Testing memory <===" << std::endl;
    // Read/write from memory
    _memory.setMar(0); _memory.setMbr(0x1234); _memory.write();
    _memory.write();
    _memory.setMar(0); _memory.read();
    _memory.read();
    auto mbr = _memory.getMbr();
    std::cout << "mbr = " << getHexStr(mbr) << std::endl;
    // Another test_memory
    _memory.setMar(1); _memory.read();
    _memory.read();
    mbr = _memory.getMbr();
    std::cout << "mbr = " << getHexStr(mbr) << std::endl;
    // Error test_memory 1
    try {
        _memory.setMar(0x1000); _memory.read();
        _memory.read();
    } catch (memory_out_of_bounds_exception &e) {
        std::cout << "Caught memory_out_of_bounds_exception" << std::endl;
    }
    // Error test_memory 2
    try {
        _memory.setMar(0); _memory.setMbr(0x1234); _memory.write();
        _memory.setMar(0); _memory.setMbr(0x1234); _memory.write();
    } catch (memory_bus_exception &e) {
        std::cout << "Caught memory_bus_exception" << std::endl;
    }
    // Error test_memory 3
    try {
        _memory.setMar(0); _memory.setMbr(0x1234); _memory.write();
        _memory.read();
    } catch (memory_bus_exception &e) {
        std::cout << "Caught memory_bus_exception" << std::endl;
    }
}

void simulator::test_registers() {
    std::cout << "===> Testing registers <===" << std::endl;
    // Read/write from registers
    for (unsigned int i = 0; i < NO_REGISTERS; i++) {
        auto value = (word) 0x1234 + i;
        _registers.setReg(static_cast<REGISTER>(i), value);
        auto retValue = _registers.getReg(static_cast<REGISTER>(i));
        std::cout << "Register " << i << ": " << getHexStr(value) << " == " << getHexStr(retValue) << " -> "
        << (value == retValue ? "PASS" : "FAIL") << std::endl;
    }
}

void simulator::test_alu() {
    std::cout << "===> Testing ALU <===" << std::endl;
    // Test ALU
    // TODO
    // Add
    word a = (word) 0b1100100010011011;
    word b = (word) 0b1010100010011011;
    word opSum = _alu.addOp(a, b);
    word opCompSum = a + b;
    std::cout << "Add: " << getHexStr(a) << " + " << getHexStr(b) << " = " << getHexStr(opCompSum) << " == "
    << getHexStr(opSum) << " -> " << (opSum == opCompSum ? "PASS" : "FAIL") << std::endl;
    // And
    word opAnd = _alu.andOp(a, b);
    word opCompAnd = a & b;
    std::cout << "And: " << getHexStr(a) << " & " << getHexStr(b) << " = " << getHexStr(opCompAnd) << " == "
    << getHexStr(opAnd) << " -> " << (opAnd == opCompAnd ? "PASS" : "FAIL") << std::endl;
    // A
    word posOp = _alu.posOp(a);
    std::cout << "Pos: " << getHexStr(a) << " == " << getHexStr(posOp) << " -> " << (posOp == a ? "PASS" : "FAIL")
    << std::endl;
    // Not A
    word negOp = _alu.negOp(a);
    word negComp = ~a;
    std::cout << "Neg: " << getHexStr(negComp) << " == " << getHexStr(negOp) << " -> " << (negComp == negOp ? "PASS" : "FAIL")
    << std::endl;
    // Zero flag
    _alu.posOp(0);
    std::cout << "Zero flag -> " << (_alu.getZ() ? "PASS" : "FAIL") << std::endl;
    _alu.posOp(1);
    std::cout << "Zero flag -> " << (!_alu.getZ() ? "PASS" : "FAIL") << std::endl;
    // Negative flag
    _alu.posOp(0);
    std::cout << "Negative flag -> " << (!_alu.getN() ? "PASS" : "FAIL") << std::endl;
    _alu.posOp(-1);
    std::cout << "Negative flag -> " << (_alu.getN() ? "PASS" : "FAIL") << std::endl;
}

void simulator::printHex(word value) {
    std::cout << getHexStr(value) << std::endl;
}

std::string simulator::getHexStr(word value) {
    std::stringstream ss;
    ss << "0x" << std::uppercase << std::hex << value;
    return ss.str();
}

void simulator::run() {

}

void simulator::reset() {
    _memory.reset();
    _registers.reset();
}

void simulator::run_tests() {
    test_memory();
    test_registers();
    test_alu();
}

void simulator::parse(const std::string& input) {

}
