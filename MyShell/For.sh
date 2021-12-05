#!/bin/bash

MAX_LOOP_NUM=10
echo 'loop time='"$1"
if [[ 0 -lt $1 ]]; then
    MAX_LOOP_NUM=$1
fi

# for num in 0 10
for ((num = 0; num<=MAX_LOOP_NUM; num++))
do
    if [[ $num -eq $MAX_LOOP_NUM ]]
    then
        break
    else
        sleep 0.01 # Delay 10 ms
        # echo "==========Test inputting stream, num = $num"
        logger -p user.info "==========Test inputting stream, num = $num"
    fi
done
