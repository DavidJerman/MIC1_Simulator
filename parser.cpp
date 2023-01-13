//
// Created by david on 1/13/2023.
//

#include <iostream>
#include "parser.h"

parser::parser() {
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

instruction parser::parse(const std::string &input) {
    // Covert to an instruction
    // Bits for checking if the property of an instruction has already been set
    bool instructionMarker[12]{false};

    // Control variables
    int seqCount{0};
    int resReg{0};
    int leftReg{0};
    int rightReg{0};
    bool band;
    bool lshift;
    bool rshift;

    // 1.1) resReg := leftReg + rightReg;
    // 1.2) resReg := leftReg;
    //   2) rd; / wr;
    //   3) goto 99;
    //   4) if n then goto 15;
    //   5) band(leftReg, rightReg)
    //   6) lshift(leftReg)
    //   7) rshift(leftReg)
    //   8) inv(leftReg)

    // Parsing
    std::stringstream stream(input);
    std::string next;
    instruction instruction;

    while (std::getline(stream, next, ' ')) {
        // Case 2.
        if (next.substr(0, 2) == "rd")
        {
            if (instructionMarker[MARK::MRD] || instructionMarker[MARK::MWR])
            {
                std::cout << "Error: cannot call read again after I/O operation!" << std::endl;
                instruction.invalidate();
                break;
            }
            instructionMarker[MARK::MRD] = true;
            instruction.setRd(ACTIVATE::YES);
            if (!findCharAfterSpaces(next, ';', 2))
            {
                instruction.invalidate();
                break;
            }
        }
        else if (next.substr(0, 2) == "wr")
        {
            if (instructionMarker[MARK::MRD] || instructionMarker[MARK::MWR])
            {
                std::cout << "Error: cannot call write again after I/O operation!" << std::endl;
                instruction.invalidate();
                break;
            }
            instructionMarker[MARK::MWR] = true;
            instruction.setWr(ACTIVATE::YES);
            if (!findCharAfterSpaces(next, ';', 2))
            {
                instruction.invalidate();
                break;
            }
        }
        else if (next.substr(0, 5) == "goto")
        {
            if (instructionMarker[MARK::MADDR])
            {
                std::cout << "Error: cannot call goto again after goto!" << std::endl;
                instruction.invalidate();
                break;
            }
            instructionMarker[MARK::MADDR] = true;
            std::getline(stream, next, ' ');
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
