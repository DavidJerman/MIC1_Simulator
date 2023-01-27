//
// Created by david on 1/8/2023.
//

#include "simulator.h"

simulator::simulator() {
    _memory = memory();
    _registers = registers();
    _alu = alu();
    _amux = amux();
    _shifter = shifter();
}

bool simulator::next() {
    // Will execute the next clock cycle
    switch (subCycle) {
        case 0:
        {
            subCycle++;

            if (_mpc >= _instructions.size()) {
                return false;
            }
            _currentInstruction = _instructions[_mpc];

            // First cycle sets all components' properties according to the current instruction
            _amux.set(_currentInstruction.getAmux());
            _alu.setOp(_currentInstruction.getAlu());
            // TODO: connect shifter to ALU and AMUX to ALU
            _shifter.set(_currentInstruction.getSh());
            _memory.setSetMar(_currentInstruction.getMar());
            _memory.setSetMbr(_currentInstruction.getMbr());
            _memory.setRd(_currentInstruction.getRd());
            _memory.setWr(_currentInstruction.getWr());
            _registers.setEnc(_currentInstruction.getEnc());
            _registers.setA(_currentInstruction.getBusA());
            _registers.setB(_currentInstruction.getBusB());
            _registers.setC(_currentInstruction.getBusC());
            if (_currentInstruction.getCond() != COND::NO_JUMP)
                jmp.address = _currentInstruction.getAddress();
            jmp.cond = _currentInstruction.getCond();
            break;
        }
        case 1:
        {
            subCycle++;

            // Latches are simulated via this cycle - there is no independent latch component

            // Amux
            _amux.setA(_registers.getAValue());
            _amux.setMBR(_memory.getMbr());

            // Alu
            _alu.setA(_amux.wordOut());
            _alu.setB(_registers.getBValue());

            // Shifter
            _shifter.wordIn(_alu.wordOut());

            // Memory
            _memory.setMbr(_shifter.wordOut());
            _memory.setMar(_registers.getBValue());

            break;
        }
        case 2:
        {
            subCycle++;

            // Memory - read/write is handled internally
            _memory.read();
            _memory.write();

            break;
        }
        case 3:
        {
            subCycle = 0;
            cycle++;

            // Registers
            _registers.setValue(_shifter.wordOut());

            // Jump if necessary
            switch (jmp.cond) {
                case COND::JUMP:
                    _mpc = jmp.address;
                    break;
                case COND::Z_JUMP:
                    if (_alu.getZ())
                        _mpc = jmp.address;
                    else
                        _mpc++;
                    break;
                case COND::N_JUMP:
                    if (_alu.getN())
                        _mpc = jmp.address;
                    else
                        _mpc++;
                    break;
                default:
                    _mpc++;
                    break;
            }

            break;
        }
        default:
            break;
    }
    return true;
}

void simulator::test_memory() {
    std::cout << "===> Testing memory <===" << std::endl;
    // Read/write from memory
    _memory.setMar(0); _memory.setMbr(0x1234); _memory.write();
    _memory.write();
    _memory.setMar(0); _memory.read();
    _memory.read();
    auto mbr = _memory.getMbr();
    std::cout << "_mbr = " << getHexStr(mbr) << std::endl;
    // Another test_memory
    _memory.setMar(1); _memory.read();
    _memory.read();
    mbr = _memory.getMbr();
    std::cout << "_mbr = " << getHexStr(mbr) << std::endl;
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
    // TODO: Rewrite these tests
//    for (unsigned int i = 0; i < NO_REGISTERS; i++) {
//        auto value = (word) 0x1234 + i;
//        _registers.setReg(static_cast<REGISTER>(i), value);
//        auto retValue = _registers.getReg(static_cast<REGISTER>(i));
//        std::cout << "Register " << i << ": " << getHexStr(value) << " == " << getHexStr(retValue) << " -> "
//        << (value == retValue ? "PASS" : "FAIL") << std::endl;
//    }
}

void simulator::test_alu() {
    std::cout << "===> Testing ALU <===" << std::endl;
    // Test ALU
    // TODO: Rewrite these tests
    // Add
//    word a = (word) 0b1100100010011011;
//    word b = (word) 0b1010100010011011;
//    word opSum = _alu.addOp(a, b);
//    word opCompSum = a + b;
//    std::cout << "Add: " << getHexStr(a) << " + " << getHexStr(b) << " = " << getHexStr(opCompSum) << " == "
//    << getHexStr(opSum) << " -> " << (opSum == opCompSum ? "PASS" : "FAIL") << std::endl;
//    // And
//    word opAnd = _alu.andOp(a, b);
//    word opCompAnd = a & b;
//    std::cout << "And: " << getHexStr(a) << " & " << getHexStr(b) << " = " << getHexStr(opCompAnd) << " == "
//    << getHexStr(opAnd) << " -> " << (opAnd == opCompAnd ? "PASS" : "FAIL") << std::endl;
//    // A
//    word posOp = _alu.posOp(a);
//    std::cout << "Pos: " << getHexStr(a) << " == " << getHexStr(posOp) << " -> " << (posOp == a ? "PASS" : "FAIL")
//    << std::endl;
//    // Not A
//    word negOp = _alu.negOp(a);
//    word negComp = ~a;
//    std::cout << "Neg: " << getHexStr(negComp) << " == " << getHexStr(negOp) << " -> " << (negComp == negOp ? "PASS" : "FAIL")
//    << std::endl;
//    // Zero flag
//    _alu.posOp(0);
//    std::cout << "Zero flag -> " << (_alu.getZ() ? "PASS" : "FAIL") << std::endl;
//    _alu.posOp(1);
//    std::cout << "Zero flag -> " << (!_alu.getZ() ? "PASS" : "FAIL") << std::endl;
//    // Negative flag
//    _alu.posOp(0);
//    std::cout << "Negative flag -> " << (!_alu.getN() ? "PASS" : "FAIL") << std::endl;
//    _alu.posOp(-1);
//    std::cout << "Negative flag -> " << (_alu.getN() ? "PASS" : "FAIL") << std::endl;
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
    _alu.reset();
    _currentInstruction = instruction();
    _amux.reset();
    _shifter.reset();
    jmp.address = 0;
    jmp.cond = COND::NO_JUMP;
    cycle = 0;
    subCycle = 0;
}

void simulator::run_tests() {
    test_memory();
    test_registers();
    test_alu();
}

void simulator::parse(const std::string& input) {
    auto instruction = _parser.parseLine(input);
    if (!instruction.isValid()) {
        std::cout << "Invalid instruction" << std::endl;
    } else {
        // Run the instruction
        std::cout << "Running instruction: " << std::endl << instruction.toString() << std::endl;
    }
}

const instruction &simulator::getCurrentInstruction() const {
    return _currentInstruction;
}

void simulator::setCurrentInstruction(const instruction &currentInstruction) {
    _currentInstruction = currentInstruction;
}

void simulator::setInstructions(const std::vector<instruction> &instructions) {
    _instructions = instructions;
}
