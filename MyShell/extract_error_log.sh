#!/usr/bin/env bash
################################################################
# 捞取设备各类异常日志，并压缩归档
# Param1： 执行设备所属MR名
# Param2： netadmin MR同网段IP（可选，默认空）

# Usage: sh extract_error_log.sh bb

# 涉及日志文件：
#   - /var/log/syslog
#   - /var/log/quagga/bgpd.log、/var/log/quagga/zebra.log
#   - /var/log/swss/swss.rec、/var/log/swss/sairedis.rec
#   - /var/log/daemon.log
#   - /var/log/monit.log
################################################################

# 入参1：获取小写 netadmin MR名
if [ ! $1 ]; then
    NETADMIN_NAME='bb'
else
    NETADMIN_NAME=$(echo "$1" | tr [A-Z] [a-z])
fi

# 运行时间
RUN_TIME=$(date +%Y-%m-%d--%H-%M-%S)
# 设备管理IP
DEV_IP=$(ip addr show eth0 | grep -oP \(\\d+\\.\){3}\\d+ | head -n +1)

# 入参2：获取 netadmin MR同网段IP
if [ $2 ]; then
    NETADMIN_IP=$2
else
    NETADMIN_IP="${DEV_IP%\.*}.5"
fi

# 临时暂存"捞取的异常日志"文件夹
SAVE_LOG_DIR="$HOME/${NETADMIN_NAME}_${DEV_IP}_${RUN_TIME}"
# 远程错误日志汇总文件仓库
REMOTE_REPOSITORY='admin@A.B.C.D:/home/admin/inspect_error_log/scp'
REMOTE_SFTP_REPOSITORY='admin@A.B.C.D:/home/admin/inspect_error_log/sftp'
REMOTE_SERVER_PWD='e'

# 函数：从各日志文件捞取指定异常字段的日志
#   param1: 所属日志
#   param2: 源日志文件名
#   param3: 异常日志（正则）字段
#   param4: 排除字段（fgrep）
func_extract_log() {
    local log_name="$1"
    local log_file="$2"
    local grep_str="$3"
    local fgrep_str="$4"
    local save_file="$SAVE_LOG_DIR/${log_name}.log"

    if [ ! -n "$1" ]; then
        echo "param1 is Null"
        return 1
    elif [ ! -n "$2" ]; then
        echo "param2 is Null"
        return 2
    elif [ ! -n "$3" ]; then
        echo "param3 is Null"
        return 3
    fi

    # echo ""
    # echo ">> Extracting '$grep_str' log from ${log_name}(${log_file}) ..."

    # 按时间顺序，循环从历史归档文件中提取异常日志
    for i in $(ls -tr /var/log/${log_file}.*.gz); do
        if [ ! $fgrep_str ]; then
            sudo zgrep -E "$grep_str" $i >> $save_file
        else
            sudo zgrep -E "$grep_str" $i | fgrep -v "$fgrep_str" >> $save_file
        fi
    done

    # 过滤当前日志文件中的异常日志
    if [ -f /var/log/${log_file} ]; then
        if [ ! $fgrep_str ];  then
            sudo grep -E "$grep_str" /var/log/${log_file} >> $save_file
        else
            sudo grep -E "$grep_str" /var/log/${log_file} | fgrep -v "$fgrep_str" >> $save_file
        fi
    fi

    # echo "\033[32mExtract '$grep_str' log from ${log_file} file complete.\033[39m"
}

# 函数：获取设备状态信息
#   param1: 存储设备状态的日志路径
func_obtain_dev_status_to() {
    local dev_status_log="$1"
    if [ "$dev_status_log" = "" ]; then
        dev_status_log="$SAVE_LOG_DIR/${NETADMIN_NAME}_${DEV_IP}--device_status"
    fi
    echo "===================== Obtain time:  $(date +%Y-%m-%d.%H:%M:%S) =====================" >> $dev_status_log
    ip addr show eth0 >> $dev_status_log
    /usr/bin/cli -c 'show version' >> $dev_status_log
    docker ps -a >> $dev_status_log
}

