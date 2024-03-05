//
// Created by pinkynyte on 1/25/23.
//

#include "amux.h"

void amux::setA(word value)
{
    a = value;
}

void amux::setMBR(word value)
{
    mbr = value;
}

void amux::set(AMUX newSel)
{
    this->sel = newSel;
}

word amux::wordOut() const
{
    return sel == AMUX::MBR_LATCH ? mbr : a;
}

void amux::reset()
{
    a = 0;
    mbr = 0;
    sel = AMUX::A_LATCH;
}
