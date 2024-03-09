#pragma once

#include "shifter.h"

namespace SHIFTER_TEST
{
    // Prototypes
    bool run();

    bool test_shift_left(shifter &s);

    bool test_shift_right(shifter &s);

    bool test_no_shift(shifter &s);

    bool test_invalid_shift(shifter &s);

} // namespace ALU_TEST
