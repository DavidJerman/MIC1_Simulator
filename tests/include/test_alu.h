#pragma once

#include "alu.h"

namespace ALU_TEST
{
    // Prototypes
    bool run();

    bool test_add(alu &a);

    bool test_and(alu &a);

    bool test_pos(alu &a);

    bool test_neg(alu &a);

    bool test_reset(alu &a);
} // namespace ALU_TEST
