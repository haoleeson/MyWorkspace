cmake_minimum_required(VERSION 3.19)
project(c_demo C)

set(CMAKE_CXX_STANDARD 11)

add_executable(c_demo_main main.c)

add_executable(test_teamd_log teamd_log/test_teamd_log.c teamd_log/teamd_log.c)


