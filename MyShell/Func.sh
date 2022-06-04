#!/usr/bin/env bash

say_hello() {
    echo "hello world"
}

print() {
    local param1=$1
    local param2=$2

    if [ $param1 ]; then
        echo "param1: $param1"
    fi

    if [ $param2 ]; then
        echo "param2: $param2"
    fi
}

add() {
    varAddRes=$(expr $1 + $2)
    return $varAddRes
}

main() {
    say_hello
    local num1=1
    local num2=2
    add $num1 $num2 #调用函数，传递参数
    echo $?

    print 'syslog' 'syslog'
}

main