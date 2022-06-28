cmake_minimum_required(VERSION 3.20)
project(MyLeetCode)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(RunSingle
        myTools.h
        No653.two-sum-iv-input-is-a-bst.cpp
        )
