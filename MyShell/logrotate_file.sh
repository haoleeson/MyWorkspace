#!/usr/bin/env bash

MAX_NUM=50

# 轮转历史归档文件（更名）
func_logrotate_file() {
    local DIR="$1"
    local FILE_PREFIX="$2"
    local FILE_SUFFIX="$3"

    if [ -f $DIR/${FILE_PREFIX}.1${FILE_SUFFIX} ]; then
        # 记录历史文件后缀到 nums 集合
        files=$(ls -t $DIR/${FILE_PREFIX}.*${FILE_SUFFIX})
        nums=(0)
        for file in $files
        do
            # num=${file##*.}
            num=$(echo $file | grep -oP \\d+)
            echo "nums[$num]=$num"
            nums[$num]=$num
        done

        # 轮转文件，历史后缀数字 + 1
        for ((i = ${#nums[@]} - 1; i > 0 && i < $MAX_NUM; i--))
        do
            num=${nums[$i]}
            if [ $num ]; then
                echo "mv $DIR/${FILE_PREFIX}.$num${FILE_SUFFIX} $DIR/${FILE_PREFIX}.$(($num+1))${FILE_SUFFIX}"
            fi
        done

        # 将当前压缩文件更名为 1
        echo "mv $DIR/${FILE_PREFIX}${FILE_SUFFIX} $DIR/${FILE_PREFIX}.1${FILE_SUFFIX}"
    fi
}


main() {
    func_logrotate_file "/var/log" "daemon.log" ".gz"
}

main