# 上传压缩后文档到 NetAdmin 服务器
func_upload_then_del_tar() {
    tftp ${NETADMIN_IP} -c put ${NETADMIN_NAME}_${DEV_IP}_${RUN_TIME}.tar.gz
    # 判断上传是否成功（ 69 ： 超时；  0：成功）
    RET=$?
    if [ "$RET" = "0" ]; then
        # expect 关键识别字段 "Successfully uploaded"
        echo "===================== Successfully uploaded ${NETADMIN_NAME}_${DEV_IP}_${RUN_TIME}.tar.gz to ${NETADMIN_IP} ^_^ ====================="
        rm -rf ${NETADMIN_NAME}_${DEV_IP}_*.tar.gz
    else
        # expect 关键识别字段 "Failed to upload"
        echo "===================== Failed to upload ${NETADMIN_NAME}_${DEV_IP}_${RUN_TIME}.tar.gz to ${NETADMIN_IP} !!! ====================="
    fi
}

# 主函数
main() {
    # 删除历史捞取的异常日志归档文件（eg. bb_A.B.C.D_*.tar.gz）
    rm -rf $HOME/${NETADMIN_NAME}_${DEV_IP}_*.tar.gz

    # 新建此次巡检的 临时暂存"捞取的异常日志"文件夹
    if [ ! -d $SAVE_LOG_DIR ]; then
        mkdir $SAVE_LOG_DIR
    fi

    echo "===================== $(date +%Y-%m-%d.%H:%M:%S) extracting start ====================="

    ## 读设备状态信息到文件
    func_obtain_dev_status_to "$SAVE_LOG_DIR/${NETADMIN_NAME}_${DEV_IP}--device_status"

    ## 捞 syslog 日志
    func_extract_log 'syslog_err_warn' 'syslog' 'ERR|WARNING'
    ## 捞 bgpd 日志
    func_extract_log 'bgpd_err_warn' 'quagga/bgpd.log' 'ERR|WARNING'
    ## 捞 zebra 日志
    func_extract_log 'zebra_err_warn' 'quagga/zebra.log' 'ERR|WARNING'
    ## 捞 swss 日志
    func_extract_log 'swss_err_warn' 'swss/swss.rec' 'ERR|WARNING'
    ## 捞 sairedis 日志
    func_extract_log 'sairedis_err_warn' 'swss/sairedis.rec' 'ERR|WARNING'
    ## 捞 daemon 日志
    func_extract_log 'daemon_err_warn' 'daemon.log' 'ERR|WARNING' 'Success'
    ## 捞 monit 日志
    func_extract_log 'monit_err_warn' 'monit.log' 'ERR|WARNING'

    # 其他非 ERR 异常补充
    ## 电源、风扇、温度异常
    func_extract_log 'psu_fan_temperature_alarm' 'syslog' '(Psu[0-9]+ is|Fan[0-9]+ is|Thermal) alarm'

    ## BGP 容器中关键子进程退出
    func_extract_log 'bgp_process_exit' 'syslog' 'exited: (zebra|staticd|bgpd)'

    # 各容器停止日志
    func_extract_log 'container_stop' 'daemon' '(Stopped [A-Za-z]+ container|stopped: supervisor-proc-exit-listener)'

    # 从上方结果 ERR/WARNING 日志中再提取出仅包含 ERR 的日志（比例约 30 : 1）
    cd $SAVE_LOG_DIR
    for i in $(ls *_err_warn.log); do
        grep ERR $i > ${i%%_*}_err.log
    done

    # 简要展示 WARNING、ERR 总共行数
    echo "===================== $(date +%Y-%m-%d.%H:%M:%S) show ERR log counter ====================="
    wc -l *_err.log | sort -nr

    # 删除为空的文件
    find $SAVE_LOG_DIR/ -type f -empty -delete

    # 压缩日志文件
    cd $HOME
    tar -czf ${NETADMIN_NAME}_${DEV_IP}_${RUN_TIME}.tar.gz -C $HOME ${NETADMIN_NAME}_${DEV_IP}_${RUN_TIME}

    # 删除 临时暂存"捞取的异常日志"文件夹
    rm -rf $SAVE_LOG_DIR/

    # 上传压缩后文档到 NetAdmin 服务器
    func_upload_then_del_tar

    # expect 识别字段 "extract_error_log.sh finished"
    echo "===================== $(date +%Y-%m-%d.%H:%M:%S) extract_error_log.sh finished =================="
}

main

unset NETADMIN_NAME
unset DEV_IP
unset RUN_TIME
unset REMOTE_REPOSITORY
unset REMOTE_SFTP_REPOSITORY
unset SAVE_LOG_DIR
