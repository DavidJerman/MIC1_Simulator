#include "test_shifter.h"

#include <iostream>

namespace SHIFTER_TEST
{

    bool run()
    {
        // Variables
        bool success = true;
        shifter s;

        // Array of test functions
        bool (*tests[])(shifter &s) = {
            test_shift_left,
            test_shift_right,
            test_no_shift,
            test_invalid_shift};

        // Run tests
        for (const auto &test : tests)
        {
            auto result = test(s);

            if (result)
                std::cout << "PASS" << std::endl;
            else
                std::cout << "FAIL" << std::endl;

            if (!result)
            {
                success = false;
            }
        }

        return success;
    }

    bool test_shift_left(shifter &s)
    {
        std::cout << "  <T> Shift left: ";

        s.set(SH::LEFT_SHIFT);
        s.wordIn(0b00000001);
        return s.wordOut() == 0b00000010;
    }

    bool test_shift_right(shifter &s)
    {
        std::cout << "  <T> Shift right: ";

        s.set(SH::RIGHT_SHIFT);
        s.wordIn(0b00000010);
        return s.wordOut() == 0b00000001;
    }

    bool test_no_shift(shifter &s)
    {
        std::cout << "  <T> No shift: ";

        s.set(SH::NO_SHIFT);
        s.wordIn(0b00000001);
        return s.wordOut() == 0b00000001;
    }

    bool test_invalid_shift(shifter &s)
    {
        std::cout << "  <T> Invalid shift: ";

        s.set(SH::INVALID_SHIFT);
        s.wordIn(0b00000001);
        return s.wordOut() == 0x00;
    }

} // namespace SHIFTER_TEST
