//
// Created by david on 1/21/2023.
//

#ifndef HOMICSIM_TEST_PARSER_H
#define HOMICSIM_TEST_PARSER_H

#include <iostream>
#include "../parser.h"

namespace PARSE_TEST {
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

    bool run()
    {
        // Variables
        bool success = true;
        parser p = parser();
        // Array of test functions
        bool (*tests[])(parser &p) = {test_rd, test_wr, test_goto, test_if, test_add, test_and, test_not, test_pass, test_shift, test_advanced, complex_test};

        // Run tests
        for (const auto &test: tests)
        {
            if (!test(p))
            {
                invalid_instruction();
                success = false;
            }
        }

        return success;
    }

    void invalid_instruction()
    {
        std::cout << "[!] Invalid instruction!" << std::endl;
    }

    bool test_rd(parser &p)
    {
        // Read
        std::cout << "  <T> Read" << std::endl;
        std::string input = "rd;";
        instruction i = p.parse(input);
        auto code = i.getCode();
        dword correctCode = 1 << RD_SH;
        if (!i.isValid())
            return false;
        if (code != correctCode)
            return false;
        return true;
    }

    bool test_wr(parser &p)
    {
        // Write
        std::cout << "  <T> Write" << std::endl;
        std::string input = "wr;";
        instruction i = p.parse(input);
        auto code = i.getCode();
        dword correctCode = 1 << WR_SH;
        if (!i.isValid())
            return false;
        if (code != correctCode)
            return false;
        return true;
    }

    bool test_goto(parser &p)
    {
        // Goto
        std::cout << "  <T> Goto" << std::endl;
        byte address = 99;
        std::string input = "goto " + std::to_string(address) + ";";
        instruction i = p.parse(input);
        auto code = i.getCode();
        dword correctCode = JUMP << COND_SH;
        correctCode |= address;
        if (!i.isValid())
            return false;
        if (code != correctCode)
            return false;
        return true;
    }

    bool test_if(parser &p)
    {
        std::cout << "  <T> If" << std::endl;
        // If z
        bool success = true;
        byte address = 99;
        std::string flag = "z";
        std::string input = "if " + flag + " then goto " + std::to_string(address) + ";";
        instruction i = p.parse(input);
        auto code = i.getCode();
        dword correctCode = Z_JUMP << COND_SH;
        correctCode |= address;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        // If n
        flag = "n";
        input = "if " + flag + " then goto " + std::to_string(address) + ";";
        i = p.parse(input);
        code = i.getCode();
        correctCode = N_JUMP << COND_SH;
        correctCode |= address;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        return success;
    }

    bool test_add(parser &p)
    {
        std::cout << "  <T> Add" << std::endl;
        // Add a := a + a;
        bool success = true;
        std::string leftReg = "a";
        std::string rightReg = "a";
        std::string resReg = "a";
        std::string input = resReg + " := " + leftReg + " + " + rightReg + ";";
        instruction i = p.parse(input);
        auto code = i.getCode();
        dword correctCode = A_PLUS_B << ALU_SH;
        correctCode |= A << BUS_A_SH;
        correctCode |= A << BUS_B_SH;
        correctCode |= A << BUS_C_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        // Add a := a + b;
        leftReg = "a";
        rightReg = "b";
        resReg = "a";
        input = resReg + " := " + leftReg + " + " + rightReg + ";";
        i = p.parse(input);
        code = i.getCode();
        correctCode = A_PLUS_B << ALU_SH;
        correctCode |= A << BUS_A_SH;
        correctCode |= B << BUS_B_SH;
        correctCode |= A << BUS_C_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        // Add a := b + a;
        leftReg = "b";
        rightReg = "a";
        resReg = "a";
        input = resReg + " := " + leftReg + " + " + rightReg + ";";
        i = p.parse(input);
        code = i.getCode();
        correctCode = A_PLUS_B << ALU_SH;
        correctCode |= B << BUS_A_SH;
        correctCode |= A << BUS_B_SH;
        correctCode |= A << BUS_C_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        // Add a := b + c;
        leftReg = "b";
        rightReg = "c";
        resReg = "a";
        input = resReg + " := " + leftReg + " + " + rightReg + ";";
        i = p.parse(input);
        code = i.getCode();
        correctCode = A_PLUS_B << ALU_SH;
        correctCode |= B << BUS_A_SH;
        correctCode |= C << BUS_B_SH;
        correctCode |= A << BUS_C_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        return success;
    }

