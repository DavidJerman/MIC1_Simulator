cmake_minimum_required(VERSION 3.24)
project(HOMicSim)

set(CMAKE_CXX_STANDARD 17)

add_executable(HOMicSim main.cpp memory.cpp memory.h constants.h exceptions.h registers.cpp registers.h)