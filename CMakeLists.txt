cmake_minimum_required(VERSION 2.8)
project(mips-assembler)

set(CMAKE_CXX_FLAGS "-std=gnu++11 -gdwarf-3")

add_executable(mips-assembler main.cpp)
