//
// Created by david on 1/7/2023.
//

#ifndef HOMICSIM_CONSTANTS_H
#define HOMICSIM_CONSTANTS_H

typedef unsigned short word;

#define MEM_SIZE 4096

enum class IO_MODE {
    READ,
    WRITE
};

enum class IO_STATE {
    BUSY,
    READY
};

#endif //HOMICSIM_CONSTANTS_H
