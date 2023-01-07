//
// Created by david on 1/7/2023.
//

#ifndef HOMICSIM_EXCEPTIONS_H
#define HOMICSIM_EXCEPTIONS_H

#include <exception>

class memory_out_of_bounds_exception : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return "Memory out of bounds - address is greater than 4096";
    }
};

class memory_bus_exception : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return "Memory bus exception - you probably tried to read while writing or vice versa or set the MAR while the memory was busy";
    }
};

#endif //HOMICSIM_EXCEPTIONS_H
