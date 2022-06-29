cmake_minimum_required(VERSION 3.20)
project(5_Dijkstra)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(5_Dijkstra
        DenseMatrixGraph.h
        DijkstraMain.cpp)
