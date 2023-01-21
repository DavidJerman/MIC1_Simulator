//
// Created by david on 1/13/2023.
//

#include <iostream>
#include <algorithm>
#include <cstring>
#include "parser.h"

parser::parser() {
    initRegisterTable();
}

instruction parser::parse(const std::string &input) {
    // Covert to an instruction
    // Bits for checking if the property of an instruction has already been set
    bool instructionMarker[13]{false};

    // 1.1) resReg := leftReg + rightReg;
    // 1.2) resReg := leftReg;
    //   2) rd; / wr;
    //   3) goto 99;
    //   4) if n then goto 15;
    //   5) band(leftReg, rightReg)
    //   6) lshift(leftReg)
    //   7) rshift(leftReg)
    //   8) inv(leftReg)
    //   9) resReg := band(leftReg, rightReg);
    //  10) resReg := lshift(leftReg);
    //  11) resReg := rshift(leftReg);
    //  12) resReg := inv(leftReg);

    // Parsing
    std::stringstream lineStream(input);
    std::stringstream instructionStream;
    std::string nextLine;
    std::string token;
    instruction instruction;

    while (std::getline(lineStream, nextLine, ';')) {
        // Case 2.
        instructionStream.clear();
        instructionStream.str(nextLine);
        while (std::getline(instructionStream, token, ' ')) {
            if (token.substr(0, 2) == "rd")
            {
                if (instructionMarker[MARK::MRD] || instructionMarker[MARK::MWR])
                {
                    std::cout << "Error: cannot call read again after I/O operation!" << std::endl;
                    instruction.invalidate();
                    break;
                }
                instructionMarker[MARK::MRD] = true;
                instruction.setRd(ACTIVATE::YES);
                if (!instructionStream.eof())
                {
                    std::cout << "Error: invalid instruction!" << std::endl;
                    instruction.invalidate();
                    break;
                }
            }
            else if (token.substr(0, 2) == "wr")
            {
                if (instructionMarker[MARK::MRD] || instructionMarker[MARK::MWR])
                {
                    std::cout << "Error: cannot call write again after I/O operation!" << std::endl;
                    instruction.invalidate();
                    break;
                }
                instructionMarker[MARK::MWR] = true;
                instruction.setWr(ACTIVATE::YES);
                if (!instructionStream.eof())
                {
                    std::cout << "Error: invalid instruction!" << std::endl;
                    instruction.invalidate();
                    break;
                }
            }
            else if (token.substr(0, 4) == "goto")
            {
                if (instructionMarker[MARK::MADDR])
                {
                    std::cout << "Error: cannot call goto again after goto!" << std::endl;
                    instruction.invalidate();
                    break;
                }
                else
                {
                    instructionMarker[MARK::MCOND] = true;
                    instruction.setCond(COND::JUMP);
                }
                instructionMarker[MARK::MADDR] = true;
                std::getline(instructionStream, token, ' ');
                if (!isNumber(token))
                {
                    std::cout << "Error: goto must be followed by a number!" << std::endl;
                    instruction.invalidate();
                    break;
                } else {
                    instruction.setAddress(std::stoi(token));
                }
                if (!instructionStream.eof())
                {
                    std::cout << "Error: invalid instruction!" << std::endl;
                    instruction.invalidate();
                    break;
                }
            }
            else if (token.substr(0, 2) == "if")
            {
                if (instructionMarker[MARK::MCOND])
                {
                    std::cout << "Error: cannot call if again after if!" << std::endl;
                    instruction.invalidate();
                    break;
                }
                instructionMarker[MARK::MCOND] = true;
                std::getline(instructionStream, token, ' ');
                if (token == "n")
                {
                    instruction.setCond(COND::N_JUMP);
                }
                else if (token == "z")
                {
                    instruction.setCond(COND::Z_JUMP);
                }
                else
                {
                    std::cout << "Error: invalid/missing jump condition flag in if statement!" << std::endl;
                    instruction.invalidate();
                    break;
                }
                std::getline(instructionStream, token, ' ');
                if (token != "then")
                {
                    std::cout << "Error: invalid/missing then in if statement!" << std::endl;
                    instruction.invalidate();
                    break;
                }
                std::getline(instructionStream, token, ' ');
                if (token != "goto")
                {
                    std::cout << "Error: invalid/missing goto in if statement!" << std::endl;
                    instruction.invalidate();
                    break;
                }
                std::getline(instructionStream, token, ' ');
                if (!isNumber(token))
                {
                    std::cout << "Error: invalid jump address in if statement!" << std::endl;
                    instruction.invalidate();
                    break;
                }
                else
                {
                    instruction.setAddress(std::stoi(token));
                }
                if (!instructionStream.eof())
                {
                    std::cout << "Error: invalid instruction!" << std::endl;
                    instruction.invalidate();
                    break;
                }
            }
            else
            {
                // a := b + c;
                auto resReg = toRegister(token);
                if (resReg == INVALID)
                {
                    std::cout << "Error: invalid register!" << std::endl;
                    instruction.invalidate();
                    break;
                }
                if (instructionMarker[MARK::MC])
                {
                    std::cout << "Error: cannot assign value to register again!" << std::endl;
                    instruction.invalidate();
                    break;
                }
                else
                {
                    instructionMarker[MARK::MC] = true;
                    instruction.setBusC(resReg);
                }
                std::getline(instructionStream, token, ' ');
                if (token != ":=")
                {
                    std::cout << "Error: invalid assignment operator!" << std::endl;
                    instruction.invalidate();
                    break;
                }
                std::getline(instructionStream, token, ' ');
                // TODO: Mar and mbr and such should be checked here!
                // Option 1: register
                // Option 2: band, inv, rshift, lshift
                if (!strcmp(token.substr(0, 3).c_str(), "inv"))
                {
                    instruction.setAlu(ALU::NEG_A);
                    if (token.length() < 5 || token.substr(token.length() - 1, 1) != ")")
                    {
                        std::cout << "Error: invalid inv instruction! Please avoid any unnecessary spaces in band!" << std::endl;
                        instruction.invalidate();
                        break;
                    }
                    auto reg = toRegister(token.substr(4, token.length() - 5));
                    if (reg == INVALID)
                    {
                        std::cout << "Error: invalid register!" << std::endl;
                        instruction.invalidate();
                        break;
                    }
                    instruction.setBusA(reg);
                    if (!instructionStream.eof())
                    {
                        std::cout << "Error: invalid instruction!" << std::endl;
                        instruction.invalidate();
                        break;
                    }
                }
                else if (!strcmp(token.substr(0, 4).c_str(), "band"))
                {
                    instruction.setAlu(ALU::A_AND_B);
                    if (token.length() < 6)
                    {
                        std::cout << "Error: invalid band instruction! Please avoid any unnecessary spaces in band!" << std::endl;
                        instruction.invalidate();
                        break;
                    }
                    auto regLeft = toRegister(token.substr(5, token.length() - 6));
                    if (regLeft == INVALID)
                    {
                        std::cout << "Error: invalid register!" << std::endl;
                        instruction.invalidate();
                        break;
                    }
                    instruction.setBusA(regLeft);
                    std::getline(instructionStream, token, ' ');
                    auto regRight = toRegister(token.substr(0, token.length() - 1));
                    if (regRight == INVALID)
                    {
                        std::cout << "Error: invalid register!" << std::endl;
                        instruction.invalidate();
                        break;
                    }
                    instruction.setBusB(regRight);
                    if (!instructionStream.eof())
                    {
                        std::cout << "Error (band): invalid instruction!" << std::endl;
                        instruction.invalidate();
                        break;
                    }
                }
                else if (!strcmp(token.substr(0, 6).c_str(), "rshift"))
                {
                    instruction.setSh(SH::RIGHT_SHIFT);
                    std::getline(instructionStream, token, ' ');
                }
                else if (!strcmp(token.substr(0, 6).c_str(), "lshift"))
                {
                    instruction.setAlu(SH::LEFT_SHIFT);
                    std::getline(instructionStream, token, ' ');
                }
                else
                {
                    std::string expression = token;
                    while (std::getline(instructionStream, token, ' '))
                    {
                        expression += " " + token;
                    }
                    arithmeticPlus(instruction, instructionMarker, expression);
                }
            }
        }
    }
    return instruction;
}

