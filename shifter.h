//
// Created by pinkynyte on 1/25/23.
//

#ifndef HOMICSIM_SHIFTER_H
#define HOMICSIM_SHIFTER_H

#include "constants.h"

class shifter {
public:
    shifter() = default;

    void set(SH shift);

    void wordIn(word value);

    word wordOut();

    void reset();

private:
    word _value;
    enum SH _shift;
};


#endif //HOMICSIM_SHIFTER_H
