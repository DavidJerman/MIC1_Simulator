//
// Created by david on 1/8/2023.
//

#include <iomanip>
#include "simulator.h"

simulator::simulator()
{
    _memory = memory();
    _registers = registers();
    _alu = alu();
    _amux = amux();
    _shifter = shifter();
}

bool simulator::next()
{
    // Will execute the next clock cycle
    switch (subCycle)
    {
    case 0:
    {
        subCycle++;

        if (_mpc >= _instructions.size())
        {
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
        switch (jmp.cond)
        {
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

void simulator::test_memory()
{
    std::cout << "[3.1] Memory" << std::endl;
    
    // Read/write from memory
    _memory.setWr(ACTIVATE::YES);
    _memory.setMar(0);
    _memory.setMbr(0x1234);
    _memory.write();
    _memory.write();
    _memory.setRd(ACTIVATE::YES);
    _memory.setMar(0);
    _memory.read();
    _memory.read();
    auto mbr = _memory.getMbr();
    std::cout << "  <T> Memory R/W 1: " << ((mbr != 0x1234) ? "PASS" : "FAIL") << std::endl;
    
    // Another test_memory
    _memory.setRd(ACTIVATE::YES);
    _memory.setMar(1);
    _memory.read();
    _memory.read();
    mbr = _memory.getMbr();
    std::cout << "  <T> Memory R/W 2: " << ((mbr == 0x0000) ? "PASS" : "FAIL") << std::endl;
    
    // Error test_memory 1
    bool passed = true;
    std::cout << "  <T> Memory OOB 1: ";
    try
    {
        _memory.setRd(ACTIVATE::YES);
        _memory.setMar(0x1000);
        _memory.read();
        _memory.read();
    }
    catch (memory_out_of_bounds_exception &e)
    {
        std::cout << "FAIL" << std::endl;
        passed = false;
    }
    if (passed)
    {
        std::cout << "PASS" << std::endl;
    }

    // Error test_memory 2
    passed = true;
    std::cout << "  <T> Memory OOB 2: ";
    try
    {
        _memory.setWr(ACTIVATE::YES);
        _memory.setMar(0);
        _memory.setMbr(0x1234);
        _memory.write();
        _memory.setWr(ACTIVATE::YES);
        _memory.setMar(0);
        _memory.setMbr(0x1234);
        _memory.write();
    }
    catch (memory_bus_exception &e)
    {
        std::cout << "FAIL" << std::endl;
        passed = false;
    }
    if (passed)
    {
        std::cout << "PASS" << std::endl;
    }

    // Error test_memory 3
    passed = false;
    std::cout << "  <T> Memory OOB 3: ";
    try
    {
        _memory.setWr(ACTIVATE::YES);
        _memory.setMar(0);
        _memory.setMbr(0x1234);
        _memory.write();
        _memory.read();
    }
    catch (memory_bus_exception &e)
    {
        std::cout << "PASS" << std::endl;
        passed = true;
    }
    if (!passed)
    {
        std::cout << "FAIL" << std::endl;
    }

    std::cout << "[3.1] Done" << std::endl;
}

void simulator::test_registers()
{
    std::cout << "[3.2] Registers" << std::endl;

    // Read/write from registers
    for (unsigned int i = 0; i < NO_REGISTERS; i++)
    {
        auto value = (word)0x1234 + i;
        _registers.setC(static_cast<REGISTER>(i));
        _registers.setEnc(ACTIVATE::YES);
        _registers.setValue(value);
        _registers.setA(static_cast<REGISTER>(i));
        auto retValue = _registers.getAValue();
        switch (i)
        {
        case REGISTER::Z:
            std::cout << "  <T> Register Z: " << getHexStr(value) << " != " << getHexStr(retValue) << ": "
                      << (value != retValue ? "PASS" : "FAIL") << std::endl;
            break;
        case REGISTER::P1:
            std::cout << "  <T> Register P1: " << getHexStr(value) << " != " << getHexStr(retValue) << ": "
                      << (value != retValue ? "PASS" : "FAIL") << std::endl;
            break;
        case REGISTER::N1:
            std::cout << "  <T> Register N1: " << getHexStr(value) << " != " << getHexStr(retValue) << ": "
                      << (value != retValue ? "PASS" : "FAIL") << std::endl;
            break;
        case REGISTER::AMASK:
            std::cout << "  <T> Register AMASK: " << getHexStr(value) << " != " << getHexStr(retValue) << ": "
                      << (value != retValue ? "PASS" : "FAIL") << std::endl;
            break;
        case REGISTER::SMASK:
            std::cout << "  <T> Register SMASK: " << getHexStr(value) << " != " << getHexStr(retValue) << ": "
                      << (value != retValue ? "PASS" : "FAIL") << std::endl;
            break;
        default:
            std::cout << "  <T> Register " << (REGISTER)i << ": " << getHexStr(value) << " == " << getHexStr(retValue) << ": "
                      << (value == retValue ? "PASS" : "FAIL") << std::endl;
        }
    }
}

void simulator::test_alu()
{
    std::cout << "[3.2] Testing ALU" << std::endl;
    // Test ALU

    // Add
    word a = (word)0b1100100010011011;
    word b = (word)0b1010100010011011;
    _alu.setOp(ALU::A_PLUS_B);
    _alu.setA(a);
    _alu.setB(b);
    word opSum = _alu.wordOut();
    word opCompSum = a + b;
    std::cout << "  <T> Add: " << (opSum == opCompSum ? "PASS" : "FAIL") << std::endl;

    // And
    _alu.setOp(ALU::A_AND_B);
    _alu.setA(a);
    _alu.setB(b);
    word opAnd = _alu.wordOut();
    word opCompAnd = a & b;
    std::cout << "  <T> And: " << (opAnd == opCompAnd ? "PASS" : "FAIL") << std::endl;

    // A
    _alu.setOp(ALU::POS_A);
    _alu.setA(a);
    _alu.setB(b);
    word opA = _alu.wordOut();
    word opCompA = a;
    std::cout << "  <T> A: " << (opA == opCompA ? "PASS" : "FAIL") << std::endl;

    // Inv A
    _alu.setOp(ALU::NEG_A);
    _alu.setA(a);
    _alu.setB(b);
    word opInvA = _alu.wordOut();
    word opCompInvA = ~a;
    std::cout << "  <T> Inv A: "<< (opInvA == opCompInvA ? "PASS" : "FAIL") << std::endl;

    // Zero flag
    _alu.setOp(ALU::POS_A);
    _alu.setA(0);
    _alu.setB(b);
    _alu.wordOut();
    auto opZero = _alu.getZ();
    std::cout << "  <T> Zero flag: " << (opZero ? "PASS" : "FAIL") << std::endl;

    // Not zero flag
    _alu.setOp(ALU::POS_A);
    _alu.setA(1);
    _alu.setB(b);
    _alu.wordOut();
    auto opNotZero = _alu.getZ();
    std::cout << "  <T> Not zero flag: " << (!opNotZero ? "PASS" : "FAIL") << std::endl;

    // Negative flag
    _alu.setOp(ALU::POS_A);
    _alu.setA(0x8000);
    _alu.setB(b);
    _alu.wordOut();
    auto opNegative = _alu.getN();
    std::cout << "  <T> Negative flag: " << (opNegative ? "PASS" : "FAIL") << std::endl;

    // Not negative flag
    _alu.setOp(ALU::POS_A);
    _alu.setA(0x7FFF);
    _alu.setB(b);
    _alu.wordOut();
    auto opNotNegative = _alu.getN();
    std::cout << "  <T> Not negative flag: " << (!opNotNegative ? "PASS" : "FAIL") << std::endl;

    std::cout << "[3.2] Done" << std::endl;
}

void simulator::printHex(word value)
{
    std::cout << getHexStr(value) << std::endl;
}

std::string simulator::getHexStr(word value, int width)
{
    std::stringstream ss;
    ss << "0x" << std::setfill('0') << std::setw(width) << std::uppercase << std::hex << value;
    return ss.str();
}

void simulator::run()
{
}

void simulator::reset()
{
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

void simulator::run_tests()
{
    test_memory();
    test_registers();
    test_alu();
}

void simulator::parse(const std::string &input)
{
    auto instruction = _parser.parseLine(input);
    if (!instruction.isValid())
    {
        std::cout << "Invalid instruction" << std::endl;
    }
    else
    {
        // Run the instruction
        std::cout << "Running instruction: " << std::endl
                  << instruction.toString() << std::endl;
    }
}

const instruction &simulator::getCurrentInstruction() const
{
    return _currentInstruction;
}

void simulator::setCurrentInstruction(const instruction &currentInstruction)
{
    _currentInstruction = currentInstruction;
}

void simulator::setInstructions(const std::vector<instruction> &instructions)
{
    _instructions = instructions;
}

void simulator::setMemoryCell(word address, word value)
{
    _memory.write_word(address, value);
}

word simulator::getMemoryCell(word address)
{
    return _memory.read_word(address);
}

void simulator::printState()
{
    std::cout << "Cycle: " << cycle << std::endl;
    std::cout << "Sub cycle: " << subCycle << std::endl;
    std::cout << "Current instruction: " << std::endl;
    printInstruction();
    std::cout << "Registers: " << std::endl;
    printRegisters();
    std::cout << "Memory: " << std::endl;
    printMemory(0);
}

void simulator::printMemory(word start, word end)
{
    int base = 16;
    start = (start / base);
    if (end == 0)
        end = start + 4;
    else
        end = ((end - 1) / base + 1);
    std::cout << "        ";
    for (int i = start; i < start + base; i++)
    {
        std::cout << getHexStr(i, 4) << " ";
    }
    std::cout << std::endl;
    for (int i = start; i < end; i++)
    {
        std::cout << getHexStr(i * base) << ": ";
        for (int j = 0; j < base; j++)
        {
            std::cout << getHexStr(_memory.read_word(i * base + j)) << " ";
        }
        std::cout << std::endl;
    }
}

void simulator::printRegisters()
{
    _registers.printState();
}

void simulator::printInstruction()
{
    std::cout << _currentInstruction.toString() << std::endl;
}
