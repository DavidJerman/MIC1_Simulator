//
// Created by david on 1/13/2023.
//

#include <iostream>
#include <algorithm>
#include <cstring>
#include "parser.h"

parser::parser()
{
    initRegisterTable();
}

instruction parser::parseLine(const std::string &input)
{
    // Covert to an instruction
    // Bits for checking if the property of an instruction has already been set
    bool instructionMarker[13]{false};
    bool fixedBusOrder = false;

    // 1.1) resReg := leftReg + rightReg;
    // 1.2) resReg := leftReg;
    //   2) rd; / wr;
    //   3) goto 99;
    //   4) if n then goto 15;
    //   5) band(leftReg, rightReg)   ---> alu := band(leftReg, rightReg)
    //   6) lshift(leftReg)    ---> alu := lshift(leftReg)
    //   7) rshift(leftReg)    ---> alu := rshift(leftReg)
    //   8) inv(leftReg)    ---> alu := inv(leftReg)
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

    // TODO: MBR has to also set ALU

    while (std::getline(lineStream, nextLine, ';'))
    {
        nextLine = trim(nextLine);
        if (nextLine[0] == '#')
            return instruction;
        // Case 2.
        instructionStream.clear();
        instructionStream.str(nextLine);
        while (std::getline(instructionStream, token, ' '))
        {
            token = trim(token);
            if (token.substr(0, 2) == "rd")
            {
                if (instructionMarker[MARK::MRD] || instructionMarker[MARK::MWR])
                {
#ifndef TESTING
                    std::cerr << "Error: cannot call read again after I/O operation!" << std::endl;
#endif
                    instruction.invalidate();
                    break;
                }
                instructionMarker[MARK::MRD] = true;
                instruction.setRd(ACTIVATE::YES);
                if (!instructionStream.eof())
                {
#ifndef TESTING
                    std::cerr << "Error: invalid instruction!" << std::endl;
#endif
                    instruction.invalidate();
                    break;
                }
            }
            else if (token.substr(0, 2) == "wr")
            {
                if (instructionMarker[MARK::MRD] || instructionMarker[MARK::MWR])
                {
#ifndef TESTING
                    std::cerr << "Error: cannot call write again after I/O operation!" << std::endl;
#endif
                    instruction.invalidate();
                    break;
                }
                instructionMarker[MARK::MWR] = true;
                instruction.setWr(ACTIVATE::YES);
                if (!instructionStream.eof())
                {
#ifndef TESTING
                    std::cerr << "Error: invalid instruction!" << std::endl;
#endif
                    instruction.invalidate();
                    break;
                }
            }
            else if (token.substr(0, 4) == "goto")
            {
                if (instructionMarker[MARK::MADDR])
                {
#ifndef TESTING
                    std::cerr << "Error: cannot call goto again after goto!" << std::endl;
#endif
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
#ifndef TESTING
                    std::cerr << "Error: goto must be followed by a number!" << std::endl;
#endif
                    instruction.invalidate();
                    break;
                }
                else
                {
                    instruction.setAddress(std::stoi(token));
                }
                if (!instructionStream.eof())
                {
#ifndef TESTING
                    std::cerr << "Error: invalid instruction!" << std::endl;
#endif
                    instruction.invalidate();
                    break;
                }
            }
            else if (token.substr(0, 2) == "if")
            {
                if (instructionMarker[MARK::MCOND])
                {
#ifndef TESTING
                    std::cerr << "Error: cannot call if again after if!" << std::endl;
#endif
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
#ifndef TESTING
                    std::cerr << "Error: invalid/missing jump condition flag in if statement!" << std::endl;
#endif
                    instruction.invalidate();
                    break;
                }
                std::getline(instructionStream, token, ' ');
                if (token != "then")
                {
#ifndef TESTING
                    std::cerr << "Error: invalid/missing then in if statement!" << std::endl;
#endif
                    instruction.invalidate();
                    break;
                }
                std::getline(instructionStream, token, ' ');
                if (token != "goto")
                {
#ifndef TESTING
                    std::cerr << "Error: invalid/missing goto in if statement!" << std::endl;
#endif
                    instruction.invalidate();
                    break;
                }
                std::getline(instructionStream, token, ' ');
                if (!isNumber(token))
                {
#ifndef TESTING
                    std::cerr << "Error: invalid jump _address in if statement!" << std::endl;
#endif
                    instruction.invalidate();
                    break;
                }
                else
                {
                    instruction.setAddress(std::stoi(token));
                    instructionMarker[MARK::MADDR] = true;
                }
                if (!instructionStream.eof())
                {
#ifndef TESTING
                    std::cerr << "Error: invalid instruction!" << std::endl;
#endif
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
#ifndef TESTING
                    std::cerr << "Error: invalid register!" << std::endl;
#endif
                    instruction.invalidate();
                    break;
                }

                if (instructionMarker[MARK::MC] || instructionMarker[MARK::MENC])
                {
#ifndef TESTING
                    std::cerr << "Error: cannot assign _value to register again!" << std::endl;
#endif
                    instruction.invalidate();
                    break;
                }
                else if ((REGISTER)resReg == MBR)
                {
                    instructionMarker[MARK::MMBR] = true;
                    instruction.setMbr(ACTIVATE::YES);
                }
                else if ((REGISTER)resReg == MAR)
                {
                    instructionMarker[MARK::MMAR] = true;
                    instruction.setMar(ACTIVATE::YES);
                    // This rule will be an exception, since _mar has to be processed differently
                    std::getline(instructionStream, token, ' ');
                    token = trim(token);
                    if (token != ":=")
                    {
#ifndef TESTING
                        std::cerr << "Error: invalid assignment operator!" << std::endl;
#endif
                        instruction.invalidate();
                        break;
                    }
                    std::getline(instructionStream, token, ' ');
                    auto reg = toRegister(token);
                    if (reg == INVALID)
                    {
#ifndef TESTING
                        std::cerr << "Error: invalid register!" << std::endl;
#endif
                        instruction.invalidate();
                        break;
                    }
                    if (instructionMarker[MARK::MB] && instruction.getBusB() != reg)
                    {
#ifndef TESTING
                        std::cerr << "Error: bus B error! Make sure the register used with mar assignment appears on the right in any other assignment!" << std::endl;
#endif
                        instruction.invalidate();
                        break;
                    }
                    instructionMarker[MARK::MB] = true;
                    instruction.setBusB(reg);
                    break;
                }
                else
                {
                    instructionMarker[MARK::MC] = true;
                    instructionMarker[MARK::MENC] = true;
                    instruction.setBusC(resReg);
                    instruction.setEnc(ACTIVATE::YES);
                }

                std::getline(instructionStream, token, ' ');
                if (token != ":=")
                {
#ifndef TESTING
                    std::cerr << "Error: invalid assignment operator!" << std::endl;
#endif
                    instruction.invalidate();
                    break;
                }

                std::getline(instructionStream, token, ' ');
                // TODO: Mar and _mbr and such should be checked here!
                // Option 1: register
                // Option 2: band, inv, rshift, lshift
                if (!strcmp(token.substr(0, 6).c_str(), "rshift"))
                {
                    if (instructionMarker[MARK::MSH])
                    {
#ifndef TESTING
                        std::cerr << "Error: cannot call _shift again after _shift!" << std::endl;
#endif
                        instruction.invalidate();
                        break;
                    }
                    instruction.setSh(SH::RIGHT_SHIFT);
                    instructionMarker[MARK::MSH] = true;
                    std::string expression = token.substr(7, token.length() - 7);
                    while (std::getline(instructionStream, token, ' '))
                    {
                        expression += " " + token;
                    }
                    expression = expression.substr(0, expression.length() - 1);
                    auto res = arithmetic(instruction, instructionMarker, expression);
                    if (!res)
                    {
                        instruction.invalidate();
                        break;
                    }
                }
                else if (!strcmp(token.substr(0, 6).c_str(), "lshift"))
                {
                    if (instructionMarker[MARK::MSH])
                    {
#ifndef TESTING
                        std::cerr << "Error: cannot call _shift again after _shift!" << std::endl;
#endif
                        instruction.invalidate();
                        break;
                    }
                    instruction.setSh(SH::LEFT_SHIFT);
                    instructionMarker[MARK::MSH] = true;
                    std::string expression = token.substr(7, token.length() - 7);
                    while (std::getline(instructionStream, token, ' '))
                    {
                        expression += " " + token;
                    }
                    expression = expression.substr(0, expression.length() - 1);
                    auto res = arithmetic(instruction, instructionMarker, expression);
                    if (!res)
                    {
                        instruction.invalidate();
                        break;
                    }
                }
                else
                {
                    auto expression = token;
                    while (std::getline(instructionStream, token, ' '))
                    {
                        expression += " " + token;
                    }
                    auto res = arithmetic(instruction, instructionMarker, expression);
                    if (!res)
                    {
                        instruction.invalidate();
                        break;
                    }
                }
            }
        }
    }

    // Idea: process _mar and _mbr assignments separately

    return instruction;
}

