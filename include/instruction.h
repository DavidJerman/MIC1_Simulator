//
// Created by pinkynyte on 1/12/23.
//

#ifndef HOMICSIM_INSTRUCTION_H
#define HOMICSIM_INSTRUCTION_H

#include <string>
#include <sstream>
#include "constants.h"

class instruction {
public:
    instruction();

    explicit instruction(dword value);

    // Copy constructor
    instruction(const instruction& other);

    // Move constructor
    instruction(instruction&& other) noexcept;

    // Copy assignment operator
    instruction& operator=(const instruction& other);

    void setCode(dword value);

    dword getCode() const;

    bool isValid() const;

    void invalidate();

    enum AMUX getAmux() const;

    void setAmux(enum AMUX newAmux);

    enum COND getCond() const;

    void setCond(enum COND newCond);

    enum ALU getAlu() const;

    void setAlu(enum ALU newAlu);

    enum SH getSh() const;

    void setSh(enum SH newSh);

    enum ACTIVATE getMbr() const;

    void setMbr(enum ACTIVATE newMbr);

    enum ACTIVATE getMar() const;

    void setMar(enum ACTIVATE newMar);

    enum ACTIVATE getRd() const;

    void setRd(enum ACTIVATE newRd);

    enum ACTIVATE getWr() const;

    void setWr(enum ACTIVATE newWr);

    enum ACTIVATE getEnc() const;

    void setEnc(enum ACTIVATE newEnc);

    REGISTER getBusC() const;

    void setBusC(REGISTER newBusC);

    REGISTER getBusB() const;

    void setBusB(REGISTER newBusB);

    REGISTER getBusA() const;

    void setBusA(REGISTER newBusA);

    byte getAddress() const;

    void setAddress(byte newAddress);

    std::string toString() const;

    unsigned int getId() const;

    void setId(unsigned int id);

private:
    int amux{};
    int cond{};
    int alu{};
    int sh{};
    int mbr{};
    int mar{};
    int rd{};
    int wr{};
    int enc{};
    int busC{};
    int busB{};
    int busA{};
    byte address{};

    bool valid{};
    unsigned int ID{};
};


#endif //HOMICSIM_INSTRUCTION_H
