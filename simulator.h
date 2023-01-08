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

class simulator {
public:
    simulator();

    void next();

    // For testing purposes
    void test_memory();

private:
    static void printHex(word value);

    static std::string getHexStr(word value);

    memory mem;
    registers reg;
};


#endif //HOMICSIM_SIMULATOR_H
