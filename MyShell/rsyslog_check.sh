#!/bin/bash

NOW_TIME=$(date "+%Y-%m-%d.%k:%M:%S.%N")
REC_FILE=$(pwd)/rsyslog_check_result.$NOW_TIME.txt

##########################
# 打印生成文件头
##########################
print_head(){
    HOSTNAME=$(hostname)
    STR="/dev/tty.usb-serial-14210"
    IP_FULL_STR=$(ip addr | grep 'scope global eth0' | awk '{ print $2 }')
    IP=${IP_FULL_STR%/*}
    echo "========= $NOW_TIME check rsyslog config of $HOSTNAME($IP) =========" > $REC_FILE
}

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

##########################
# 执行命令并获取命令的返回内容
# - $1 : 命令的描述文字
# - $2 : 执行的命令字符串
##########################
exec_cmd_and_rec_stdoutput(){
    echo '' >> $REC_FILE
    echo "$1" >> $REC_FILE
    echo "$2" >> $REC_FILE
    echo '```shell' >> $REC_FILE
    $2 >> $REC_FILE
    echo '```' >> $REC_FILE
}

print_head
exec_cmd_and_rec_stdoutput '# 1. 查看线上设备的配置' 'cat /etc/rsyslog.conf'
exec_cmd_and_rec_stdoutput '# 2. 查看 rsyslog 自定义配置文件' 'ls -l /etc/rsyslog.d/'
# 查看 /etc/rsyslog.conf 路径下的所有文件
traverse_folders_and_exec_cmd '/etc/rsyslog.d/' 'cat ' >> $REC_FILE
exec_cmd_and_rec_stdoutput '# 3. 查看 pmon 容器内 rsyslog 的配置文件' 'docker exec pmon cat /etc/rsyslog.conf'
exec_cmd_and_rec_stdoutput '# 4. 查看 pmon 容器内 rsyslog 自定义配置文件' 'docker exec pmon ls -l /etc/rsyslog.d/'
exec_cmd_and_rec_stdoutput '## 4.1. 查看 pmon 容器内 rsyslog supervisor 自定义配置文件' 'docker exec pmon cat /etc/rsyslog.d/supervisor.conf'

