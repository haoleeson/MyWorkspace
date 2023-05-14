#!/bin/bash

DATE="$(date +%Y_%m_%d)"
RES_DIR="/root/reboot_syncd_core_log_$DATE"

if [ -d $RES_DIR ]; then
    echo "dir '$RES_DIR' is existed, delete it."
    rm -rf $RES_DIR
fi

mkdir -p $RES_DIR/var_log_dir
mkdir -p $RES_DIR/var_core_dir
mkdir -p $RES_DIR/syncd_container

cp -rf /var/log/* $RES_DIR/var_log_dir/
cp -rf /var/core/* $RES_DIR/var_core_dir/
docker cp syncd:/bf_drivers.log $RES_DIR/syncd_container/

# 解析文件夹和路径字段
DIR_PWD=${RES_DIR%/*}
DIR_NAME=${RES_DIR##*/}

# 压缩
cd $DIR_PWD
tar -czf $DIR_NAME.tar.gz $DIR_NAME
