#!/usr/bin/env bash
####################################################
# 周期观测 telemetry 的 cpu、memory、pps、bps 使用情况
# ver:      0.0.2
# author:   admin
# date:     2022-05-11
####################################################


# 观测资源性能时间间隔（五分钟）
INTERVAL_SEC='300'
# BGP 观测协议抖动时间间隔（资源间隔的多少倍，12倍，1小时）
TIMES_OF_INTERVAL_SEC=12

IP_STR=$(ip addr show eth0 | grep -oP \(\\d+\\.\){3}\\d+)

# 观察进程名
OBSERVE_PROCESS_NAME='dialout_client'
# 观测结果输出文件
OUTPUT_FILE="/home/admin/telemetry_inband_test/${IP_STR##*.}_observe_telemetry_cpu_mem_bps_pps_result.csv"
BGP_OBSERVE_OUTPUT_FILE="/home/admin/telemetry_inband_test/${IP_STR##*.}_observe_telemetry_bgp_effect.csv"


# 查看指定进程的 CPU 使用率
# param1:  入参 进程字段
# return:   xx % ;  process_not_exist
func_observe_process_cpu_usage() {
    local process_name="$1"
    if [ ! -n "$1" ]; then
        echo "empty_process_name"
        return 1
    fi

    STR=$(ps -ef | fgrep -v 'grep' | grep "$process_name")
    if [ "$?" != 0 ]; then
        echo "process_not_exist"
        return 2
    fi

    PID=$(ps -ef | fgrep -v 'grep' | grep "$process_name" | head -n +1 | awk '{ print $2 }')
    echo "$(ps -p $PID -o %cpu | tail -n +2  | tr -d ' ')"
}


# 设备的整体 CPU 使用率
func_total_cpu_usage() {
    echo "$(cat /proc/stat | grep cpu | head -1 | awk '{print ($5*100)/($2+$3+$4+$5+$6+$7+$8+$9+$10)}'| awk '{print 100-$1}')"
}


# 查看指定进程的 内存占用
# param1:  入参 进程字段
# return:   xxxxx kB ;  process_not_exist
func_observe_process_mem_usage() {
    local process_name="$1"
    if [ ! -n "$1" ]; then
        echo "empty_process_name"
        return 1
    fi

    STR=$(ps -ef | fgrep -v 'grep' | grep "$process_name")
    if [ "$?" != 0 ]; then
        echo "process_not_exist"
        return 2
    fi

    PID=$(ps -ef | fgrep -v 'grep' | grep "$process_name" | head -n +1 | awk '{ print $2 }')
    if [ -f /proc/$PID/status ]; then
        STR=$(grep 'VmRSS' /proc/$PID/status | tr -d ' kB')
        echo ${STR##*:}
    fi
}


# 观测资源占用情况，输出到文件
# param1: 进程名
# param2: 观测结果输出文件
observe_and_output_source_usage() {
    local process_name="$1"
    local output_file="$2"
    if [ ! -n "$1" ]; then
        return 1
    elif [ ! -n "$2" ]; then
        return 2
    fi

    if [ ! -f $output_file ]; then
        echo 'observe_time,telemetry_cpu_usage(%),dev_average_cpu_usage(%),memory_usage(kB),pps(p/s),bps(b/s)' > $output_file
    fi

    local observe_time="$(date +%Y-%m-%d.%H:%M:%S)"
    local telemetry_cpu_usage="$(func_observe_process_cpu_usage "$process_name")"
    local dev_average_cpu_usage="$(func_total_cpu_usage)"
    local memory_usage="$(func_observe_process_mem_usage "$process_name")"
    RESULT="$(bcmcmd 'show c cpu' | grep '(2)' | awk '{ print $1,$5 }' | sed 's/,//g')"
    pps="$(echo "$RESULT" | grep 'PKT(2)' | awk '{ print $2 }' | tr -d '\r\n/s')"
    bps="$(echo "$RESULT" | grep 'BYTE(2)' | awk '{ print $2 }' | tr -d '\r\n/s')"

    echo "$observe_time,$telemetry_cpu_usage,$dev_average_cpu_usage,$memory_usage,$pps,$bps" >> $output_file
}


main() {
    i=0
    while true; do
        # 观察 Telemetry 资源占用情况
        observe_and_output_source_usage $OBSERVE_PROCESS_NAME $OUTPUT_FILE

        # 每当计数到资源观测周期 TIMES_OF_INTERVAL_SEC 倍时（每三小时），观测一次 bgp 协议状态
        if [ $i -eq $TIMES_OF_INTERVAL_SEC ]; then
            echo "" >> $BGP_OBSERVE_OUTPUT_FILE
            show bgp summary | fgrep -v 'never' >> $BGP_OBSERVE_OUTPUT_FILE
            let i=0
        fi
        sleep ${INTERVAL_SEC}s
        let i++
    done
}

main