bool parser::findCharAfterSpaces(const std::string &s, char c, int offset) {
    bool found {false};
    for (; offset < s.length(); offset++) {
        auto chr = s[offset];
        if (chr == c && found)
            return false;
        if (chr == c) {
            found = true;
            continue;
        }
        if (chr != ' ')
            return false;
    }
    return found;
}

bool parser::isNumber(const std::string &s) {
    auto res = std::all_of(s.begin(), s.end(), isdigit);
    return res;
}

REGISTER parser::toRegister(const std::string &s) {
    auto reg = registerTable.find(s);
    if (reg != registerTable.end())
        return (REGISTER)reg->second;
    return INVALID;
}

void parser::initRegisterTable() {
    registerTable.insert({"pc", REGISTER::PC});
    registerTable.insert({"ac", REGISTER::AC});
    registerTable.insert({"sp", REGISTER::SP});
    registerTable.insert({"ir", REGISTER::IR});
    registerTable.insert({"tir", REGISTER::TIR});
    registerTable.insert({"0", REGISTER::Z});
    registerTable.insert({"1", REGISTER::P1});
    registerTable.insert({"(-1)", REGISTER::N1});
    registerTable.insert({"-1", REGISTER::N1});
    registerTable.insert({"amask", REGISTER::AMASK});
    registerTable.insert({"smask", REGISTER::SMASK});
    registerTable.insert({"a", REGISTER::A});
    registerTable.insert({"b", REGISTER::B});
    registerTable.insert({"c", REGISTER::C});
    registerTable.insert({"d", REGISTER::D});
    registerTable.insert({"e", REGISTER::E});
    registerTable.insert({"f", REGISTER::F});
    registerTable.insert({"mar", REGISTER::MAR});
    registerTable.insert({"mbr", REGISTER::MBR});
    registerTable.insert({"alu", REGISTER::ALU});
}

bool parser::arithmeticPlus(instruction &instruction, bool *instructionMarker, const std::string &expression) {
    std::stringstream expressionStream(expression);
    std::string token;
    std::getline(expressionStream, token, ' ');
    auto leftReg = toRegister(token);
    if (leftReg == INVALID)
    {
        std::cout << "Error: invalid register!" << std::endl;
        instruction.invalidate();
        return false;
    }
    else
    {
        instruction.setBusA(leftReg);
    }
    // End if there is no additional operation
    if (expressionStream.eof())
    {
        return true;
    }
    // Check for plus operation
    std::getline(expressionStream, token, ' ');
    if (token == "+")
    {
        instruction.setAlu(ALU::A_PLUS_B);
    }
    else
    {
        std::cout << "Error: invalid ALU operation!" << std::endl;
        instruction.invalidate();
        return false;
    }
    std::getline(expressionStream, token, ' ');
    auto rightReg = toRegister(token);
    if (rightReg == INVALID)
    {
        std::cout << "Error: invalid register!" << std::endl;
        instruction.invalidate();
        return false;
    }
    else
    {
        instruction.setBusB(rightReg);
    }
    if (!expressionStream.eof())
    {
        std::cout << "Error: invalid instruction!" << std::endl;
        instruction.invalidate();
        return false;
    }
    return true;
}
