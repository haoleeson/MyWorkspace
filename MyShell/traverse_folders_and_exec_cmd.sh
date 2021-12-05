#!/bin/bash

##########################
# 执行命令并获取命令的返回内容
# - $1 : 目标路径
# - $2 : 待执行命令
##########################
traverse_folders_and_exec_cmd(){
    local TARGET_DIR=$1
    local TARGET_CMD=$2

    if [ ! -n "$TARGET_DIR" ];then
        echo 'Input TARGET_DIR is empty!!!'
        exit 1
    elif [ ! -n "$TARGET_CMD" ];then
        echo 'Input TARGET_CMD is empty!!!'
        exit 2
    elif [ ! -d $TARGET_DIR ]; then
        echo "The input TARGET_DIR$($TARGET_DIR) is not exist!!!"
        exit 3
    fi

    local files=$(ls -l $TARGET_DIR | tail -n +2 | awk '{ print $NF }')

    # exec target cmd with each file
    for file in $files
    do
        if [ -d "$TARGET_DIR/$file" ]; then
            traverse_folders_and_exec_cmd "$TARGET_DIR/$file" "$TARGET_CMD"
        else
            # the real exec target command
            echo "exec $TARGET_CMD $TARGET_DIR/$file"
            $TARGET_CMD "$TARGET_DIR/$file"
        fi
    done
}

traverse_folders_and_exec_cmd '/Users/lihao52/test/' 'ls '
