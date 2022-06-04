#!/usr/bin/env bash

MAX_LOOP_NUM=5
echo 'loop time='"$1"
if [[ 0 -lt $1 ]]; then
    MAX_LOOP_NUM=$1
fi

# for num in 0 10
for ((num = 0; num<=MAX_LOOP_NUM; num++))
do
    echo "\t$num\t/\t$MAX_LOOP_NUM"
    # nohup /home/main_exe -t &
    sleep 0.125 # Delay 1 s
done

for i in 1 2 3 4 5;
do
    cmd_str="bcmcmd \"dsh -c 'phyd $i dsc'\""
    # 打印命令
    echo $cmd_str
done


for i in 1 2 3 4 5; do
    cmd_str="bcmcmd \"dsh -c 'phyd $i dsc'\""
    # 打印命令
    echo $cmd_str
done
