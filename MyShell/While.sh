#!/usr/bin/env bash

MAX_LOOP_NUM=10
num=0
if [[ 0 -lt $1 ]]; then
    echo 'loop time='"$1"
    MAX_LOOP_NUM=$1
fi

# for num in 0 10
while true
do
    if [[ $num -eq $MAX_LOOP_NUM ]]; then
        break
    else
        echo "Loop time $num/$MAX_LOOP_NUM"
        let num++
    fi
done


str1="I am chinese"
array1=(${str1// / })
echo "----------::::While循环遍历未知长度数组::::----------"
i=0
while [ $i -lt ${#array1[@]} ]
do
    echo "arr[$i] = ${array1[$i]}"
    let i++
done