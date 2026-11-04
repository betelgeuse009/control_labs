cmake_minimum_required(VERSION 3.20)
project(PIDcontroller)

set(CMAKE_CXX_STANDARD 20)

add_executable(PIDcontroller main.cpp
        PID.cpp
        PID.h)
