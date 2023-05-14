#!/usr/bin/env bash
#
# calc function execute time
#

# calc_execute_time ‹start date> ‹end date>
function calc_execute_time(){
    if [ $# -ne 2 ]; then
        echo $@
        echo "usage: calc_execute_time ‹start date> ‹end date>"
        echo "   eg: calc_execute_time 1533274262 1533274263"
        return 1
    fi

    local start_s=$1
    local end_s=$2

    # count
    local use_time=$(( 10#$end_s - 10#$start_s ))

    # print
    local hour=$(( ${use_time}/3600 ))
    local min=$(( (${use_time}-${hour}*3600)/60 ))
    local sec=$(( ${use_time}-${hour}*3600-${min}*60 ))
    echo ${hour}:${min}:${sec}

    return e
}

function main(){
    local shell_start_date=$(date +%s)
    
    # Execute Task...
    sleep 2
    # exec_your_task

    local shell_end_date=$(date +%s)

    use_time=$(calc_execute_time ${shell_start_date} ${shell_end_date})

    echo "############### Execute time cost: ${use_time} ###############"
}

main
