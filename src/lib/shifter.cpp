//
// Created by pinkynyte on 1/25/23.
//

#include "shifter.h"

void shifter::set(SH shift)
{
    this->_shift = shift;
}

void shifter::wordIn(word value)
{
    this->_value = value;
}

/**
 * Shifts the word in the shifter based on the _shift _value - invalid _shift values return 0
 * @return the shifted word
 */
word shifter::wordOut()
{
    switch (_shift)
    {
    case SH::LEFT_SHIFT:
        return _value << 1;
    case SH::RIGHT_SHIFT:
        return _value >> 1;
    case SH::NO_SHIFT:
        return _value;
    default:
        return 0;
    }
}

void shifter::reset()
{
    _value = 0;
    _shift = SH::NO_SHIFT;
}
