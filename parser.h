//
// Created by david on 1/13/2023.
//

#ifndef HOMICSIM_PARSER_H
#define HOMICSIM_PARSER_H

#include <string>
#include <sstream>
#include <map>
#include "instruction.h"

class parser {
public:
    parser();

    instruction parse(const std::string& input);

private:
    static bool findCharAfterSpaces(const std::string &s, char c, int offset);

    static bool isNumber(const std::string &s);

    REGISTER toRegister(const std::string &s);

    void initRegisterTable();

    bool arithmeticPlus(instruction &instruction, bool instructionMarker[13], const std::string &expression);

    std::map<std::string, int> registerTable {};
};


#endif //HOMICSIM_PARSER_H