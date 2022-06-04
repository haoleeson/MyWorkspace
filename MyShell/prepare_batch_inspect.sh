#!/usr/bin/env bash

# Describe: 自动根据机房从远程服务器拉脚本和设备列表文件、自动补全配置环境，执行脚本和将运行日志汇总到远程服务器
# Param1:   MR_IP（可选）
# Param2:   指定日期（eg. 2022-04-12，可选）

if [ $1 ]; then
    NETADMIN_IP=$1
else
    NETADMIN_IP=''
    # 判断 IP 配置为 xxx.xxx.xxx.5 的数目（若小于 6 则用 xgbe1 IP 代替，大于等于6，传空让后续脚本自行拼接同网段.5） 
    DOT_5_NUM=$(ifconfig | grep -oP \(\\d+\\.\){3}5 | wc -l)
    if [ $DOT_5_NUM -lt 6 ]; then
        NETADMIN_IP="$(ip addr show xgbe1 | grep -oP '(\d+\.){3}\d+' | head -n +1)"
    fi
fi

# 执行日期
NOW_DATE=$(date +%Y-%m-%d)
if [ $2 ]; then
    NOW_DATE=$2
fi


EMAIL_PREFIX='xxx'
# 执行脚本文件
PY_SCRIPT_NAME='batch_log_inspect.py'
SH_SCRIPT_NAME='extract_error_log.sh'
# 远程修复文件仓库
REMOTE_REPOSITORY='xxx@A.B.C.D:/home/disk1/xxx/inspect_error_log/'
PASSWD='e'
# 机房名
MR_NAME=${HOSTNAME%%-*}
# 运行目录
RUN_PATH=$HOME/inspect_error_log
# 脚本执行日志名（截取机房名）
LOG_NAME="$RUN_PATH/${NOW_DATE}--${MR_NAME}--batch_log_inspect.log"


# 函数：准备脚本运行环境
func_prepare_environment() {
    # 创建运行文件夹
    mkdir -p $RUN_PATH/${MR_NAME}/ && cd $RUN_PATH/

    # 拉取 执行脚本 和 待修复列表文件
    expect -c "
spawn scp $REMOTE_REPOSITORY/$PY_SCRIPT_NAME $RUN_PATH/
expect \"assword:\"
send \"$PASSWD\r\"

spawn scp $REMOTE_REPOSITORY/$SH_SCRIPT_NAME $RUN_PATH/
expect \"assword:\"
send \"$PASSWD\r\"

spawn scp $REMOTE_REPOSITORY/dev_list/$NOW_DATE/dev_info_${MR_NAME}.csv $RUN_PATH/
expect \"assword:\"
send \"$PASSWD\r\"
expect eof
"

    # 拷贝捞取设备各类异常日志 Shell 脚本到 /tftpboot/
    cp ${RUN_PATH}/${SH_SCRIPT_NAME} /tftpboot/
    ls -l /tftpboot/${SH_SCRIPT_NAME}

    # 为批量执行 Python 脚本加执行权限
    chmod u+x $RUN_PATH/$PY_SCRIPT_NAME

    # 查看待操作设备数
    echo -e "\033[47;30m $(wc -l $RUN_PATH/dev_info_${MR_NAME}.csv | cut -d ' ' -f 1) \033[0m"
}


# 函数：执行操作
func_exec_operator() {
    cd $RUN_PATH/
    # 验证有无 pexpect 包(2.3)，并执行修复脚本
    python2.6 -c 'import pexpect; print(pexpect.__version__)'
    if [ "$?" != "0" ]; then
        echo "================== No pexpect Lib !!! =================="
        # 下拉 pexpect 包
        expect -c "
spawn scp $REMOTE_REPOSITORY/pexpect-2.3.tar.gz $RUN_PATH/
expect \"assword:\"
send \"$PASSWD\r\"
expect eof
"
        # 解压 pexpect 包
        tar -xzf $RUN_PATH/pexpect-2.3.tar.gz
        # 将脚本移至解压后的 pexpect 包（能够正常执行）
        mv $RUN_PATH/$PY_SCRIPT_NAME $RUN_PATH/pexpect-2.3/
        # 跳转至解压后的目录
        cd $RUN_PATH/pexpect-2.3/
        # 执行修复
        echo "python2 $RUN_PATH/pexpect-2.3/$PY_SCRIPT_NAME $RUN_PATH/dev_info_${MR_NAME}.csv $LOG_NAME $MR_NAME $NETADMIN_IP"
        python2 $RUN_PATH/pexpect-2.3/$PY_SCRIPT_NAME $RUN_PATH/dev_info_${MR_NAME}.csv $LOG_NAME $MR_NAME $NETADMIN_IP
    else
        # 直接执行修复
        echo "$RUN_PATH/$PY_SCRIPT_NAME $RUN_PATH/dev_info_${MR_NAME}.csv $LOG_NAME $MR_NAME $NETADMIN_IP"
        $RUN_PATH/$PY_SCRIPT_NAME $RUN_PATH/dev_info_${MR_NAME}.csv $LOG_NAME $MR_NAME $NETADMIN_IP
    fi
}


# 函数：操作后整理&上传操作
func_after_operator() {
    cd $RUN_PATH/

    if [ -f $LOG_NAME ]; then
        # 清除日志中回显的密码
        sed -i 's/J3Q1\\XH69r=Nu2{//g' $LOG_NAME
        # 清除日志空行
        sed -i '/^\s*$/d' $LOG_NAME
    fi

    # 检查成功操作数（标志字段）
    # echo "Check success operate num: $(grep 'notice \@\[' $LOG_NAME | wc -l)"

    # 将 /tftpboot/ 中暂存的异常日志文档 移动到归档本目录
    mv /tftpboot/${MR_NAME}_*.tar.gz $RUN_PATH/${MR_NAME}/

    # 删除 /tftpboot/ 暂存的执行脚本
    if [ -f /tftpboot/$SH_SCRIPT_NAME ]; then
        rm -rf /tftpboot/$SH_SCRIPT_NAME
    fi

    # 上传脚本执行日志
    expect -c "
set timeout 15
spawn scp $LOG_NAME $REMOTE_REPOSITORY/run_log/$NOW_DATE/
expect \"assword:\"
send \"$PASSWD\r\"
expect eof
"
    sleep 1s

    # 上传归档文件
    for i in $(ls $RUN_PATH/${MR_NAME}/${MR_NAME}_*.tar.gz); do
        upload_cmd_str="scp $i $REMOTE_REPOSITORY/err_log_tar/${MR_NAME}/"
        expect -c "
set timeout 60
spawn $upload_cmd_str
expect {
    \"*assword:*\" { send \"$PASSWD\r\"; exp_continue}
    \"*$EMAIL_PREFIX@$HOSTNAME*\" { send \"\n\"; exp_continue}
    eof
}
"
        sleep 1s
    done
}


# 主函数
main() {
    # 准备脚本运行环境
    func_prepare_environment

    # 执行操作
    func_exec_operator

    # 操作后整理&上传操作
    func_after_operator
}

main

unset NOW_DATE
unset MR_NAME
unset PASSWD
unset PY_SCRIPT_NAME
unset LOG_NAME
unset RUN_PATH
unset REMOTE_REPOSITORY
