#include <iostream>

#include "simulator.h"
#include "tests/run_tests.h"

int main() {
    std::cout << "MIC-1 Simulator" << std::endl;
//    simulator sim = simulator();
//    sim.test_memory();
//    sim.test_registers();
//    sim.test_alu();

    // Test
    run_tests();

    return 0;
}
