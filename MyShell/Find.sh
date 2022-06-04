#!/bin/bash

# 1. 根据 文件自身属性 查找
## 1.1. 根据 文件名查找
sudo find ./ -name *sub_file_name*

## 1.2. 根据 文件类型 查找
### 1.2.1. 根据 文件类型（文件类型，不含符号链接文件）查找
sudo find ./ -type f

### 1.2.2. 根据 文件类型（目录类型）查找
sudo find ./ -type d

### 1.2.3. 根据 文件类型（符号链接文件类型）查找
sudo find ./ -type d

## 1.3. 根据 文件大小 查找
 <!-- + 表示大于，- 表示小于； c 表示字节、w 表示字、b 表示512位元组区块、k、M、G -->
sudo find ./ -size +1M

## 1.4. 根据 文件/目录是否为空 查找
sudo find ./ -empty

## 1.5. 根据 文件/目录权限 查找
sudo find ./ -perm -0644

## 1.6. 根据 文件所有者 查找
sudo find ./ -user user_name

## 1.7. 根据 文件所属组 查找
sudo find ./ -group group_name

## 1.8. 根据 文件所属组 查找
sudo find ./ -group group_name

## 根据 文件深度 查找
### 从指定目录下最深的子目录开始查找
sudo find /etc/ -depth

### 限定 最大目录层级 查找
sudo find /etc/ -maxdepth 2

### 限定 最小目录层级 查找
sudo find /etc/ -mindepth 2


# 2. 根据被使用情况 查找

## 2.1. 根据上一次访问时间 查找（3天内访问过access time）
sudo find ./ -atime - 3

## 2.2. 根据上一次创建时间 查找（3天内创建过create time）
sudo find ./ -ctime - 3

## 2.3. 根据上一次修改时间 查找（3天内修改过modify time）
sudo find ./ -mtime - 3

## 2.4. 根据上一次访问时间 查找（3分钟内访问过access time）
sudo find ./ -amin - 3

## 2.5. 根据上一次创建时间 查找（3分钟内创建过create time）
sudo find ./ -cmin - 3

## 2.6. 根据上一次修改时间 查找（3分钟内修改过modify time）
sudo find ./ -mmin - 3

