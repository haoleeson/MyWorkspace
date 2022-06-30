cmake_minimum_required(VERSION 3.20)
project(MyLeetCode)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(RunSingle
        myTools.h
        No80.remove-duplicates-from-sorted-array-ii.cpp
        )
