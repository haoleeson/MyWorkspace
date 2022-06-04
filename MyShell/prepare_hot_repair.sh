#!/usr/bin/env bash

# Describe: 自动根据MR从远程服务器拉脚本和设备列表文件、自动补全配置环境，执行脚本和将运行日志汇总到远程服务器
# Param1:   远程服务器密码
# Param2:   指定日期（eg. 2022-03-31）

# 创建运行文件夹
mkdir -p ~/BIN14327 && cd ~/BIN14327
RUN_PATH=$(pwd)

PASSWD=$1
if [ ! $PASSWD ]; then
    PASSWD="e"
fi

# 执行日期
NOW_DATE=$(date +%Y-%m-%d)
if [ $2 ]; then
    NOW_DATE=$2
fi

# MR名
COMPUTER_ROOM=${HOSTNAME%%-*}
# 热修复脚本文件
SCRIPT_NAME='batch_hot_repair_BIN-14327.py'
# 热修复执行日志名（截取MR名）
LOG_NAME="$RUN_PATH/$NOW_DATE-BIN-14327-repair-$COMPUTER_ROOM.log"
# 远程修复文件仓库
REMOTE_REPOSITORY='admin@A.B.C.D:/home/admin/Repair_Operation_Files'


# 拉取 批量热修复脚本 和 待修复列表文件
expect -c "
spawn scp $REMOTE_REPOSITORY/$SCRIPT_NAME $RUN_PATH/
expect \"assword:\"
send \"$PASSWD\r\"

spawn scp $REMOTE_REPOSITORY/dev_list/$NOW_DATE/dev_info_$COMPUTER_ROOM.csv $RUN_PATH/
expect \"assword:\"
send \"$PASSWD\r\"
expect eof
"

# 脚本加执行权限
chmod u+x $RUN_PATH/$SCRIPT_NAME
# 检查待操作设备数
echo -e "\033[47;30m $(wc -l $RUN_PATH/dev_info_$COMPUTER_ROOM.csv | cut -d ' ' -f 1) \033[0m"

# 验证有无 pexpect 包(2.3)，并执行修复脚本
python2.6 -c 'import pexpect; print(pexpect.__version__)'
if [ "$?" != "0" ]; then
    echo "================== No pexpect Lib !!! =================="
    # 下拉 pexpect 包
    expect -c "
spawn scp $REMOTE_REPOSITORY/pexpect-2.3.tar.gz $RUN_PATH
expect \"assword:\"
send \"$PASSWD\r\"
expect eof
"
    # 解压 pexpect 包
    tar -xzf $RUN_PATH/pexpect-2.3.tar.gz
    # 将脚本移至解压后的 pexpect 包（能够正常执行）
    mv $RUN_PATH/$SCRIPT_NAME $RUN_PATH/pexpect-2.3/
    # 跳转至解压后的目录
    cd $RUN_PATH/pexpect-2.3/
    # 执行修复
    python2 $RUN_PATH/pexpect-2.3/$SCRIPT_NAME $RUN_PATH/dev_info_$COMPUTER_ROOM.csv $LOG_NAME
else
    # 直接执行修复
    $RUN_PATH/$SCRIPT_NAME $RUN_PATH/dev_info_$COMPUTER_ROOM.csv $LOG_NAME
fi

# 清除日志中回显的密码
sed -i 's/J3Q1\\XH69r=Nu2{//g' $LOG_NAME
# 清除日志空行
sed -i '/^\s*$/d' $LOG_NAME

# 检查成功操作数（标志字段）
echo "Check success operate num: $(grep 'notice \@\[' $LOG_NAME | wc -l)"

# 上传脚本执行日志
expect -c "
spawn scp $LOG_NAME $REMOTE_REPOSITORY/log/$NOW_DATE/
expect \"assword:\"
send \"$PASSWD\r\"
expect eof
"

unset NOW_DATE
unset COMPUTER_ROOM
unset PASSWD
unset SCRIPT_NAME
unset LOG_NAME
unset RUN_PATH
unset REMOTE_REPOSITORY
