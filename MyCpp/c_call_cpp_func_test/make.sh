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
g++ -Wno-deprecated -std=c++0x -o logctl_access_redis_wrapper.o -c logctl_access_redis_wrapper.cpp -L. -ologctlaccessredis -lpthread

# 编译 main.c
gcc -o main_exe main.c logctl_access_redis_wrapper.o -lstdc++ -L. -llogctlaccessredis -lpthread

gcc main.c -o main_exe -lstdc++ -L/usr/lib/x86_64-linux-gnu/ -ologctlaccessredis
gcc main.c -o main_exe -lstdc++ -L. -llogctlaccessredis
#【OK】
gcc main.c -o main_exe -lstdc++ -L. /usr/lib/x86_64-linux-gnu/liblogctlaccessredis.so

gcc main.c -o main_exe -lpthread -lstdc++ -L/usr/lib/x86_64-linux-gnu/ /usr/lib/x86_64-linux-gnu/liblogctlaccessredis.so.0



gcc -D_REENTRANT -D_GNU_SOURCE -g -O2 -o main_exe teamd-teamd.o teamd-teamd_common.o teamd-teamd_json.o teamd-teamd_config.o teamd-teamd_state.o teamd-teamd_workq.o teamd-teamd_events.o teamd-teamd_per_port.o teamd-teamd_option_watch.o teamd-teamd_ifinfo_watch.o teamd-teamd_lw_ethtool.o teamd-teamd_lw_psr.o teamd-teamd_lw_arp_ping.o teamd-teamd_lw_nsna_ping.o teamd-teamd_lw_tipc.o teamd-teamd_link_watch.o teamd-teamd_ctl.o teamd-teamd_dbus.o teamd-teamd_zmq.o teamd-teamd_usock.o teamd-teamd_phys_port_check.o teamd-teamd_bpf_chef.o teamd-teamd_hash_func.o teamd-teamd_balancer.o teamd-teamd_runner_basic_ones.o teamd-teamd_runner_activebackup.o teamd-teamd_runner_loadbalance.o teamd-teamd_runner_lacp.o  ../libteam/.libs/libteam.so -ldaemon -ljansson -ldbus-1 -L../../../sonic-swss-common/logctl/ /sonic/src/sonic-swss-common/logctl/.libs/liblogctlaccessredis.so