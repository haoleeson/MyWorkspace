cmake_minimum_required(VERSION 3.20)
project(MyLeetCode)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(RunSingle
        myTools.h
        No1161.maximum-level-sum-of-a-binary-tree.cpp
        )

