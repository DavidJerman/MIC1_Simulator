//
// Created by pinkynyte on 1/23/23.
//

#ifndef HOMICSIM_TEST_SIMULATOR_H
#define HOMICSIM_TEST_SIMULATOR_H

#include <iostream>
#include "../parser.h"

namespace SIMULATOR_TEST {
    // Prototypes
    bool run();

    // Implementation
    bool run() {
        std::cout << "Running simulator tests..." << std::endl;

        bool result = true;
        simulator sim;

        std::string input = "a := rshift(inv(b)); if n then goto 33; wr;";
        sim.parse(input);

        std::string input2 = "_mbr := rshift(band(a, c)); _mar := c; if n then goto 33; wr;";
        sim.parse(input2);

        std::cout << "Components tests:" << std::endl;
        sim.run_tests();

        return result;
    }
}

#endif //HOMICSIM_TEST_SIMULATOR_H
