#pragma once

#include "parser.h"

namespace PARSE_TEST
{
    // Prototypes
    bool run();

    void invalid_instruction();

    bool test_rd(parser &p);

    bool test_wr(parser &p);

    bool test_goto(parser &p);

    bool test_if(parser &p);

    bool test_add(parser &p);

    bool test_and(parser &p);

    bool test_not(parser &p);

    bool test_pass(parser &p);

    bool test_shift(parser &p);

    bool test_advanced(parser &p);

    bool complex_test(parser &p);

    bool test_mbr(parser &p);

    bool test_mar(parser &p);

    bool test_isNumber_1(parser &p);

    bool test_isNumber_2(parser &p);

    bool test_isNumber_3(parser &p);

    bool test_isNumber_4(parser &p);

    bool test_toRegister_1(parser &p);

    bool test_toRegister_2(parser &p);

    bool test_toRegister_3(parser &p);

    bool test_toRegister_4(parser &p);

    bool test_arithmetic_1(parser &p);

    bool test_arithmetic_2(parser &p);

    bool test_arithmetic_3(parser &p);

    bool test_arithmeticPlus_1(parser &p);

    bool test_arithmeticPlus_2(parser &p);

    bool test_arithmeticPlus_3(parser &p);

    bool test_arithmeticPlus_4(parser &p);

    bool test_setA_1(parser &p);

    bool test_setA_2(parser &p);

    bool test_setA_3(parser &p);

    bool test_setB_1(parser &p);

    bool test_setB_2(parser &p);

    bool test_setB_3(parser &p);
} // namespace PARSE_TEST
