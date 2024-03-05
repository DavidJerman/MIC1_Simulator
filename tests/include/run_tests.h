//
// Created by david on 1/21/2023.
//

#pragma once

#include "test_parser.h"
#include "test_simulator.h"

#include <iostream>

void run_tests() {
    std::cout << "[0] Running tests..." << std::endl;
    std::cout << "[1] Parser: " << std::endl;
    auto res = PARSE_TEST::run();
    if (res)
        std::cout << "[1] Passed!" << std::endl;
    else
        std::cout << "[1] Failed!" << std::endl;
    std::cout << "[2] Simulator: " << std::endl;
    res = SIMULATOR_TEST::run();
    if (res)
        std::cout << "[2] Passed!" << std::endl;
    else
        std::cout << "[2] Failed!" << std::endl;
    std::cout << "[0] Tests complete!" << std::endl;

    std::cout << "[x] Press any key to continue..." << std::endl;
    std::cin.get();
}
