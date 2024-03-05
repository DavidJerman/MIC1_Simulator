//
// Created by pinkynyte on 1/12/23.
//

#include "instruction.h"

instruction::instruction()
{
    amux = 0;
    cond = 0;
    alu = 0;
    sh = 0;
    mbr = 0;
    mar = 0;
    rd = 0;
    wr = 0;
    enc = 0;
    busC = 0;
    busB = 0;
    busA = 0;
    address = 0;
    valid = true;
}

instruction::instruction(dword value)
{
    setCode(value);
}

void instruction::setCode(dword value)
{
    auto cast = (int)value;
    address = (cast >> ADDRESS_SH) & 0xFF;
    busA = (cast >> BUS_A_SH) & 0XF;
    busB = (cast >> BUS_B_SH) & 0XF;
    busC = (cast >> BUS_C_SH) & 0XF;
    enc = (cast >> ENC_SH) & 0X1;
    wr = (cast >> WR_SH) & 0X1;
    rd = (cast >> RD_SH) & 0X1;
    mar = (cast >> MAR_SH) & 0X1;
    mbr = (cast >> MBR_SH) & 0X1;
    sh = (cast >> SH_SH) & 0X3;
    alu = (cast >> ALU_SH) & 0X3;
    cond = (cast >> COND_SH) & 0X3;
    amux = (cast >> AMUX_SH) & 0X1;
}

dword instruction::getCode() const
{
    return (dword)(amux << AMUX_SH | cond << COND_SH | alu << ALU_SH | sh << SH_SH | mbr << MBR_SH | mar << MAR_SH |
                   rd << RD_SH | wr << WR_SH | enc << ENC_SH | busC << BUS_C_SH | busB << BUS_B_SH | busA << BUS_A_SH |
                   address << ADDRESS_SH);
}

bool instruction::isValid() const
{
    return valid;
}

void instruction::invalidate()
{
    valid = false;
}

enum AMUX instruction::getAmux() const
{
    return (enum AMUX)amux;
}

void instruction::setAmux(enum AMUX newAmux)
{
    instruction::amux = newAmux;
}

enum COND instruction::getCond() const
{
    return (enum COND)cond;
}

void instruction::setCond(enum COND newCond)
{
    instruction::cond = newCond;
}

enum ALU instruction::getAlu() const
{
    return (enum ALU)alu;
}

void instruction::setAlu(enum ALU newAlu)
{
    instruction::alu = newAlu;
}

enum SH instruction::getSh() const
{
    return (enum SH)sh;
}

void instruction::setSh(enum SH newSh)
{
    instruction::sh = newSh;
}

enum ACTIVATE instruction::getMbr() const
{
    return (enum ACTIVATE)mbr;
}

void instruction::setMbr(enum ACTIVATE newMbr)
{
    instruction::mbr = newMbr;
}

enum ACTIVATE instruction::getMar() const
{
    return (enum ACTIVATE)mar;
}

void instruction::setMar(enum ACTIVATE newMar)
{
    instruction::mar = newMar;
}

enum ACTIVATE instruction::getRd() const
{
    return (enum ACTIVATE)rd;
}

void instruction::setRd(enum ACTIVATE newRd)
{
    instruction::rd = newRd;
}

enum ACTIVATE instruction::getWr() const
{
    return (enum ACTIVATE)wr;
}

void instruction::setWr(enum ACTIVATE newWr)
{
    instruction::wr = newWr;
}

enum ACTIVATE instruction::getEnc() const
{
    return (enum ACTIVATE)enc;
}

void instruction::setEnc(enum ACTIVATE newEnc)
{
    instruction::enc = newEnc;
}

REGISTER instruction::getBusC() const
{
    return (REGISTER)busC;
}

void instruction::setBusC(REGISTER newBusC)
{
    instruction::busC = newBusC;
}

REGISTER instruction::getBusB() const
{
    return (REGISTER)busB;
}

void instruction::setBusB(REGISTER newBusB)
{
    instruction::busB = newBusB;
}

REGISTER instruction::getBusA() const
{
    return (REGISTER)busA;
}

void instruction::setBusA(REGISTER newBusA)
{
    instruction::busA = newBusA;
}

byte instruction::getAddress() const
{
    return address;
}

void instruction::setAddress(byte newAddress)
{
    instruction::address = newAddress;
}

std::string instruction::toString() const
{
    std::stringstream ss;
    ss << "Amux: " << (amux == AMUX::A_LATCH ? "A Latch" : "MBR") << std::endl;
    ss << "Cond: " << (cond == COND::JUMP ? "Always Jump" : cond == COND::NO_JUMP ? "No Jump"
                                                        : cond == COND::N_JUMP    ? "N Jump"
                                                                                  : "Z Jump")
       << std::endl;
    ss << "Alu: " << (alu == ALU::A_PLUS_B ? "+" : alu == ALU::A_AND_B ? "&"
                                               : alu == ALU::POS_A     ? "Pos A"
                                                                       : "Neg A")
       << std::endl;
    ss << "Sh: " << (sh == SH::NO_SHIFT ? "No Shift" : sh == SH::LEFT_SHIFT ? "Left Shift"
                                                   : sh == SH::RIGHT_SHIFT  ? "Right Shift"
                                                                            : "Invalid Shift")
       << std::endl;
    ss << "Mbr: " << (mbr == YES ? "Yes" : "No") << std::endl;
    ss << "Mar: " << (mar == YES ? "Yes" : "No") << std::endl;
    ss << "Rd: " << (rd == YES ? "Yes" : "No") << std::endl;
    ss << "Wr: " << (wr == YES ? "Yes" : "No") << std::endl;
    ss << "Enc: " << (enc == YES ? "Yes" : "No") << std::endl;
    ss << "Bus C: "
       << "0x" << std::hex << (int)busC << std::endl;
    ss << "Bus B: "
       << "0x" << std::hex << (int)busB << std::endl;
    ss << "Bus A: "
       << "0x" << std::hex << (int)busA << std::endl;
    ss << "Address: "
       << "0x" << std::hex << (int)address << std::endl;
    return ss.str();
}

instruction::instruction(const instruction &other)
{
    setCode(other.getCode());
    valid = other.isValid();
    ID = other.getId();
}

instruction::instruction(instruction &&other) noexcept
{
    setCode(other.getCode());
    valid = other.isValid();
    ID = other.getId();
}

unsigned int instruction::getId() const
{
    return ID;
}

void instruction::setId(unsigned int id)
{
    ID = id;
}

instruction &instruction::operator=(const instruction &other)
{
    setCode(other.getCode());
    valid = other.isValid();
    ID = other.getId();
    return *this;
}
