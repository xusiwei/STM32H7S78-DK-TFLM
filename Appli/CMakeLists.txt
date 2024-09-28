cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

message("Build type: " ${CMAKE_BUILD_TYPE})

find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    message(STATUS "Ccache found: ${CCACHE_PROGRAM}!")
else ()
    message(STATUS "Ccache not found!")
endif ()

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Compiler options
set(STM32_MCU_FLAGS  "-mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard " )

#Linker options
set(STM32_LINKER_SCRIPT stm32h7rsxx_RAMxspi1_ROMxspi2.ld)
set(STM32_LINKER_OPTION  )

# Include toolchain file
include("../gcc-arm-none-eabi.cmake")

# Set the project name
set(CMAKE_PROJECT_NAME STM32H7S78-DK-XIP_Appli)
project(${CMAKE_PROJECT_NAME})

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Include mx-generated 
include("mx-generated.cmake")

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# In order to use CMake for cross-compiling
set(CMAKE_CXX_COMPILER_FORCED "true") 

set(TOP_DIR ..)
set(TENSORFLOW_SUBDIR Middlewares/tensorflow/tflite-micro)
set(TENSORFLOW_DIR ${TOP_DIR}/${TENSORFLOW_SUBDIR})

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE 
    # Add user defined symbols
    # KEYWORD_BENCHMARK
    PERSON_DETECTION_BENCHMARK
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    ${TENSORFLOW_DIR}
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    Src/tflm_benchmark.cc
    Src/tflm_benchmark.h
    # 添加 STM32 的计时实现：
    Src/micro_time.cc
)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
    ../build/Release/${TENSORFLOW_SUBDIR}
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined libraries
    # keyword_benchmark
    person_detection_benchmark
    tflite-micro
)

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()


# Post build commands
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD 
  COMMAND ${CMAKE_OBJCOPY} -O srec ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.srec
  )


# 支持浮点数格式化
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
  -u _printf_float
)




