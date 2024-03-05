cmake_minimum_required(VERSION 3.21)
set(APP_NAME HOMicSim)
project(${APP_NAME})

# Copy program.mp to build directory
file(COPY programs/program.mp DESTINATION ${CMAKE_BINARY_DIR})
file(COPY programs/program2.mp DESTINATION ${CMAKE_BINARY_DIR})
file(COPY programs/program3.mp DESTINATION ${CMAKE_BINARY_DIR})
file(COPY programs/SUMOFN.MP DESTINATION ${CMAKE_BINARY_DIR})

# VS Structure
file(GLOB_RECURSE SRC "src/*.cpp")
file(GLOB_RECURSE INCLUDE "src/*.h")

source_group("Header files" FILES ${INCLUDE})
source_group("Source files" FILES ${SRC})

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
    add_executable(${APP_NAME} ${SRC} ${INCLUDE})
    target_include_directories(${APP_NAME} PRIVATE include)
    target_link_libraries(${APP_NAME} ${LINKER_LIBRARIES_WINDOWS})
elseif(UNIX)
    add_executable(${APP_NAME} ${SRC} ${INCLUDE})
    target_include_directories(${APP_NAME} PRIVATE include)
    target_link_libraries(${APP_NAME} ${LINKER_LIBRARIES_LINUX})
endif()
