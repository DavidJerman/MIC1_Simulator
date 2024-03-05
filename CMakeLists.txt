cmake_minimum_required(VERSION 3.21)
set(APP_NAME HOMicSim)
set(TEST_NAME HOMicSim_Tests)
project(${APP_NAME})

# Copy program.mp to build directory
file(COPY programs/program.mp DESTINATION ${CMAKE_BINARY_DIR})
file(COPY programs/program2.mp DESTINATION ${CMAKE_BINARY_DIR})
file(COPY programs/program3.mp DESTINATION ${CMAKE_BINARY_DIR})
file(COPY programs/SUMOFN.MP DESTINATION ${CMAKE_BINARY_DIR})

# VS Structure
file(GLOB_RECURSE SRC "src/lib/*.cpp")
file(GLOB_RECURSE INCLUDE "src/*.h")
file(GLOB_RECURSE SRC_Test "tests/src/*.cpp")
file(GLOB_RECURSE INCLUDE_Test "tests/src/*.h")
file(GLOB MAIN "src/main.cpp")

source_group("Header files" FILES ${INCLUDE})
source_group("Source files" FILES ${SRC})
source_group("Test \\ Header files" FILES ${INCLUDE_Test})
source_group("Test \\ Source files" FILES ${SRC_Test})

set(CMAKE_CXX_STANDARD 17)

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
    add_executable(${APP_NAME} ${SRC} ${INCLUDE} ${MAIN})
    add_executable(${TEST_NAME} ${SRC_Test} ${INCLUDE_Test} ${SRC} ${INCLUDE})
    target_include_directories(${APP_NAME} PRIVATE include)
    target_include_directories(${TEST_NAME} PRIVATE include)
    target_include_directories(${TEST_NAME} PRIVATE tests/include)
    target_link_libraries(${APP_NAME} ${LINKER_LIBRARIES_WINDOWS})
elseif(UNIX)
    add_executable(${APP_NAME} ${SRC} ${INCLUDE} ${MAIN})
    add_executable(${TEST_NAME} ${SRC_Test} ${INCLUDE_Test} ${SRC} ${INCLUDE})
    target_include_directories(${APP_NAME} PRIVATE include)
    target_include_directories(${TEST_NAME} PRIVATE include)
    target_include_directories(${TEST_NAME} PRIVATE tests/include)
    target_link_libraries(${APP_NAME} ${LINKER_LIBRARIES_LINUX})
endif()
