#!/usr/bin/env bash

##########################
# 模拟重复点击鼠标
# - $1 : 重复次数
# - $2 : x坐标
# - $3 : y坐标
##########################
MAX_LOOP_NUM=5
X_POSITION=1209
Y_POSITION=427
echo 'loop time='"$1"
if [[ 0 -lt $1 ]]; then
    MAX_LOOP_NUM=$1
fi

if [ $2 ]; then
    X_POSITION=$2
fi

if [ $3 ]; then
    Y_POSITION=$3
fi

# for num in 0 10
for ((num = 0; num<=MAX_LOOP_NUM; num++))
do
    if [[ $num -eq $MAX_LOOP_NUM ]]
    then
        break
    else
        echo "\t$num\t/\t$MAX_LOOP_NUM"
        # nohup /home/main_exe -t &
        cliclick c:$X_POSITION,$Y_POSITION
        sleep 0.125 # Delay 1 s
    fi
done

# for i in 1 2 3 4 5;
# do
#     cmd_str="bcmcmd \"dsh -c 'phyd $i dsc'\""
#     # 打印命令
#     echo $cmd_str
# done
