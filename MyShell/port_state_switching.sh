#!/usr/bin/env bash
####################################################
# 批量端口转换 （模拟端口抖动）
# ver:      0.0.1
# author:   admin
# date:     2022-05-06
####################################################


# 关闭端口后等待时间（3秒）
DOWN_WAIT_SEC='3'
# 开启端口后等待时间（7秒）
UP_WAIT_SEC='7'
# 端口类型
PORTS_TYPE='ce'
# 待切换端口范围（逗号分隔，包含两端；注意为实际端口号-1）
PORTS='0,63'
# 抖动次数 （抖动持续时间 10s x 360 = 一小时）
MAX_SWITCH_TIMES=360


# 批量关闭指定范围的端口
# param1: bcm 中端口的类型 eg. cd ce
# param2: 要批量关闭的端口范围
func_batch_range_down() {
    local port_type="$1"
    local port_range="$2"
    # echo "$(date +%Y-%m-%d.%H:%M:%S.%N) 'for i=$port_range \"port $port_type\\\$i en=0\"'"

    # 批量 DOWN 1~63 共 33 个端口
    # bcmcmd 'for i=1,63 "port ce\$i en=0"' > /dev/null 2>&1
    bcmcmd "for i=$port_range 'port $port_type\\\$i en=0'" > /dev/null 2>&1
}


# 批量打开指定范围的端口
# param1: bcm 中端口的类型 eg. cd ce
# param2: 要批量打开的端口范围
func_batch_range_up() {
    local port_type="$1"
    local port_range="$2"
    # echo "$(date +%Y-%m-%d.%H:%M:%S.%N) 'for i=$port_range \"port $port_type\\\$i en=1\"'"

    # 批量 DOWN 1~63 共 33 个端口
    # bcmcmd 'for i=0,63 "port ce\$i en=1"' > /dev/null 2>&1
    bcmcmd "for i=$port_range 'port $port_type\\\$i en=1'" > /dev/null 2>&1
}


# 显示端口初始信息
func_show_initial_port_stat() {
    RESULT="$(/usr/bin/cli -c 'show interfaces status all' | grep 'up       up' | awk '{ print $1 }')"
    local up_port_num="$(echo "$RESULT" | wc -l)"
    local up_ports="$(echo "$RESULT" | sed 's/Ethernet//g' | tr '\r\n' ' ')"
    echo "$(date +%Y-%m-%d.%H:%M:%S.%N) There are a total of ($up_port_num) up ports:"
    echo $up_ports
}


main() {
    echo "$(date +%Y-%m-%d.%H:%M:%S.%N) Starting running port_state_switching.sh"

    # 打印初始端口信息
    func_show_initial_port_stat

    i=0
    while true; do
        let i++
        if [ $i -gt $MAX_SWITCH_TIMES ]; then
            echo "$(date +%Y-%m-%d.%H:%M:%S.%N) Flapping ports finish."
            return 0
        fi

        echo "$(date +%Y-%m-%d.%H:%M:%S.%N) The ($i)th time to flap ports($PORTS)..."

        # 批量关闭指定范围内端口
        func_batch_range_down $PORTS_TYPE $PORTS
        # 关闭端口等待时间（3秒）
        sleep ${DOWN_WAIT_SEC}s

        # 批量打开指定范围内端口
        func_batch_range_up $PORTS_TYPE $PORTS
        # 打开端口等待时间（7秒）
        sleep ${UP_WAIT_SEC}s
    done
}

main
