cmake_minimum_required(VERSION 3.21)
project(HOMicSim)

# Copy program.mp to build directory
configure_file(program.mp program.mp COPYONLY)

set(CMAKE_CXX_STANDARD 17)

set(CPP_SOURCE_FILES
        alu.cpp
        main.cpp
        memory.cpp
        registers.cpp
        simulator.cpp
        instruction.cpp
        parser.cpp
        amux.cpp
        shifter.cpp)

set(CPP_HEADER_FILES
        alu.h
        constants.h
        exceptions.h
        memory.h
        registers.h
        simulator.h
        instruction.h
        parser.h
        tests/test_parser.h
        tests/run_tests.h
        tests/test_simulator.h
        amux.h
        shifter.h)

add_executable(HOMicSim ${CPP_SOURCE_FILES} ${CPP_HEADER_FILES})
