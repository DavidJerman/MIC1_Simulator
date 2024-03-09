#include "test_alu.h"

#include <iostream>

namespace ALU_TEST
{

    bool run()
    {
        // Variables
        bool success = true;
        alu a;
        
        // Array of test functions
        bool (*tests[])(alu &a) = {test_add, test_and, test_pos, test_neg, test_reset};

        // Run tests
        for (const auto &test : tests)
        {
            auto result = test(a);

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

    bool test_add(alu &a)
    {
        std::cout << "  <T> Add: ";

        word A = 0x1004;
        word B = 0x3333;

        a.setA(A);
        a.setB(B);
        a.setOp(ALU::A_PLUS_B);

        auto result = a.wordOut();
        word expected = A + B;

        return result == expected;
    }

    bool test_and(alu &a)
    {
        std::cout << "  <T> And: ";

        word A = 0x1004;
        word B = 0x3333;

        a.setA(A);
        a.setB(B);
        a.setOp(ALU::A_AND_B);

        auto result = a.wordOut();
        word expected = A & B;

        return result == expected;
    }
    
    bool test_pos(alu &a)
    {
        std::cout << "  <T> Pos A: ";

        word A = 0x1004;
        word B = 0x3333;

        a.setA(A);
        a.setB(B);
        a.setOp(ALU::POS_A);

        auto result = a.wordOut();
        word expected = A;

        return result == expected;
    }
    
    bool test_neg(alu &a)
    {
        std::cout << "  <T> Neg A: ";

        word A = 0x1004;
        word B = 0x3333;

        a.setA(A);
        a.setB(B);
        a.setOp(ALU::NEG_A);

        auto result = a.wordOut();
        word expected = ~A;

        return result == expected && a.getN() == true;
    }
    
    bool test_reset(alu &a)
    {
        std::cout << "  <T> Reset: ";

        word A = 0x1004;
        word B = 0x3333;

        a.setA(A);
        a.setB(B);
        a.setOp(ALU::A_PLUS_B);

        a.reset();

        return a.getN() == false && a.getZ() == false && a.wordOut() == 0;
    }
}
