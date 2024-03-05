//
// Created by pinkynyte on 1/23/23.
//

#pragma once

#include <iostream>
#include "parser.h"
#include "simulator.h"

namespace SIMULATOR_TEST
{
    // Prototypes
    bool run();

    // Implementation
    bool run()
    {
        std::cout << "Running simulator tests..." << std::endl;

        bool result = true;
        simulator sim;

        std::string input = "a := rshift(inv(b)); if n then goto 33; wr;";
        sim.parse(input);

        std::string input2 = "mbr := rshift(band(a, c)); mar := c; if n then goto 33; wr;";
        sim.parse(input2);

        std::cout << "Components tests:" << std::endl;
        sim.run_tests();

        return result;
    }
}
