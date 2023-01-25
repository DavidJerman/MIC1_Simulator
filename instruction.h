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
    instruction() = default;

    explicit instruction(dword value);

    // Copy constructor
    instruction(const instruction& other);

    // Move constructor
    instruction(instruction&& other) noexcept;

    void setCode(dword value);

    [[nodiscard]] dword getCode() const;

    [[nodiscard]] bool isValid() const;

    void invalidate();

    [[nodiscard]] enum AMUX getAmux() const;

    void setAmux(enum AMUX newAmux);

    [[nodiscard]] enum COND getCond() const;

    void setCond(enum COND newCond);

    [[nodiscard]] enum ALU getAlu() const;

    void setAlu(enum ALU newAlu);

    [[nodiscard]] enum SH getSh() const;

    void setSh(enum SH newSh);

    [[nodiscard]] enum ACTIVATE getMbr() const;

    void setMbr(enum ACTIVATE newMbr);

    [[nodiscard]] enum ACTIVATE getMar() const;

    void setMar(enum ACTIVATE newMar);

    [[nodiscard]] enum ACTIVATE getRd() const;

    void setRd(enum ACTIVATE newRd);

    [[nodiscard]] enum ACTIVATE getWr() const;

    void setWr(enum ACTIVATE newWr);

    [[nodiscard]] enum ACTIVATE getEnc() const;

    void setEnc(enum ACTIVATE newEnc);

    [[nodiscard]] REGISTER getBusC() const;

    void setBusC(REGISTER newBusC);

    [[nodiscard]] REGISTER getBusB() const;

    void setBusB(REGISTER newBusB);

    [[nodiscard]] REGISTER getBusA() const;

    void setBusA(REGISTER newBusA);

    [[nodiscard]] byte getAddress() const;

    void setAddress(byte newAddress);

    [[nodiscard]] std::string toString() const;

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
};


#endif //HOMICSIM_INSTRUCTION_H
