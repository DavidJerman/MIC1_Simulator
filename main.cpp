#include <iostream>

#include "simulator.h"

int main() {
    std::cout << "MIC-1 Simulator" << std::endl;
    simulator sim = simulator();
    sim.test_memory();
    return 0;
}
