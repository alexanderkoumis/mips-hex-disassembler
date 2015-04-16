cmake_minimum_required(VERSION 2.8)
project(mips-disassembler)

set(CMAKE_CXX_FLAGS "-std=c++11")

add_executable(mips-disassembler main.cpp mips_instruction.cpp)