bool parser::findCharAfterSpaces(const std::string &s, char c, int offset)
{
    bool found{false};
    for (; offset < s.length(); offset++)
    {
        auto chr = s[offset];
        if (chr == c && found)
            return false;
        if (chr == c)
        {
            found = true;
            continue;
        }
        if (chr != ' ')
            return false;
    }
    return found;
}

bool parser::isNumber(const std::string &s)
{
    auto res = std::all_of(s.begin(), s.end(), isdigit);
    return res;
}

REGISTER parser::toRegister(const std::string &s)
{
    auto reg = registerTable.find(s);
    if (reg != registerTable.end())
        return (REGISTER)reg->second;
    return INVALID;
}

void parser::initRegisterTable()
{
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

bool parser::arithmetic(instruction &instruction, bool *instructionMarker, const std::string &expression)
{
    std::stringstream instructionStream{expression};
    std::string token;
    std::getline(instructionStream, token, ' ');

    if (!strcmp(token.substr(0, 3).c_str(), "inv"))
    {
        instruction.setAlu(ALU::NEG_A);
        if (token.length() < 5 || token.substr(token.length() - 1, 1) != ")")
        {
#ifndef TESTING
            std::cerr << "Error: invalid inv instruction! Please avoid any unnecessary spaces in band!" << std::endl;
#endif
            instruction.invalidate();
            return false;
        }
        auto reg = toRegister(token.substr(4, token.length() - 5));
        if (reg == INVALID || reg == REGISTER::MAR)
        {
#ifndef TESTING
            std::cerr << "Error: invalid register!" << std::endl;
#endif
            instruction.invalidate();
            return false;
        }
        if (reg == REGISTER::MBR)
        {
            instruction.setAmux(AMUX::MBR_LATCH);
        }
        else
        {
            setA(instruction, instructionMarker, reg);
            instruction.setAmux(AMUX::A_LATCH);
        }
        if (!instructionStream.eof())
        {
#ifndef TESTING
            std::cerr << "Error: invalid instruction!" << std::endl;
#endif
            instruction.invalidate();
            return false;
        }
    }
    else if (!strcmp(token.substr(0, 4).c_str(), "band"))
    {
        instruction.setAlu(ALU::A_AND_B);
        if (token.length() < 6)
        {
#ifndef TESTING
            std::cerr << "Error: invalid band instruction! Please avoid any unnecessary spaces in band!" << std::endl;
#endif
            instruction.invalidate();
            return false;
        }
        auto regLeft = toRegister(token.substr(5, token.length() - 6));
        if (regLeft == INVALID || regLeft == REGISTER::MAR)
        {
#ifndef TESTING
            std::cerr << "Error: invalid register!" << std::endl;
#endif
            instruction.invalidate();
            return false;
        }
        if (regLeft == REGISTER::MBR)
        {
            instruction.setAmux(AMUX::MBR_LATCH);
        }
        else
        {
            setA(instruction, instructionMarker, regLeft);
            instruction.setAmux(AMUX::A_LATCH);
        }
        std::getline(instructionStream, token, ' ');
        auto regRight = toRegister(token.substr(0, token.length() - 1));
        if (regRight == INVALID || regRight == REGISTER::MAR || regRight == REGISTER::MBR)
        {
#ifndef TESTING
            std::cerr << "Error: invalid register or mar/mbr was used (mbr should be used as the first parameter in assignment)!" << std::endl;
#endif
            instruction.invalidate();
            return false;
        }
        setB(instruction, instructionMarker, regRight);
        if (!instructionStream.eof())
        {
#ifndef TESTING
            std::cerr << "Error (band): invalid instruction!" << std::endl;
#endif
            instruction.invalidate();
            return false;
        }
    }
    else
    {
        std::string expr = token;
        while (std::getline(instructionStream, token, ' '))
        {
            expr += " " + token;
        }
        auto res = arithmeticPlus(instruction, instructionMarker, expr);
        if (!res)
        {
            return false;
        }
    }
    return true;
}

bool parser::arithmeticPlus(instruction &instruction, bool *instructionMarker, const std::string &expression)
{
    std::stringstream expressionStream(expression);
    std::string token;
    std::getline(expressionStream, token, ' ');
    auto leftReg = toRegister(token);
    if (leftReg == INVALID || leftReg == REGISTER::MAR)
    {
#ifndef TESTING
        std::cerr << "Error: invalid register!" << std::endl;
#endif
        instruction.invalidate();
        return false;
    }
    if (leftReg == REGISTER::MBR)
    {
        instruction.setAmux(AMUX::MBR_LATCH);
    }
    else
    {
        auto res = setA(instruction, instructionMarker, leftReg);
        if (!res)
        {
            return false;
        }
        instruction.setAmux(AMUX::A_LATCH);
    }
    // End if there is no additional operation
    if (expressionStream.eof())
    {
        instruction.setAlu(ALU::POS_A);
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
#ifndef TESTING
        std::cerr << "Error: invalid ALU operation!" << std::endl;
#endif
        instruction.invalidate();
        return false;
    }
    std::getline(expressionStream, token, ' ');
    auto rightReg = toRegister(token);
    if (rightReg == INVALID || rightReg == REGISTER::MAR || rightReg == REGISTER::MBR)
    {
#ifndef TESTING
        std::cerr << "Error: invalid register!" << std::endl;
#endif
        instruction.invalidate();
        return false;
    }
    else
    {
        auto res = setB(instruction, instructionMarker, rightReg);
        if (!res)
        {
            return false;
        }
    }
    if (!expressionStream.eof())
    {
#ifndef TESTING
        std::cerr << "Error: invalid instruction!" << std::endl;
#endif
        instruction.invalidate();
        return false;
    }
    return true;
}

bool parser::setA(instruction &instruction, bool *instructionMarker, const REGISTER &reg)
{
    if (instructionMarker[MARK::MA] && instruction.getBusA() != reg)
    {
#ifndef TESTING
        std::cerr << "Error: cannot call setA again with different register!" << std::endl;
#endif
        return false;
    }
    instructionMarker[MARK::MA] = true;
    instruction.setBusA(reg);
    return true;
}

bool parser::setB(instruction &instruction, bool *instructionMarker, const REGISTER &reg)
{
    if (instructionMarker[MARK::MB] && instruction.getBusB() != reg)
    {
#ifndef TESTING
        std::cerr << "Error: cannot call setB again with different register!" << std::endl;
#endif
        return false;
    }
    instructionMarker[MARK::MB] = true;
    instruction.setBusB(reg);
    return true;
}

std::vector<instruction> parser::parseFile(const std::string &path)
{
    std::ifstream stream;
    stream.open(path);
    if (!stream.is_open())
    {
#ifndef TESTING
        std::cerr << "Error: cannot open file!" << std::endl;
#endif
        return {};
    }
    return parseProgram(stream);
}

std::vector<instruction> parser::parseProgram(std::istream &stream)
{
    std::vector<instruction> instructions;
    std::string token;
    int lineCounter = 0;
    int instructionCounter = 0;
    while (std::getline(stream, token))
    {
        std::stringstream tokenStream(token);
        std::getline(tokenStream, token, ':');
        auto label = trim(token);
        if (label[0] == '#')
        {
            lineCounter++;
            continue;
        }
        if (label.empty() || instructionCounter != std::stoi(label))
        {
#ifndef TESTING
            std::cerr << "Error: invalid label in line " << lineCounter << "!" << std::endl;
#endif
            return {};
        }
        std::getline(tokenStream, token);
        auto instruction = parseLine(token);
        if (instruction.isValid())
        {
            instructions.push_back(instruction);
            instructionCounter++;
        }
        else
        {
#ifndef TESTING
            std::cerr << "Error: invalid instruction in line " << lineCounter << "!" << std::endl;
#endif
            return {};
        }
        lineCounter++;
    }
    return instructions;
}
