//
// Created by pinkynyte on 1/25/23.
//

#ifndef HOMICSIM_AMUX_H
#define HOMICSIM_AMUX_H

#include "constants.h"

class amux {
public:
    amux() = default;

    void setA(word value);

    void setMBR(word value);

    void set(AMUX newSel);

    [[nodiscard]] word wordOut() const;

private:
    word a;
    word mbr;
    enum AMUX sel;
};


#endif //HOMICSIM_AMUX_H
