#!/usr/bin/env bash

MAX_LOOP_NUM=100000
num=0
if [[ 0 -lt $1 ]]; then
    echo 'loop time='"$1"
    MAX_LOOP_NUM=$1
fi

# for num in 0 100000
while true
do
    if [[ $num -eq $MAX_LOOP_NUM ]]; then
        break
    else
        echo "Loop time $num/$MAX_LOOP_NUM"
        zcat /var/log/syslog.8.gz > /dev/null
        let num+=1
    fi
done
