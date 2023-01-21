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

    bool run() {
        // Variables
        bool success = true;
        parser p = parser();
        // Array of test functions
        bool (*tests[])(parser &p) = {test_rd, test_wr, test_goto, test_if, test_add};

        // Run tests
        for (const auto &test: tests) {
            if (!test(p)) {
                invalid_instruction();
                success = false;
            }
        }

        return success;
    }

    void invalid_instruction() {
        std::cout << "[!] Invalid instruction!" << std::endl;
    }

    bool test_rd(parser &p) {
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

    bool test_wr(parser &p) {
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

    bool test_goto(parser &p) {
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

    bool test_if(parser &p) {
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

    bool test_add(parser &p) {
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
}

#endif //HOMICSIM_TEST_PARSER_H
