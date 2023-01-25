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

    [[nodiscard]] int getAmux() const;

    void setAmux(int newAmux);

    [[nodiscard]] int getCond() const;

    void setCond(int newCond);

    [[nodiscard]] int getAlu() const;

    void setAlu(int newAlu);

    [[nodiscard]] int getSh() const;

    void setSh(int newSh);

    [[nodiscard]] int getMbr() const;

    void setMbr(int newMbr);

    [[nodiscard]] int getMar() const;

    void setMar(int newMar);

    [[nodiscard]] int getRd() const;

    void setRd(int newRd);

    [[nodiscard]] int getWr() const;

    void setWr(int newWr);

    [[nodiscard]] int getEnc() const;

    void setEnc(int newEnc);

    [[nodiscard]] int getBusC() const;

    void setBusC(int newBusC);

    [[nodiscard]] int getBusB() const;

    void setBusB(int newBusB);

    [[nodiscard]] int getBusA() const;

    void setBusA(int newBusA);

    [[nodiscard]] byte getAddress() const;

    void setAddress(byte newAddress);

    std::string toString() const;

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
