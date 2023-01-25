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

    void reset();

    [[nodiscard]] ACTIVATE getSetMar() const;

    void setSetMar(ACTIVATE setMar);

    [[nodiscard]] ACTIVATE getSetMbr() const;

    void setSetMbr(ACTIVATE setMbr);

    [[nodiscard]] ACTIVATE getRead() const;

    void setRd(ACTIVATE read);

    [[nodiscard]] ACTIVATE getWrite() const;

    void setWr(ACTIVATE write);

private:
    word read_word(word address);
    void write_word(word address, word value);

    // Memory is 4K
    word _mem[MEM_SIZE]{};

    word _mar; // Memory Address Register --> Mar should not be changed while the memory is busy
    word _mbr; // Memory Data Register

    enum ACTIVATE _setMar;
    enum ACTIVATE _setMbr;
    enum ACTIVATE _read;
    enum ACTIVATE _write;

    IO_STATE _ioState = IO_STATE::READY; // 0 = not busy, 1 = busy, 2 = ready to read/write
    IO_MODE _ioMode = IO_MODE::READ;
};


#endif //HOMICSIM_MEMORY_H
