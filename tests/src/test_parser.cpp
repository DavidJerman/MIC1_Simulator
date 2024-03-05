#include "test_parser.h"

#include <iostream>

namespace PARSE_TEST
{
    bool run()
    {
        // Variables
        bool success = true;
        parser p = parser();
        // Array of test functions
        bool (*tests[])(parser &p) = {test_rd,
                                      test_wr,
                                      test_goto,
                                      test_if,
                                      test_add,
                                      test_and,
                                      test_not,
                                      test_pass,
                                      test_shift,
                                      test_advanced,
                                      complex_test,
                                      test_mbr,
                                      test_mar,
                                      test_isNumber_1,
                                      test_isNumber_2,
                                      test_isNumber_3,
                                      test_isNumber_4,
                                      test_toRegister_1,
                                      test_toRegister_2,
                                      test_toRegister_3,
                                      test_toRegister_4,
                                      test_arithmetic_1,
                                      test_arithmetic_2,
                                      test_arithmetic_3};

        // Run tests
        for (const auto &test : tests)
        {
            auto result = test(p);

            if (result)
                std::cout << "PASS" << std::endl;
            else
                std::cout << "FAIL" << std::endl;

            if (!result)
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
        std::cout << "  <T> Read: ";
        std::string input = "rd;";
        instruction i = p.parseLine(input);
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
        std::cout << "  <T> Write: ";
        std::string input = "wr;";
        instruction i = p.parseLine(input);
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
        std::cout << "  <T> Goto: ";
        byte address = 99;
        std::string input = "goto " + std::to_string(address) + ";";
        instruction i = p.parseLine(input);
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
        std::cout << "  <T> If: ";
        // If z
        bool success = true;
        byte address = 99;
        std::string flag = "z";
        std::string input = "if " + flag + " then goto " + std::to_string(address) + ";";
        instruction i = p.parseLine(input);
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
        i = p.parseLine(input);
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
        std::cout << "  <T> Add: ";
        // Add a := a + a;
        bool success = true;
        std::string leftReg = "a";
        std::string rightReg = "a";
        std::string resReg = "a";
        std::string input = resReg + " := " + leftReg + " + " + rightReg + ";";
        instruction i = p.parseLine(input);
        auto code = i.getCode();
        dword correctCode = A_PLUS_B << ALU_SH;
        correctCode |= A << BUS_A_SH;
        correctCode |= A << BUS_B_SH;
        correctCode |= A << BUS_C_SH;
        correctCode |= YES << ENC_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        // Add a := a + b;
        leftReg = "a";
        rightReg = "b";
        resReg = "a";
        input = resReg + " := " + leftReg + " + " + rightReg + ";";
        i = p.parseLine(input);
        code = i.getCode();
        correctCode = A_PLUS_B << ALU_SH;
        correctCode |= A << BUS_A_SH;
        correctCode |= B << BUS_B_SH;
        correctCode |= A << BUS_C_SH;
        correctCode |= YES << ENC_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        // Add a := b + a;
        leftReg = "b";
        rightReg = "a";
        resReg = "a";
        input = resReg + " := " + leftReg + " + " + rightReg + ";";
        i = p.parseLine(input);
        code = i.getCode();
        correctCode = A_PLUS_B << ALU_SH;
        correctCode |= B << BUS_A_SH;
        correctCode |= A << BUS_B_SH;
        correctCode |= A << BUS_C_SH;
        correctCode |= YES << ENC_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        // Add a := b + c;
        leftReg = "b";
        rightReg = "c";
        resReg = "a";
        input = resReg + " := " + leftReg + " + " + rightReg + ";";
        i = p.parseLine(input);
        code = i.getCode();
        correctCode = A_PLUS_B << ALU_SH;
        correctCode |= B << BUS_A_SH;
        correctCode |= C << BUS_B_SH;
        correctCode |= A << BUS_C_SH;
        correctCode |= YES << ENC_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        return success;
    }

    bool test_and(parser &p)
    {
        std::cout << "  <T> And: ";
        bool success = true;
        // a := band(a, a);
        std::string resReg = "a";
        std::string leftReg = "a";
        std::string rightReg = "a";
        std::string input = resReg + " := band(" + leftReg + ", " + rightReg + ");";
        instruction i = p.parseLine(input);
        auto code = i.getCode();
        dword correctCode = A_AND_B << ALU_SH;
        correctCode |= A << BUS_A_SH;
        correctCode |= A << BUS_B_SH;
        correctCode |= A << BUS_C_SH;
        correctCode |= YES << ENC_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        // c := band(a, b);
        resReg = "c";
        leftReg = "a";
        rightReg = "b";
        input = resReg + " := band(" + leftReg + ", " + rightReg + ");";
        i = p.parseLine(input);
        code = i.getCode();
        correctCode = A_AND_B << ALU_SH;
        correctCode |= A << BUS_A_SH;
        correctCode |= B << BUS_B_SH;
        correctCode |= C << BUS_C_SH;
        correctCode |= YES << ENC_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        return success;
    }

    bool test_not(parser &p)
    {
        std::cout << "  <T> Not (inv): ";
        bool success = true;
        // a := not(a);
        std::string resReg = "a";
        std::string reg = "a";
        std::string input = resReg + " := inv(" + reg + ");";
        instruction i = p.parseLine(input);
        auto code = i.getCode();
        dword correctCode = NEG_A << ALU_SH;
        correctCode |= A << BUS_A_SH;
        correctCode |= A << BUS_C_SH;
        correctCode |= YES << ENC_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        // c := not(a);
        resReg = "c";
        reg = "a";
        input = resReg + " := inv(" + reg + ");";
        i = p.parseLine(input);
        code = i.getCode();
        correctCode = NEG_A << ALU_SH;
        correctCode |= A << BUS_A_SH;
        correctCode |= C << BUS_C_SH;
        correctCode |= YES << ENC_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        return success;
    }

    bool test_pass(parser &p)
    {
        std::cout << "  <T> Pass: ";
        bool success = true;
        // a := a;
        std::string resReg = "a";
        std::string reg = "a";
        std::string input = resReg + " := " + reg + ";";
        instruction i = p.parseLine(input);
        auto code = i.getCode();
        dword correctCode = POS_A << ALU_SH;
        correctCode |= A << BUS_A_SH;
        correctCode |= A << BUS_C_SH;
        correctCode |= YES << ENC_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        // c := a;
        resReg = "c";
        reg = "a";
        input = resReg + " := " + reg + ";";
        i = p.parseLine(input);
        code = i.getCode();
        correctCode = POS_A << ALU_SH;
        correctCode |= A << BUS_A_SH;
        correctCode |= C << BUS_C_SH;
        correctCode |= YES << ENC_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        // c := (-1);
        resReg = "c";
        reg = "(-1)";
        input = resReg + " := " + reg + ";";
        i = p.parseLine(input);
        code = i.getCode();
        correctCode = POS_A << ALU_SH;
        correctCode |= N1 << BUS_A_SH;
        correctCode |= C << BUS_C_SH;
        correctCode |= YES << ENC_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        return success;
    }

    bool test_shift(parser &p)
    {
        std::cout << "  <T> Shift: ";
        // a := lshift(a);
        std::string resReg = "a";
        std::string reg = "a";
        std::string input = resReg + " := lshift(" + reg + ");";
        instruction i = p.parseLine(input);
        auto code = i.getCode();
        dword correctCode = POS_A << ALU_SH;
        correctCode |= A << BUS_A_SH;
        correctCode |= A << BUS_C_SH;
        correctCode |= LEFT_SHIFT << SH_SH;
        correctCode |= YES << ENC_SH;
        if (!i.isValid())
            return false;
        if (code != correctCode)
            return false;
        // c := rshift(b);
        resReg = "c";
        reg = "b";
        input = resReg + " := rshift(" + reg + ");";
        i = p.parseLine(input);
        code = i.getCode();
        correctCode = POS_A << ALU_SH;
        correctCode |= B << BUS_A_SH;
        correctCode |= C << BUS_C_SH;
        correctCode |= RIGHT_SHIFT << SH_SH;
        correctCode |= YES << ENC_SH;
        if (!i.isValid())
            return false;
        if (code != correctCode)
            return false;
        return true;
    }

    bool test_advanced(parser &p)
    {
        std::cout << "  <T> Advanced: ";
        bool success = true;
        // a := lshift(a + b);
        std::string resReg = "a";
        std::string regLeft = "a";
        std::string regRight = "b";
        std::string input = resReg + " := lshift(" + regLeft + " + " + regRight + ");";
        instruction i = p.parseLine(input);
        auto code = i.getCode();
        dword correctCode = A_PLUS_B << ALU_SH;
        correctCode |= A << BUS_A_SH;
        correctCode |= B << BUS_B_SH;
        correctCode |= A << BUS_C_SH;
        correctCode |= LEFT_SHIFT << SH_SH;
        correctCode |= YES << ENC_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        // c := rshift(a + b);
        resReg = "c";
        regLeft = "a";
        regRight = "b";
        input = resReg + " := rshift(" + regLeft + " + " + regRight + ");";
        i = p.parseLine(input);
        code = i.getCode();
        correctCode = A_PLUS_B << ALU_SH;
        correctCode |= A << BUS_A_SH;
        correctCode |= B << BUS_B_SH;
        correctCode |= C << BUS_C_SH;
        correctCode |= RIGHT_SHIFT << SH_SH;
        correctCode |= YES << ENC_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        // c := rshift(band(a, (-1)));
        resReg = "c";
        regLeft = "a";
        regRight = "(-1)";
        input = resReg + " := rshift(band(" + regLeft + ", " + regRight + "));";
        i = p.parseLine(input);
        code = i.getCode();
        correctCode = A_AND_B << ALU_SH;
        correctCode |= A << BUS_A_SH;
        correctCode |= N1 << BUS_B_SH;
        correctCode |= C << BUS_C_SH;
        correctCode |= RIGHT_SHIFT << SH_SH;
        correctCode |= YES << ENC_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        return success;
    }

    bool complex_test(parser &p)
    {
        std::cout << "  <T> Complex: ";
        bool success = true;
        // ac := lshift(a + b); if z then goto 22; rd;
        std::string resReg = "ac";
        std::string regLeft = "a";
        std::string regRight = "b";
        byte address = 22;
        std::string input = resReg + " := lshift(" + regLeft + " + " + regRight + "); if z then goto " + std::to_string(address) + "; rd;";
        instruction i = p.parseLine(input);
        auto code = i.getCode();
        dword correctCode = A_PLUS_B << ALU_SH;
        correctCode |= A << BUS_A_SH;
        correctCode |= B << BUS_B_SH;
        correctCode |= AC << BUS_C_SH;
        correctCode |= LEFT_SHIFT << SH_SH;
        correctCode |= Z_JUMP << COND_SH;
        correctCode |= address << ADDRESS_SH;
        correctCode |= YES << RD_SH;
        correctCode |= YES << ENC_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        // ac := rshift(inv(a)); if n then goto 22; wr;
        resReg = "ac";
        regLeft = "a";
        address = 22;
        input = resReg + " := rshift(inv(" + regLeft + ")); if n then goto " + std::to_string(address) + "; wr;";
        i = p.parseLine(input);
        code = i.getCode();
        correctCode = NEG_A << ALU_SH;
        correctCode |= A << BUS_A_SH;
        correctCode |= AC << BUS_C_SH;
        correctCode |= RIGHT_SHIFT << SH_SH;
        correctCode |= N_JUMP << COND_SH;
        correctCode |= address << ADDRESS_SH;
        correctCode |= YES << WR_SH;
        correctCode |= YES << ENC_SH;
        if (!i.isValid())
            success = false;
        if (code != correctCode)
            success = false;
        return success;
    }

    bool test_mbr(parser &p)
    {
        std::cout << "  <T> MBR: ";
        bool success = true;
        // _mbr := a; c := d;   --> should be invalid
        std::string resReg = "mbr";
        std::string reg = "a";
        std::string input = resReg + " := " + reg + "; c := d;";
        instruction i = p.parseLine(input);
        if (i.isValid())
            success = false;
        // _mbr := a;   --> should be valid
        resReg = "mbr";
        reg = "a";
        input = resReg + " := " + reg + ";";
        i = p.parseLine(input);
        if (!i.isValid())
            success = false;
        // _mbr := a; c := a;   --> should be valid
        resReg = "mbr";
        reg = "a";
        input = resReg + " := " + reg + "; c := a;";
        i = p.parseLine(input);
        if (!i.isValid())
            success = false;
        return success;
    }

    bool test_mar(parser &p)
    {
        std::cout << "  <T> MAR: ";
        // _mar := c;
        std::string resReg = "mar";
        std::string reg = "c";
        std::string input = resReg + " := " + reg + ";";
        instruction i = p.parseLine(input);
        auto code = i.getCode();
        dword correctCode = C << BUS_B_SH;
        correctCode |= YES << MAR_SH;
        if (!i.isValid())
            return false;
        if (code != correctCode)
            return false;
        // _mar := c; b := a + c;   --> should be valid
        resReg = "mar";
        reg = "c";
        std::string reg2 = "a";
        input = resReg + " := " + reg + "; b := " + reg2 + " + " + reg + ";";
        i = p.parseLine(input);
        if (!i.isValid())
            return false;
        // _mar := c; b := b + d;   --> should be invalid
        resReg = "mar";
        reg = "c";
        reg2 = "b";
        input = resReg + " := " + reg + "; b := " + reg2 + " + d;";
        i = p.parseLine(input);
        if (i.isValid())
            return false;
        return true;
    }

    bool test_isNumber_1(parser &p)
    {
        std::cout << "  <T> isNumber 1: ";

        std::string input = "12";

        auto result = p.isNumber(input);

        if (result)
            return true;
        else
            return false;
    }

    bool test_isNumber_2(parser &p)
    {
        std::cout << "  <T> isNumber 2: ";

        std::string input = "13A";

        auto result = p.isNumber(input);

        if (!result)
            return true;
        else
            return false;
    }

    bool test_isNumber_3(parser &p)
    {
        std::cout << "  <T> isNumber 3: ";

        std::string input = "012";

        auto result = p.isNumber(input);

        if (result)
            return true;
        else
            return false;
    }

    bool test_isNumber_4(parser &p)
    {
        std::cout << "  <T> isNumber 3: ";

        std::string input = "c12";

        auto result = p.isNumber(input);

        if (!result)
            return true;
        else
            return false;
    }

    bool test_toRegister_1(parser &p)
    {
        std::cout << "  <T> toRegister 1: ";

        std::string input = "a";

        auto result = p.toRegister(input);

        if (result == A)
            return true;
        else
            return false;
    }

    bool test_toRegister_2(parser &p)
    {
        std::cout << "  <T> toRegister 2: ";

        std::string input = "ab";

        auto result = p.toRegister(input);

        if (result == INVALID)
            return true;
        else
            return false;
    }

    bool test_toRegister_3(parser &p)
    {
        std::cout << "  <T> toRegister 3: ";

        std::string input = "amask 1";

        auto result = p.toRegister(input);

        if (result == INVALID)
            return true;
        else
            return false;
    }

    bool test_toRegister_4(parser &p)
    {
        std::cout << "  <T> toRegister 4: ";

        std::string input = "mask";

        auto result = p.toRegister(input);

        if (result == INVALID)
            return true;
        else
            return false;
    }
    
    bool test_arithmetic_1(parser &p)
    {
        std::cout << "  <T> Arithmetic 1: ";

        std::string input = "b";

        instruction inst;
        bool instMarker;

        auto result = p.arithmetic(inst, &instMarker, input);

        if (inst.getAlu() == ALU::POS_A)
            return true;
        else
            return false;
    }
    
    bool test_arithmetic_2(parser &p)
    {
        std::cout << "  <T> Arithmetic 2: ";

        std::string input = "a + b";

        instruction inst;
        bool instMarker;

        auto result = p.arithmetic(inst, &instMarker, input);

        if (inst.getAlu() == ALU::A_AND_B)
            return true;
        else
            return false;
    }
    
    bool test_arithmetic_3(parser &p)
    {
        std::cout << "  <T> Arithmetic 3: ";

        std::string input = "inv(a)";

        instruction inst;
        bool instMarker;

        auto result = p.arithmetic(inst, &instMarker, input);

        // Print the results
        std::cout << "Result: " << inst.getAlu() << std::endl;

        if (inst.getAlu() == ALU::NEG_A)
            return true;
        else
            return false;
    }
}
