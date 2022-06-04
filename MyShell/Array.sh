#!/usr/bin/env bash

# 定义数组方式1
china_citizen_name="Chinese"
array1=("I" "am" $china_citizen_name)

# 定义数组方式2
array2[0]="I"
array2[1]="love"
array2[2]="China"

# for 循环初始化数组
array3=(0)
for ((i = 0; i<=10; i++)); do
    # echo "i = $i"
    array3[$i]=$i
done


echo "----------::::获取数组1长度::::----------"
len1=${#array1[*]}; echo "get len of array1 is: $len1"

echo "----------::::获取数组2长度::::----------"
len2=${#array2[@]}; echo "get len of array2 is: $len2"

echo "----------::::获取数组3长度::::----------"
len3=${#array3[@]}; echo "get len of array3 is: $len3"

echo "----------::::获取对应下标的元素值::::----------"
get_2=${array1[1]}; echo "get element value of index two is: $get_2"

echo "----------::::获取所有元素值::::----------"
get_all=${array1[@]}; echo "get all element value of array1: $get_all"


echo "----------::::For循环依次遍历所有元素::::----------"
for ((i = 0; i<3; i++))
do
    echo "arr[$i] = ${array1[$i]}"
done


echo "----------::::For循环遍历指定下标元素::::----------"
for i in 0 2 3 # 此时下标溢出不会出错
do
    echo "arr[$i] = ${array2[$i]}"
done

echo "----------::::For循环遍历未知长度数组::::----------"
for value in ${array1[@]}
do
    echo "$value"
done

echo "----------::::While循环遍历未知长度数组::::----------"
i=0
while [ $i -lt ${#array1[@]} ]
do
    echo "arr[$i] = ${array1[$i]}"
    let i++
done
