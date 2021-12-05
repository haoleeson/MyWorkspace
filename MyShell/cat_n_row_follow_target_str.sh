#!/bin/bash

################################################
# 获取文件中目标字段及其下方 n 行
# Param1: 目标字段
# Param2: 目标文件
# Param3: 要展示的其下 n 行
################################################
cat_n_row_follow_target_str(){
    TARGET_STR=$1
    TARGET_FILE=$2
    FOLLOW_N_ROW=$3
    sed -n "$(grep -n "$TARGET_STR" $TARGET_FILE | tail -1 | cut -d : -f 1), +${FOLLOW_N_ROW}p" $TARGET_FILE
}

cat_n_row_follow_target_str 'MGMT_INTERFACE' '/etc/sonic/libra_user.json' '5'