    bool test_and(parser &p)
    {
        std::cout << "  <T> And" << std::endl;
        bool success = true;
        // a := band(a, a);
        std::string resReg = "a";
        std::string leftReg = "a";
        std::string rightReg = "a";
        std::string input = resReg + " := band(" + leftReg + ", " + rightReg + ");";
        instruction i = p.parse(input);
        auto code = i.getCode();
        dword correctCode = A_AND_B << ALU_SH;
        correctCode |= A << BUS_A_SH;
        correctCode |= A << BUS_B_SH;
        correctCode |= A << BUS_C_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        // c := band(a, b);
        resReg = "c";
        leftReg = "a";
        rightReg = "b";
        input = resReg + " := band(" + leftReg + ", " + rightReg + ");";
        i = p.parse(input);
        code = i.getCode();
        correctCode = A_AND_B << ALU_SH;
        correctCode |= A << BUS_A_SH;
        correctCode |= B << BUS_B_SH;
        correctCode |= C << BUS_C_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        return success;
    }

    bool test_not(parser &p)
    {
        std::cout << "  <T> Not (inv)" << std::endl;
        bool success = true;
        // a := not(a);
        std::string resReg = "a";
        std::string reg = "a";
        std::string input = resReg + " := inv(" + reg + ");";
        instruction i = p.parse(input);
        auto code = i.getCode();
        dword correctCode = NEG_A << ALU_SH;
        correctCode |= A << BUS_A_SH;
        correctCode |= A << BUS_C_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        // c := not(a);
        resReg = "c";
        reg = "a";
        input = resReg + " := inv(" + reg + ");";
        i = p.parse(input);
        code = i.getCode();
        correctCode = NEG_A << ALU_SH;
        correctCode |= A << BUS_A_SH;
        correctCode |= C << BUS_C_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        return success;
    }

    bool test_pass(parser &p)
    {
        std::cout << "  <T> Pass" << std::endl;
        bool success = true;
        // a := a;
        std::string resReg = "a";
        std::string reg = "a";
        std::string input = resReg + " := " + reg + ";";
        instruction i = p.parse(input);
        auto code = i.getCode();
        dword correctCode = POS_A << ALU_SH;
        correctCode |= A << BUS_A_SH;
        correctCode |= A << BUS_C_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        // c := a;
        resReg = "c";
        reg = "a";
        input = resReg + " := " + reg + ";";
        i = p.parse(input);
        code = i.getCode();
        correctCode = POS_A << ALU_SH;
        correctCode |= A << BUS_A_SH;
        correctCode |= C << BUS_C_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        // c := (-1);
        resReg = "c";
        reg = "(-1)";
        input = resReg + " := " + reg + ";";
        i = p.parse(input);
        code = i.getCode();
        correctCode = POS_A << ALU_SH;
        correctCode |= N1 << BUS_A_SH;
        correctCode |= C << BUS_C_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        return success;
    }

