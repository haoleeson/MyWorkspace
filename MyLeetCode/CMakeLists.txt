cmake_minimum_required(VERSION 3.20)
project(MyLeetCode)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(RunSingle
        myTools.h
        No558.logical-or-of-two-binary-grids-represented-as-quad-trees.cpp
        )
