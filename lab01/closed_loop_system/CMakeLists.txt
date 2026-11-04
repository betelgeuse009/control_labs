cmake_minimum_required(VERSION 3.20)
project(closed_loop_system)

set(CMAKE_CXX_STANDARD 20)

add_executable(closed_loop_system main.cpp
        PID.cpp
        PID.h
        FOtf.cpp
        FOtf.h)
