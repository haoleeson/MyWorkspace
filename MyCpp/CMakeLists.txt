cmake_minimum_required(VERSION 3.20)
project(MyCpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(RunSingle
        baseTest/pipeTest.c
        )
