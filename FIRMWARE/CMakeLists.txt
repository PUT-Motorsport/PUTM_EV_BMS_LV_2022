cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME BMSLV_2022)


# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C CXX ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)
#Add Can library
add_subdirectory(Core/Inc/PUTM_EV_CAN_LIBRARY)
# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

file(GLOB CXX_SRC "${PROJECT_SOURCE_DIR}/Core/Src/*.cpp")
# file(GLOB C_SRC "${PROJECT_SOURCE_DIR}/Core/Src/*.c")

message("CXX_SRC: " ${CXX_SRC})
message("C_SRC: " ${C_SRC})
set(C_SRC
    "${PROJECT_SOURCE_DIR}/Core/Src/ring_buffer.c"
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    ${CXX_SRC}
    ${C_SRC}
    # Add user defined source files
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}/Drivers/ETL/include/"
    "${PROJECT_SOURCE_DIR}/Core/Inc"
    "${PROJECT_SOURCE_DIR}/Core/Inc/PUTM_EV_CAN_LIBRARY/include"
    "${PROJECT_SOURCE_DIR}/Core/Inc/PUTM_EV_CAN_LIBRARY/database/generated"
    # Add user defined include paths
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx
    putm_ev_can
    # Add user defined libraries
)
