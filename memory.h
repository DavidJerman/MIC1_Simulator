//
// Created by david on 1/7/2023.
//

#ifndef HOMICSIM_MEMORY_H
#define HOMICSIM_MEMORY_H

#include "constants.h"
#include "exceptions.h"

class memory {
public:
    memory();
    ~memory();

    void read();
    void write();

    [[nodiscard]] word getMbr() const;
    void setMbr(word _mbr);
    void setMar(word _mar);

private:
    word read_word(word address);
    void write_word(word address, word value);

    // Memory is 4K
    word mem[MEM_SIZE]{};

    word mar; // Memory Address Register --> Mar should not be changed while the memory is busy
    word mbr; // Memory Data Register

    IO_STATE io_state = IO_STATE::READY; // 0 = not busy, 1 = busy, 2 = ready to read/write
    IO_MODE io_mode = IO_MODE::READ;
};


#endif //HOMICSIM_MEMORY_H
