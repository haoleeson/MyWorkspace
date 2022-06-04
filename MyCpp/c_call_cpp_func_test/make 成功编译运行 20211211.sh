#!/bin/bash

rm ./*.o
rm ./*.a

# 编译 common_data_definition
g++ -Wno-deprecated -std=c++0x -o common_data_definition.o -c common_data_definition.cpp

# 编译 logctl_access_redis
g++ -Wno-deprecated -std=c++0x -o logctl_access_redis.o -c logctl_access_redis.cpp -lpthread

# 将 logctl_access_redis、common_data_definition 二进制 生成静态库 logctlaccessredis
ar -crv liblogctlaccessredis.a logctl_access_redis.o common_data_definition.o

# 编译 logctl_access_redis_wrapper 并链接 logctlaccessredis 及 pthread 静态库
g++ -Wno-deprecated -std=c++0x -o logctl_access_redis_wrapper.o -c logctl_access_redis_wrapper.cpp -L. -llogctlaccessredis -lpthread

# 编译 main.c
gcc -o main_exe main.c logctl_access_redis_wrapper.o -lstdc++ -L. -llogctlaccessredis -lpthread

# teamd 容器内执行
gcc main.c -o main_exe -lstdc++ -L/usr/lib/x86_64-linux-gnu/ /usr/lib/x86_64-linux-gnu/liblogctlaccessredis.so.0
