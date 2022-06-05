cmake_minimum_required(VERSION 3.19)
project(SkipList)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/log)
include_directories(src/skip_list)
include_directories(src/tests)

add_executable(skip_list_main
        src/log/vlog.cpp
        src/log/vlog.h
        src/skip_list/skip_list.h
        src/skip_list/skip_list_node.h
        main.cpp)

add_executable(test_insert
        src/log/vlog.cpp
        src/log/vlog.h
        src/skip_list/skip_list.h
        src/skip_list/skip_list_node.h
        src/tests/test_insert.cpp)


add_executable(test_del
        src/log/vlog.cpp
        src/log/vlog.h
        src/skip_list/skip_list.h
        src/skip_list/skip_list_node.h
        src/tests/test_del.cpp)


add_executable(test_get
        src/log/vlog.cpp
        src/log/vlog.h
        src/skip_list/skip_list.h
        src/skip_list/skip_list_node.h
        src/tests/test_get.cpp)


add_executable(test_dump
        src/log/vlog.cpp
        src/log/vlog.h
        src/skip_list/skip_list.h
        src/skip_list/skip_list_node.h
        src/tests/test_dump.cpp)

add_executable(test_load
        src/log/vlog.cpp
        src/log/vlog.h
        src/skip_list/skip_list.h
        src/skip_list/skip_list_node.h
        src/tests/test_load.cpp)

add_executable(test_mul_thread_read
        src/log/vlog.cpp
        src/log/vlog.h
        src/skip_list/skip_list.h
        src/skip_list/skip_list_node.h
        )
