//
// Created by david on 1/8/2023.
//

#ifndef HOMICSIM_SIMULATOR_H
#define HOMICSIM_SIMULATOR_H

#include <sstream>
#include <iostream>
#include <thread>

#include "parser.h"
#include "memory.h"
#include "registers.h"
#include "alu.h"
#include "amux.h"
#include "shifter.h"

class simulator {
public:
    simulator();

    bool next();

    void run();

    void reset();

    void parse(const std::string& input);

    const instruction &getCurrentInstruction() const;

    void setCurrentInstruction(const instruction &currentInstruction);

    void setInstructions(const std::vector<instruction> &instructions);

    // Dangerous functions
    void setMemoryCell(word address, word value);

    word getMemoryCell(word address);

    // Testing
    void run_tests();

    void test_memory();

    void test_registers();

    void test_alu();

    // Visualization
    void printState();

    void printMemory(word start, word end = 0);

    void printRegisters();

    void printInstruction();

private:
    static void printHex(word value);

    static std::string getHexStr(word value, int width = 4);

    parser _parser;

    memory _memory;
    registers _registers;
    alu _alu;
    amux _amux;
    shifter _shifter;

    JMP jmp;
    instruction _currentInstruction {};
    std::vector<instruction> _instructions {};
    int subCycle {0};
    int cycle {0};
    byte _mpc {0};
};


#endif //HOMICSIM_SIMULATOR_H
