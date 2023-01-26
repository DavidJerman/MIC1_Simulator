//
// Created by pinkynyte on 1/26/23.
//

#ifndef HOMICSIM_GUI_H
#define HOMICSIM_GUI_H

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "simulator.h"
#include "constants.h"

class gui : public olc::PixelGameEngine {
public:
    gui()
    {
        sAppName = "Horizontal Micro-Architecture Simulator";
        sim.reset();
    }

    bool OnUserCreate() override
    {
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        return true;
    }

private:
    simulator sim;
};


#endif //HOMICSIM_GUI_H
