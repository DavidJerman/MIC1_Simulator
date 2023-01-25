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

    void next();

    void run();

    void reset();

    void parse(const std::string& input);

    // Testing
    void run_tests();

    void test_memory();

    void test_registers();

    void test_alu();

private:
    static void printHex(word value);

    static std::string getHexStr(word value);

    parser _parser;

    memory _memory;
    registers _registers;
    alu _alu;
    amux _amux;
    shifter _shifter;

    byte _jumpAddress {0};
    instruction _currentInstruction {};
    int subCycle {0};
    int cycle {0};
};


#endif //HOMICSIM_SIMULATOR_H
