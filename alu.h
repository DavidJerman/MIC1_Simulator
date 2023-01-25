//
// Created by david on 1/8/2023.
//

#ifndef HOMICSIM_ALU_H
#define HOMICSIM_ALU_H

#include "constants.h"

class alu {
public:
    alu();

    [[nodiscard]] bool getZ() const;

    [[nodiscard]] bool getN() const;

    void setA(word value);

    void setB(word value);

    void setOp(enum ALU newOp);

    [[nodiscard]] word wordOut();

private:
    word addOp(word a, word b);

    word andOp(word a, word b);

    word posOp(word a);

    word negOp(word a);

    bool flagZ;
    bool flagN;
    word A;
    word B;
    enum ALU op;
};


#endif //HOMICSIM_ALU_H
