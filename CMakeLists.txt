cmake_minimum_required(VERSION 4.0)
project(CS213_Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CS213_Project
        Instruction.cpp
        Instruction.h
        RegisterFile.cpp
        RegisterFile.h)
