//
// Created by pinkynyte on 1/12/23.
//

#include "instruction.h"

instruction::instruction() {
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

instruction::instruction(dword value) {
    setCode(value);
}

void instruction::setCode(dword value) {
    auto cast = (int) value;
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

dword instruction::getCode() const {
    return (dword) (amux << AMUX_SH | cond << COND_SH | alu << ALU_SH | sh << SH_SH | mbr << MBR_SH | mar << MAR_SH |
                    rd << RD_SH | wr << WR_SH | enc << ENC_SH | busC << BUS_C_SH | busB << BUS_B_SH | busA << BUS_A_SH |
                    address << ADDRESS_SH);
}

bool instruction::isValid() const {
    return valid;
}

void instruction::invalidate() {
    valid = false;
}

int instruction::getAmux() const {
    return amux;
}

void instruction::setAmux(int newAmux) {
    instruction::amux = newAmux;
}

int instruction::getCond() const {
    return cond;
}

void instruction::setCond(int newCond) {
    instruction::cond = newCond;
}

int instruction::getAlu() const {
    return alu;
}

void instruction::setAlu(int newAlu) {
    instruction::alu = newAlu;
}

int instruction::getSh() const {
    return sh;
}

void instruction::setSh(int newSh) {
    instruction::sh = newSh;
}

int instruction::getMbr() const {
    return mbr;
}

void instruction::setMbr(int newMbr) {
    instruction::mbr = newMbr;
}

int instruction::getMar() const {
    return mar;
}

void instruction::setMar(int newMar) {
    instruction::mar = newMar;
}

int instruction::getRd() const {
    return rd;
}

void instruction::setRd(int newRd) {
    instruction::rd = newRd;
}

int instruction::getWr() const {
    return wr;
}

void instruction::setWr(int newWr) {
    instruction::wr = newWr;
}

int instruction::getEnc() const {
    return enc;
}

void instruction::setEnc(int newEnc) {
    instruction::enc = newEnc;
}

int instruction::getBusC() const {
    return busC;
}

void instruction::setBusC(int newBusC) {
    instruction::busC = newBusC;
}

int instruction::getBusB() const {
    return busB;
}

void instruction::setBusB(int newBusB) {
    instruction::busB = newBusB;
}

int instruction::getBusA() const {
    return busA;
}

void instruction::setBusA(int newBusA) {
    instruction::busA = newBusA;
}

byte instruction::getAddress() const {
    return address;
}

void instruction::setAddress(byte newAddress) {
    instruction::address = newAddress;
}

std::string instruction::toString() const {
    std::stringstream ss;
    ss << "Amux: " << (amux == AMUX::A_LATCH ? "A Latch" : "MBR") << std::endl;
    ss << "Cond: " << (cond == COND::JUMP ? "Always Jump" :
                       cond == COND::NO_JUMP ? "No Jump" :
                       cond == COND::N_JUMP ? "N Jump" : "Z Jump") << std::endl;
    ss << "Alu: " << (alu == ALU::A_PLUS_B ? "+" :
                      alu == ALU::A_AND_B ? "&" :
                      alu == ALU::POS_A ? "Pos A" : "Neg A") << std::endl;
    ss << "Sh: " << (sh == SH::NO_SHIFT ? "No Shift" :
                     sh == SH::LEFT_SHIFT ? "Left Shift" :
                     sh == SH::RIGHT_SHIFT ? "Right Shift" : "Invalid Shift") << std::endl;
    ss << "Mbr: " << (mbr == YES ? "Yes" : "No") << std::endl;
    ss << "Mar: " << (mar == YES ? "Yes" : "No") << std::endl;
    ss << "Rd: " << (rd == YES ? "Yes" : "No") << std::endl;
    ss << "Wr: " << (wr == YES ? "Yes" : "No") << std::endl;
    ss << "Enc: " << (enc == YES ? "Yes" : "No") << std::endl;
    ss << "Bus C: " << "0x" << std::hex << (int) busC << std::endl;
    ss << "Bus B: " << "0x" << std::hex << (int) busB << std::endl;
    ss << "Bus A: " << "0x" << std::hex << (int) busA << std::endl;
    ss << "Address: " << "0x" << std::hex << (int) address << std::endl;
    return ss.str();
}
