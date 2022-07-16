cmake_minimum_required(VERSION 3.20)
project(MyLeetCode)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(RunSingle
        myTools.h
        No346.moving-average-from-data-stream.cpp
        )
