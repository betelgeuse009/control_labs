cmake_minimum_required(VERSION 3.20)
project(simple_tf)

set(CMAKE_CXX_STANDARD 20)

add_executable(simple_tf main.cpp
        FOtf.cpp
        FOtf.h)
