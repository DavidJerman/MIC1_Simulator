//
// Created by david on 1/8/2023.
//

#ifndef HOMICSIM_SIMULATOR_H
#define HOMICSIM_SIMULATOR_H

#include <sstream>
#include <iostream>
#include <thread>

#include "memory.h"
#include "registers.h"
#include "alu.h"

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

    memory _memory;
    registers _registers;
    alu _alu;
};


#endif //HOMICSIM_SIMULATOR_H
