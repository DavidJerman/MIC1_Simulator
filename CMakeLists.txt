cmake_minimum_required(VERSION 3.24)
project(HOMicSim)

set(CMAKE_CXX_STANDARD 17)

set(CPP_SOURCE_FILES
        alu.cpp
        main.cpp
        memory.cpp
        registers.cpp
        simulator.cpp
        instruction.cpp
        parser.cpp)

set(CPP_HEADER_FILES
        alu.h
        constants.h
        exceptions.h
        memory.h
        registers.h
        simulator.h
        instruction.h
        parser.h)

add_executable(HOMicSim ${CPP_SOURCE_FILES} ${CPP_HEADER_FILES})
