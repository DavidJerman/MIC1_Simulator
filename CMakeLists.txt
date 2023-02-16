cmake_minimum_required(VERSION 3.24)
project(HOMicSim)

# Copy program.mp to build directory
file(COPY program.mp DESTINATION ${CMAKE_BINARY_DIR})
file(COPY program2.mp DESTINATION ${CMAKE_BINARY_DIR})
file(COPY program3.mp DESTINATION ${CMAKE_BINARY_DIR})
file(COPY SUMOFN.MP DESTINATION ${CMAKE_BINARY_DIR})

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

# Set linker libraries for Windows
set(LINKER_LIBRARIES_WINDOWS
        user32
        gdi32
        opengl32
        gdiplus
        Shlwapi
        dwmapi)

# Set linker libraries for Linux
set(LINKER_LIBRARIES_LINUX
        X11
        GL
        pthread
        png
        stdc++fs)

if(WIN32)
    add_executable(HOMicSim ${CPP_SOURCE_FILES} ${CPP_HEADER_FILES})
    target_link_libraries(HOMicSim ${LINKER_LIBRARIES_WINDOWS})
elseif(UNIX)
    add_executable(HOMicSim ${CPP_SOURCE_FILES} ${CPP_HEADER_FILES})
    target_link_libraries(HOMicSim ${LINKER_LIBRARIES_LINUX})
endif()
