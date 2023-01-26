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
    // run_tests();

    parser p;
    simulator sim;
    sim.reset();
    auto instructions = p.parseFile("program.mp");

    try {
        for (auto &i : instructions) {
            sim.setCurrentInstruction(i);
            for (int j = 0; j < 4; j++) {
                sim.next();
            }
        }
    } catch (std::exception &e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    sim.reset();
    instructions = p.parseFile("program2.mp");
    try {
        for (auto &i : instructions) {
            [&](){
                sim.setCurrentInstruction(i);
                for (int j = 0; j < 4; j++) {
                    sim.next();
                }
            }();
        }
    } catch (std::exception &e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }


    return 0;
}
