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
    std::vector<instruction> instructions;
//    instructions = p.parseFile("program.mp");
//
//    try {
//        for (auto &i : instructions) {
//            sim.setCurrentInstruction(i);
//            for (int j = 0; j < 4; j++) {
//                sim.next();
//            }
//        }
//    } catch (std::exception &e) {
//        std::cout << "Caught exception: " << e.what() << std::endl;
//    }
//
//    sim.reset();
//    instructions = p.parseFile("program2.mp");
//    try {
//        for (auto &i : instructions) {
//            [&](){
//                sim.setCurrentInstruction(i);
//                for (int j = 0; j < 4; j++) {
//                    sim.next();
//                }
//            }();
//        }
//    } catch (std::exception &e) {
//        std::cout << "Caught exception: " << e.what() << std::endl;
//    }

    sim.reset();
    instructions = p.parseFile("SUMOFN.MP");
    if (instructions.empty()) {
        std::cout << "No instructions parsed" << std::endl;
    }
    sim.setInstructions(instructions);
    sim.setMemoryCell((word)0, (word)20);
    sim.setMemoryCell((word)1, (word)28);
    sim.setMemoryCell((word)2, (word)19);
    sim.setMemoryCell((word)20, (word)5);
    sim.setMemoryCell((word)28, (word)1);
    sim.setMemoryCell((word)29, (word)2);
    sim.setMemoryCell((word)30, (word)3);
    sim.setMemoryCell((word)31, (word)4);
    sim.setMemoryCell((word)32, (word)5);
    while (sim.next()) ;
    auto res = sim.getMemoryCell((word)19);
    std::cout << "Result: " << res << std::endl;

    return 0;
}