    bool test_shift(parser &p)
    {
        std::cout << "  <T> Shift" << std::endl;
        // a := lshift(a);
        std::string resReg = "a";
        std::string reg = "a";
        std::string input = resReg + " := lshift(" + reg + ");";
        instruction i = p.parse(input);
        auto code = i.getCode();
        dword correctCode = POS_A << ALU_SH;
        correctCode |= A << BUS_A_SH;
        correctCode |= A << BUS_C_SH;
        correctCode |= LEFT_SHIFT << SH_SH;
        if (!i.isValid())
            return false;
        if (code != correctCode)
            return false;
        // c := rshift(b);
        resReg = "c";
        reg = "b";
        input = resReg + " := rshift(" + reg + ");";
        i = p.parse(input);
        code = i.getCode();
        correctCode = POS_A << ALU_SH;
        correctCode |= B << BUS_A_SH;
        correctCode |= C << BUS_C_SH;
        correctCode |= RIGHT_SHIFT << SH_SH;
        if (!i.isValid())
            return false;
        if (code != correctCode)
            return false;
        return true;
    }

    bool test_advanced(parser &p)
    {
        std::cout << "  <T> Advanced" << std::endl;
        bool success = true;
        // a := lshift(a + b);
        std::string resReg = "a";
        std::string regLeft = "a";
        std::string regRight = "b";
        std::string input = resReg + " := lshift(" + regLeft + " + " + regRight + ");";
        instruction i = p.parse(input);
        auto code = i.getCode();
        dword correctCode = A_PLUS_B << ALU_SH;
        correctCode |= A << BUS_A_SH;
        correctCode |= B << BUS_B_SH;
        correctCode |= A << BUS_C_SH;
        correctCode |= LEFT_SHIFT << SH_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        // c := rshift(a + b);
        resReg = "c";
        regLeft = "a";
        regRight = "b";
        input = resReg + " := rshift(" + regLeft + " + " + regRight + ");";
        i = p.parse(input);
        code = i.getCode();
        correctCode = A_PLUS_B << ALU_SH;
        correctCode |= A << BUS_A_SH;
        correctCode |= B << BUS_B_SH;
        correctCode |= C << BUS_C_SH;
        correctCode |= RIGHT_SHIFT << SH_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        // c := rshift(band(a, (-1)));
        resReg = "c";
        regLeft = "a";
        regRight = "(-1)";
        input = resReg + " := rshift(band(" + regLeft + ", " + regRight + "));";
        i = p.parse(input);
        code = i.getCode();
        correctCode = A_AND_B << ALU_SH;
        correctCode |= A << BUS_A_SH;
        correctCode |= N1 << BUS_B_SH;
        correctCode |= C << BUS_C_SH;
        correctCode |= RIGHT_SHIFT << SH_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        return success;
    }

    bool complex_test(parser &p)
    {
        std::cout << "  <T> Complex" << std::endl;
        bool success = true;
        // ac := lshift(a + b); if z then goto 22; rd;
        std::string resReg = "ac";
        std::string regLeft = "a";
        std::string regRight = "b";
        byte address = 22;
        std::string input = resReg + " := lshift(" + regLeft + " + " + regRight + "); if z then goto " + std::to_string(address) + "; rd;";
        instruction i = p.parse(input);
        auto code = i.getCode();
        dword correctCode = A_PLUS_B << ALU_SH;
        correctCode |= A << BUS_A_SH;
        correctCode |= B << BUS_B_SH;
        correctCode |= AC << BUS_C_SH;
        correctCode |= LEFT_SHIFT << SH_SH;
        correctCode |= Z_JUMP << COND_SH;
        correctCode |= address << ADDRESS_SH;
        correctCode |= YES << RD_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        // ac := rshift(inv(a)); if n then goto 22; wr;
        resReg = "ac";
        regLeft = "a";
        address = 22;
        input = resReg + " := rshift(inv(" + regLeft + ")); if n then goto " + std::to_string(address) + "; wr;";
        i = p.parse(input);
        code = i.getCode();
        correctCode = NEG_A << ALU_SH;
        correctCode |= A << BUS_A_SH;
        correctCode |= AC << BUS_C_SH;
        correctCode |= RIGHT_SHIFT << SH_SH;
        correctCode |= N_JUMP << COND_SH;
        correctCode |= address << ADDRESS_SH;
        correctCode |= YES << WR_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        return success;
    }
}

#endif //HOMICSIM_TEST_PARSER_H
