layout: post
title: Linux常用工具指令
date: 2020/05/29 21:44:30
updated: 2025/5/17 7:21:45
comments: true
tags:
- Shell
categories:
- 技术

---
<img src="../../../../uploads/ConfusedShellLang.jpg" class="full-image" />

Linux是一款开源、稳定且高度可定制的类Unix操作系统，凭借其卓越的性能、强大的安全性和庞大的开源生态，在后端服务领域占据绝对霸主地位，本文记录一些工作中常用的Linux工具和指令。

<!-- more -->

# 1. Shell
## 1.1. 变量判空
- 判空必要性：某些环境下执行空变量可能造成严重后果，如执行 rm 删除操作时，rm -rf 空路径变量会删除根目录，造成无法挽回的严重后果。
- 正确操作：
```Shell
#!/bin/bash
# 判断 DIR 变量非空，才会执行 rm 命令
[ -n $DIR ] && rm -rf $DIR
```
- 变量判空常用方法
```Shell
#!/bin/bash
para=
# 判空方式 1. 直接判断变量
if [ ! $para ];then
    echo "NULL"
fi
# 判空方式 2. 作字符串判空
if [ ! -n "$para" ];then
    echo "NULL"
fi
# 判空方式 3. 与“空字符串”比较判空
if [ "$para" = "" ];then
    echo "NULL"
fi
# 判空方式 4. 利用 test 判空
if test -z "$para"
then
    echo "NULL"
fi
```

## 1.2. 变量转大小写
```shell
str='HelLo World'
# 变量转换为大写
upper_str=${str^^}
upper_str=$(echo "$str" | tr [a-z] [A-Z])
upper_str=$(echo "$str" | tr [:lower:] [:upper:])
# 变量转换为小写
lower_str=${str,,}
lower_str=$(echo "$str" | tr [A-Z] [a-z])
lower_str=$(echo "$str" | tr [:upper:] [:lower:])
```

## 1.3. 变量替换：四种模式匹配替换
- \# 是去掉左边（在键盘上、#在、$之左边）；
- \% 是去掉右边（在键盘上、%在、$之右边）；
- \#和、%中的单一符号是最小匹配，两个相同符号是最大匹配。
- 这四种模式中都不会改变 variable 的值，其中，只有在 pattern 中使用了、*匹配符号时，%和%%，#和##才有区别。
- 结构中的 pattern 支持通配符：
  - \*表示零个或多个任意字符
  - \? 表示仅与一个任意字符匹配
  - [...] 表示匹配中括号里面的字符
  - [!...] 表示不匹配中括号里面的字符

**模式 1：${variable%pattern}**

说明：shell 在 variable 中查找，判断 variable 是否以 pattern 结尾，如果是，就从命令行把 variable 中的内容去掉右边**最短的**匹配模式

**模式 2：${variable%%pattern}**

说明：shell 在 variable 中查找，判断 variable 是否以 pattern 结尾，如果是，就从命令行把 variable 中的内容去掉右边**最长的**匹配模式

**模式 3：${variable#pattern}**

说明：shell 在 variable 中查找，判断 variable 是否以 pattern 开始，如果是，就从命令行把 variable 中的内容去掉左边最短的匹配模式

**模式 4：${variable##pattern}**

shell 在 variable 中查找，判断 variable 是否以 pattern 开始，如果是，就从命令行把 variable 中的内容去掉右边最长的匹配模式
```Shell
#!/bin/bash

VAR=ABCABCDEFDEF
PATTERN1=DEF
PATTERN2=ABC

echo "VAR=$VAR"
echo "PATTERN1=$PATTERN1"
echo "PATTERN2=$PATTERN2"

echo 'M1.${VAR%*$PATTERN1}'
echo ${VAR%*$PATTERN1}

echo 'M2.${VAR%%*$PATTERN1}'
echo ${VAR%%*$PATTERN1}

echo 'M2.${VAR%%?$PATTERN1}'
echo ${VAR%%?$PATTERN1}

echo 'M3.${VAR#*$PATTERN2}'
echo ${VAR#*$PATTERN2}

echo 'M4.${VAR##*$PATTERN2}'
echo ${VAR##*$PATTERN2}

echo 'M4.${VAR##$PATTERN2*}'
echo ${VAR##$PATTERN2*}

# 执行结果
VAR=ABCABCDEFDEF
PATTERN1=DEF
PATTERN2=ABC
M1.${VAR%*$PATTERN1}
ABCABCDEF
M2.${VAR%%*$PATTERN1}
（空）
M2.${VAR%%?$PATTERN1}
ABCABCDE
M3.${VAR#*$PATTERN2}
ABCDEFDEF
M4.${VAR##*$PATTERN2}
DEFDEF
M4.${VAR##$PATTERN2*}
（空）
```

## 1.4. 变量特殊值替换
几种特殊的替换用法：
- 若变量为空，则用默认值执行${var:-string}
```Shell
#!/bin/bash
var=
echo ${var:-NULL}
echo $var

# 执行结果如下：
NULL
```
- 若变量为空，则用默认值赋值给空变量${var:=abc}
```Shell
#!/bin/bash
var=
echo ${var:=abc}
echo $var

# 执行结果如下：
abc
```
- 若变量非空，则用默认值执行，若变量为空，则不作为${var:+string}
```Shell
#!/bin/bash
var1=abc
var2=
echo ${var1:+FULL}
echo ${var2:+FULL}

# 执行结果如下：
FULL
```
- 若变量非空，则用其值，若变量为空，则输出 string 到标准错误中后退出脚本${var:?string}
```Shell
#!/bin/bash
var1=abc
var2=
echo ${var1:+FULL}
echo ${var2:+FULL}

# 执行结果如下：
FULL
```

## 1.5. 变量切分
字符变量切分
```shell
str1="I am chinese"
# 根据空格分割为数组
array1=(${str1// / })
```

## 1.6. 变量长度
```shell
# 获取字符串变量长度
STR='hello'; echo ${#STR}
```

## 1.7. 变量截取
字符串变量截取
### 1.7.1. 头部截取（最大 -* 匹配）
从右往左匹配最后遇到的'-'字符及之后的部分（减掉表达式"-*"最大匹配的部分"-serial-14210"），结果："/dev/tty.usb"
```shell
STR="/dev/tty.usb-serial-14210"; echo ${STR%%-*}
```

### 1.7.2. 头部截取（最小 -* 匹配）
从右往左匹配最先遇到的'-'字符及之后的部分（减掉表达式"-*"最大匹配的部分"-14210"），结果："/dev/tty.usb-serial"
最后一个'-'之前的部分，结果："/dev/tty.usb-serial"
```shell
STR="/dev/tty.usb-serial-14210"; echo ${STR%-*}
```

### 1.7.3. 尾部截取（ *- 最大匹配）
从左往右匹配最后遇到的'-'字符及之前的部分（减掉表达式"*-"最大匹配的部分"/dev/tty.usb-serial-"），结果："14210"
```shell
STR="/dev/tty.usb-serial-14210"; echo ${STR##*-}
```

### 1.7.4. 尾部截取（ *- 最小匹配）
从左往右匹配最先遇到的'-'字符及之前的部分（减掉表达式"*-"最小匹配的部分"/dev/tty.usb-"），结果："serial-14210"
```shell
STR="/dev/tty.usb-serial-14210"; echo ${STR#*-}
```

## 1.8. 单行命令执行 FOR 循环
```shell
for i in 1 3 5 7 9; do echo "num = $i" ;done
for ((i = 0; i<=10; i++)); do echo "num = $i" ;done
```

## 1.9. 支持 POSIX 标准的扩展计算
```shell
$((exp))
```

其中 exp 为符合 C 语言的运算符，示例如下
```Shell
#!/bin/bash
echo $((1+2))
echo $((1<2))
echo $((5<4?0:1))
echo $((var=2+3))
echo $((var++))
# 执行结果如下：
3
1
5
6
```

## 1.10. 脚本中获取当前脚本所在文件夹路径
```shell
#!/usr/bin/env bash
# echo $(dirname $0)
SCRIPT_LOCATION="$( cd "$(dirname "$0" )" && pwd )"
echo "Script location: ${SCRIPT_LOCATION}"
```

## 1.11. cut 截取命令 （以截取 ip "192.168.3.35/24"中'/'字符前部为例）
```shell
ip addr | grep 'eth0' | awk '{ print $2 }' | cut -d / -f 1
```

## 1.12. 求取一行数字最大值
```shell
cat 1 | sed 's/PCI-MSI.*//' | cut -d : -f2- | awk '{ maxnum=0; for(i=1;i<=NF;i++) if ($i>maxnum) maxnum=$i; print maxnum }'
```

## 1.13. 打印彩色字体
```shell
echo -e "\033[30m 黑色字 \033[0m"
echo -e "\033[31m 红色字 \033[0m"
echo -e "\033[32m 绿色字 \033[0m"
echo -e "\033[33m 黄色字 \033[0m"
echo -e "\033[34m 蓝色字 \033[0m"
echo -e "\033[35m 紫色字 \033[0m"
echo -e "\033[36m 天蓝字 \033[0m"
echo -e "\033[37m 白色字 \033[0m"

echo -e "\033[40;37m 黑底白字 \033[0m"
echo -e "\033[41;37m 红底白字 \033[0m"
echo -e "\033[42;37m 绿底白字 \033[0m"
echo -e "\033[43;37m 黄底白字 \033[0m"
echo -e "\033[44;37m 蓝底白字 \033[0m"
echo -e "\033[45;37m 紫底白字 \033[0m"
echo -e "\033[46;37m 天蓝底白字 \033[0m"
echo -e "\033[47;30m 白底黑字 \033[0m"
```

## 1.14. 输出内容的 字符替换 & 字符删除
```shell
# 替换
echo 'ABCDABCD' | sed 's/ABC/DEF/g'
# tr 替换，注意是字符集合替换
echo 'ABCDABCD' | tr 'AD' 'C'

# 删除
echo 'ABCDABCD' | sed 's/ABC//g'
echo 'ABCDABCD' | tr -d 'AC'
```

## 1.15. 逐行读文件，并处理
```shell
cat file | while read line; do echo "Line contents are : ${line} " ;done

# 示例： 逐行读 file 中的设备，并执行操作
cat file | while read line; do echo "${line} $(grep -oP 'HwSKU: [A-Z0-9]{5,}'  ./${line}_*--*/*--device_status)"  ;done
```

## 1.16. shell 脚本中临时调用 pexpect
```shell
expect -c "
spawn scp admin@10.32.19.100:/home/admin/pexpect-2.3.tar.gz $RUN_PATH

expect \"assword:\"
send \"$PASSWD\r\"
expect eof
"
```

# 2. 查询

## 2.1. 显示文件列表
```shell
ls -l -A --color=auto --group-directories-first /var/log/
```

## 2.2. 查看指定程序的 CPU 占用、内存占用
```shell
# 设备的整体 CPU 使用率
cat /proc/stat | grep cpu | head -1 | awk '{print ($5*100)/($2+$3+$4+$5+$6+$7+$8+$9+$10)}'| awk '{print 100-$1}'

# CPU 占用
ps -p $(ps -ef | fgrep -v 'grep' | grep "process_name" | head -n +1 | awk '{ print $2 }') -o %cpu | tail -n +2

# 内存占用
STR=$(grep 'VmRSS' /proc/$(ps -ef | fgrep -v 'grep' | grep "process_name" | head -n +1 | awk '{ print $2 }')/status); echo ${STR##*:}
```

## 2.3. 查看磁盘占用情况
```shell
sudo du -h --max-depth=1 ./ 2>&1 | fgrep -v 'cannot'
sudo du -sh /*  2>&1 | fgrep -v 'cannot' | sort -nr
```

## 2.4. 查看当前用户是否为 root 用户
```shell
if [ $UID == 0 ];then
  echo "you are root"
fi
```

## 2.5. 查看个人进程
```shell
ps -ef | grep admin |fgrep -v vscode | fgrep -v baas
```

## 2.6. 查看内存大小
```shell
free -h
```

## 2.7. 列出已安装软件包
```shell
dpkg -l | grep ''
```

## 2.8. 查询指定字段在文本中的行数
```shell
grep -n <target_string> <file_path>

# 提取最早出现行数
grep -n <target_string> <file_path> | tail -1 | cut -d : -f 1
# 提取最后出现行数
grep -n <target_string> <file_path> | tail -1 | cut -d : -f 1
```

## 2.9. 输出内容的 字符替换 & 字符删除
```shell
# 替换
echo 'ABCDABCD' | sed 's/ABC/DEF/g'
# tr 替换，注意是字符集合替换
echo 'ABCDABCD' | tr 'AD' 'C'

# 删除
echo 'ABCDABCD' | sed 's/ABC//g'
echo 'ABCDABCD' | tr -d 'AC'
```

## 2.10. 统计第 2 列总类型
```shell
command | awk '{ print $2 }' | uniq | sort | uniq

cat ~/1.txt  | awk '{ for(i=2;i<=NF;i++) printf $i""FS;print "" }' | uniq | sort | uniq
```

## 2.11. 只打印 第 n~最末 列
```shell
cat xxx.log | awk '{ for(i=1; i<=3; i++){ $i="" }; print $0 }'
```

## 2.12. grep 查找命令说明
```shell
-r 是递归查找
-n 是显示行号
-R 查找所有文件包含子目录
-i 忽略大小写

# 增加显示匹配行的 前后各 [number] 行
grep -C number pattern files

# 增加显示匹配行的 前的 [number] 行
grep -B number pattern files

# 增加显示匹配行的 后的 [number] 行
grep -A number pattern files

# 反向查找 “不匹配” 的行
grep -v dis_pattern files

# 正则表达式查找 1
grep -E "[1-9]+"

# 正则表达式查找 2
egrep "[1-9]+"

# 不显示错误信息
grep -s

# 按匹配文件中内容查询
grep -f pattern_file file

# 不区分大小写地搜索。默认情况区分大小写，
grep -i pattern files
# 只列出匹配的文件名，
grep -l pattern files
# 列出不匹配的文件名，
grep -L pattern files
# 只匹配整个单词，而不是字符串的一部分（如匹配‘magic’，而不是‘magical’），
grep -w pattern files

# 显示匹配 pattern1 或 pattern2 的行，
grep pattern1 | pattern2 files
# 显示既匹配 pattern1 又匹配 pattern2 的行。
grep pattern1 files | grep pattern2

```
grep -a "systemd" /var/log/daemon.log | grep "snmp"
grep -a "systemd" | "snmp" /var/log/daemon.log

--group-directories-first

## 2.13. 倒序查看 n 行 符合条件行
```shell
sudo grep -E 'Psu|Fan|Sff|Linecard' /var/log/syslog | sort -r | head -n 40
```

## 2.14. 查看某容器中 打印到 某文件的进程列表
```shell
grep -a "bgp" /var/log/syslog | awk '{ print $7 }' | uniq | sort | uniq
grep -a "bgp" /var/log/user.log | awk '{ print $7 }' | uniq | sort | uniq
```

## 2.15. 查看某进程打印日志的类别 列表
```shell
grep -a "database" /var/log/user.log | awk '{ print $4 }' | uniq | sort | uniq
grep -a "bgp\#zebra" /var/log/quagga/zebra.log | awk '{ print $4 }' | uniq | sort | uniq
grep -a "swss\#supervisord" /var/log/syslog | awk '{ print $4 }' | uniq | sort | uniq

grep -a "snmp\#snmpd" /var/log/daemon.log
```

## 2.16. 文件

### 2.16.1. Linux 文件类型说明
b  块设备，是一些提供系统存取数据的接口设备，例如硬盘。
c  字符设备，是一些串行端口的接口设备，例如键盘、鼠标、打印机、tty 终端。
d  目录，类似于 Windows 的文件夹。
l  链接文件，类似于 Windows 的快捷方式。
s  套接字文件（socket），用于进程之间的通信。
-  文件，分纯文本文件（ASCII）和二进制文件（binary）。

### 2.16.2. 按文件大小排序
```shell
ls -alSh
```

### 2.16.3. 获知文件创建时间（stat）
```shell
# stat -c %y <file_path>
stat -c %y /home/admin/testfile

# 获取文件创建日期
stat -c %y /home/admin/testfile | cut -d \  -f 1
```

### 2.16.4. 查看文件创建时间（debugfs）
```shell
# 获取文件 inode 号
INODE_NUM=$(ls -i /var/log/swss/swss.rec | awk '{ print $1 }')

# 获取文件所挂载磁盘
PAN=$(df -h /var/log/ | tail -n +2 | awk '{ print $1 }')

# 查看文件创建时间
debugfs -R "stat <$INODE_NUM>" $PAN
debugfs -R "stat <$(ls -i /var/log/swss/swss.rec | awk '{ print $1 }')>" $(df -h /var/log/ | tail -n +2 | awk '{ print $1 }')
```

### 2.16.5. 查看指定时间内修改过的文件
```shell
# 查看昨天到今天（过去一天/24小时）内修改过的 syslog* 文件
cd /var/log/ && find ./ -maxdepth 1 -name 'syslog*' -mtime -1 | sort

# 反之：查看一天以前修改过的文件
find /var/log/ -mtime +1

# 查看过去 5 分钟内修改过的代码
find /var/log/ -mmin -5

# 查看 2022-02-15 0:00:00 之后修改过的文件
find /var/log/ -type f -newermt '4/23/2022 0:00:00'
```

### 2.16.6. 查看指定时间段修改过的文件
```shell
rm /tmp/start > /etc/null 2>&1; touch --date "2022-05-04 00:00:00" /tmp/start
rm /tmp/end > /etc/null 2>&1; touch --date "2022-12-30 23:00:00" /tmp/end

# 查看指定日期之后的日志
find /var/log/ -type f -newer /tmp/start -ls
# 查看指定时段内的日志（区间左闭右开）
cd /var/log/; find -type f -name 'syslog*' -newer /tmp/start -not -newer /tmp/end -printf "%T@\t%p\n" | sort -n | cut -f 2-
```

### 2.16.7. 比较二进制文件
```shell
cmp [options] <file1> <file2>

# Options
# -c 或 --print-chars                         除了标明差异处的十进制字码之外，一并显示该字符所对应字符
# -i <字符数目> 或 --ignore-initial=<字符数目>  指定字符数
# -l 或 --verbose                             标示出所有不一样的地方
# -s 或 --quiet 或--silent                      不显示错误信息
# -v 或 --version                             显示版本信息
# --help  在线帮助
```

### 2.16.8. 查找文件（过滤无效信息）
```shell
sudo find / -name "makefile" -print 2>&1 | fgrep -v "Operation not permitted" | fgrep -v "No such file"
```

### 2.16.9. 输出内容到文件（含换行）
printf  '%s\n' <文本内容> > <文件名>

```shell
FILE_PATH='/home/haoleeson/2'
printf  '%s\n' \
        '#!/bin/sh' \
        'set -e' \
        'rm -f /etc/ld.so.conf.d/bfn-sde.conf' \
        'rm -f /usr/lib/libsai.so' \
        'ldconfig' \
        'rm -f /usr/include/sai' > $FILE_PATH
```

### 2.16.10. 清空文件内容
```shell
cat /dev/null > finename
```

### 2.16.11. 查看打开文件的进程
```shell
lsof file_name 2>&1
```

### 2.16.12. 查看状态为 delete 的僵尸文件
```shell
sudo lsof 2>&1 |grep delete
```

### 2.16.13. 查看链接默认搜索库路径
```shell
ld --verbose | grep SEARCH_DIR | tr -s ' ;' \\012
```

# 3. 修改

## 3.1. 删除空文件
```shell
find ./ -type f -empty -delete
```

## 3.2. 向文件中随机填入指定大小值
```shell
# 追加填充
head -c 10M < /dev/urandom >> /var/log/log-file
```

## 3.3. Linux 修改日期 & 时间
```shell
# 更改为 2020 年 5 月 20 号
sudo date -s '5/20/2020 12:00:00'
sudo date -s '2024-05-26 16:49:40'

# 时间写入 bios【硬件】
sudo hwclock -w

# 查看 bios 时间
sudo hwclock -r
```

## 3.4. 开发机添加新用户命令
```shell
# 查询是否存在 "username" 用户
awk -F':' '{ print $1}' /etc/passwd | grep username

# 创建用户
useradd -m username

# 编辑所属组（添加 docker 组）
usermod -G username,docker username

# 添加用户到 docker 组
sudo usermod -aG docker ${USER}
sudo gpasswd -a ${USER} docker

# 查询当前 docker 组用户列表
sudo cat /etc/group | grep docker

# 添加密码
passwd username

# 更改密码
passwd

# 清空用户密码
passwd -d username

# 添加 root 权限
username ALL=(ALL:ALL) ALL

# 删除用户账号
userdel username
```

## 3.5. sed
### 3.5.1. 删除文件空行
```shell
sed -i '/^\s*$/d' <path_to_file>
```

### 3.5.2. 删除包含指定字段的行
```shell
sed -i '/vm.nr_hugepages/d' 2.txt
```

### 3.5.3. 删除某字符至行尾
```shell
sed -i '' -E 's/ +\|[ 0-9\+]+$//g' /Users/admin/Downloads/1
```

### 3.5.4. 正则字符串替换
```shell
type='json'
sed -i '' -E "s/[\._0-9a-zA-Z]+\\.$type/*.json/g" /Users/admin/Downloads/1
```

### 3.5.5. 查看文件中 指定行 内容
```shell
sed -n '5,10p' ${filename}
sed -n '87226,87250p' /var/log/quagga/bgpd.log
```

### 3.5.6. 获取文件中目标字段及其下方 n 行
```shell
sed -n "$(grep -n '目标字段' /etc/sonic/libra_user.json | tail -1 | cut -d : -f 1), +5p" /etc/sonic/libra_user.json
sed -n "$(grep -n 'PORTCHANNEL_MEMBER' /etc/sonic/libra_user.json | tail -1 | cut -d : -f 1), +5p" /etc/sonic/libra_user.json
# 或
grep -A 10 'string' path_to_file
```

## 3.6. 文本替换

### 3.6.1. 替换文件字段
（支持正则）
```shell
sed -i 's/AAA [0-9]\+/BBB 123/g' /etc/rsyslog.conf
sudo sed -i 's/*.* @/local2.notice @/g' /etc/rsyslog.conf

sed -i 's;logfile \"\";logfile \"/var/log/redis/redis.log\";g'

sed -i 's/vm\.nr_hugepages = [0-9]\+/vm\.nr_hugepages = 71680/g' /etc/sysctl.conf
```

### 3.6.2. 替换换行符
```shell
# 压缩行
sed -i ':a;N;$!ba;s/\n        Port/        Port/g' 2
sed -i ':a;N;$!ba;s/\n            Interface/            Interface/g' 2
sed -i ':a;N;$!ba;s/\n                type/                type/g' 2
sed -ri ':a;N;$!ba;s/\n    build:\n/\n    build:\n      network: host\n/g' 2

# 展开行 (on MAC)
sed -i '' 's/        Port/\n        Port/g' ~/Downloads/3
sed -i '' 's/            Interface/\n            Interface/g' ~/Downloads/3
sed -i '' 's/                type:/\n                type:/g' ~/Downloads/3
```

### 3.6.3. 跨行替换 2
```shell
sed -z 's/    build:\n/    build:\n      network: host\n/g' -i /Users/admin/Downloads/4
```

### 3.6.4. 批量替换
```shell
FILE='tests/p4gw_test/xgw_test_for_hpa.py'
for ((i=33; i<65; i++)); do echo "s/ethernet$i/ethernet$((i-32))/g" ;done

# linux
for ((i=33; i<65; i++)); do sed -i "s/ethernet$i/ethernet$((i-32))/g" $FILE ;done

# MACOS
for ((i=0; i<7; i++)); do echo "sed -i '' \"s/    to_port = $((i+20))/    to_port = $i/g\"" $FILE ;done
for ((i=0; i<7; i++)); do sed -i '' "s/    to_port = $((i+20))/    to_port = $i/g" $FILE ;done
for ((i=0; i<7; i++)); do sed -i '' "s/    from_port = $((i+20))/    from_port = $i/g" $FILE ;done

```

### 3.6.5. XML 文件转义字符恢复
```shell
XML_FILE='test.xml'
sed -i '' 's/&amp;/&/g' $XML_FILE
sed -i '' 's/&lt;/</g' $XML_FILE
sed -i '' 's/&gt;/>/g' $XML_FILE
sed -i '' 's/&quot;/"/g' $XML_FILE
sed -i '' "s/&apos;/'/g" $XML_FILE
```

# 4. 工作常用工具&指令

## 4.1. 解压缩
### 4.1.1. 压缩/解压 tar
```shell
# 压缩文件（-C 指定执行压缩目录，就只会记相对路径信息）
tar -cf filename.tar -C /home/admin /filename

# （不解压）查看文档内容
tar -tf filename.tar

# 解压 tar
tar -xf filename.tar
```

### 4.1.2. 压缩/解压 gz
```shell
# 压缩 gz（保留源文件）
gzip -c ABC-001.log > ABC-001.log.gz
# 解压 gz（保留源文件）
gunzip -c ABC-003.log.gz > ABC-003.log
```

### 4.1.3. 解压 .deb 包
```shell
# 解压 .deb 包
ar vx test.deb
# 解压 tar.xz 包（解压成 xxx.tar）
xz -d data.tar.xz
# 再解压 tar 包
tar -xf data.tar

# 三合一
ar vx test.deb; xz -d data.tar.xz; tar -xf data.tar
```

## 4.2. SSH
### 4.2.1. SSH 参数
```shell
# - P 指定访问目标设备的端口号
ssh -p 2223 admin@192.168.0.3

# -J 跳板机设备
ssh -J 'jump-proxy-A.B.C.D.org' root@10.172.0.3

# --silent 静默模式（拒绝一些提示信息）
ssh --silent admin@192.168.0.3

# -6 访问 v6 地址
ssh -6 admin@fe20::3

# IP_ADDR%[] 指定访问出接口
ssh admin@192.168.0.3%eth2
```

### 4.2.2. 查看 SSH 配置
```shell
# 查看 SSH “连接用户上限”配置值
sudo grep -r '^ClientAliveCountMax' /etc/ssh/sshd_config

# 查看 SSH “无操作自动退出”配置值（单位：秒）
sudo grep -r '^ClientAliveInterval' /etc/ssh/sshd_config

# 统计 ssh 在线人数
w | grep pts | wc -l
```

### 4.2.3. 查看用户自定义 SSH 配置
```shell
cat ~/.ssh/config
```

### 4.2.4. 生成 ssh 密钥
```shell
ssh-keygen -o -t rsa -C "haoleeson@outlook.com" -b 4096
```

## 4.3. Tmux
### 4.3.1. 登录tmux
```shell
tmux a -t $(tmux ls | grep session | awk '{ print $1 }' | cut  -d \: -f 1)
```

### 4.3.2. tmux 常用命令

```shell
# 新建会话
tmux new -s user_session_name

# 查看已创建的会话
tmux ls

# 进入一个已创建的会话
tmux a -t user_session_name

# 暂时跳出当前会话（快捷键）
# 1. 先按 control + B 后松开（触发 tmux 功能键监听）
# 2. 再按 D （跳出会话窗口）

# Kill 远程会话
tmux kill-session -t user_session_name
```

### 4.3.3. tmux 快捷键
均为先按 ctrl + b，放开后再按：
- 分屏
  - 水平向： %
  - 垂直向： "
- 光标切换： o
- 会话终端切换： s
- 退出终端窗口： d
- 终止终端窗口： &
- 在当前窗口基础上再开一个新窗口： c
- 关闭所有分屏后的窗口： !
- 终端内显示时间： t
- 显示终端编号：q

## 4.4. MySQL
### 4.4.1. Mac 安装 Microsoft SQL server container
> [MacOS配置Sql Server环境](https://blog.csdn.net/QAZJOU/article/details/123276681)

**docker - Setting - Docker Engine - 添加 中科大源**
```json
"registry-mirrors": [
  "https://docker.mirrors.ustc.edu.cn"
]
```

```shell
# 拉取 Microsoft SQL server 容器镜像
sudo docker pull mcr.microsoft.com/mssql/server:2022-latest

# 创建 sql_server 服务容器 (用户名 sa，密码 root@123 ，端口 1433 )
docker run -d --name sql_server_2022 \
    -e 'ACCEPT_EULA=Y' -e 'SA_PASSWORD=root@123' -p 1433:1433 \
    mcr.microsoft.com/mssql/server:2022-latest
```

### 4.4.2. Mac 安装 MySQL container
```shell
# 拉取 MySQL 容器镜像
docker pull mysql/mysql-server

# 创建 mysql 服务容器 (用户名 root，密码 root@123 ，端口 3306 )
docker run -dit --name mysql_server \
    -e 'MYSQL_ROOT_PASSWORD=root@123' -p 3306:3306 \
    mysql/mysql-server

# 登录容器中 MySQL
docker exec -it mysql_server mysql -u root -proot@123

# 或
mysql -h 127.0.0.1 -u root --port=3306 -p
mysql -h 172.23.0.3 -u root --port=3306 -p

# 运行 root 可以通过任何客户端连接（否则容器外无法连接）
CREATE USER 'root'@'%' IDENTIFIED BY 'root@123';
grant all on *.* to 'root'@'%';
ALTER USER 'root'@'%' IDENTIFIED WITH mysql_native_password BY 'root@123';
# check
SELECT host, user FROM mysql.user;
```

## 4.5. etcd
### 4.5.1. 安装 etcdctl
```shell
ETCD_NAME='etcd-v3.5.16-linux-amd64'
wget https://github.com/etcd-io/etcd/releases/download/v3.5.0/${ETCD_NAME}.tar.gz
tar -xvf ${ETCD_NAME}.tar.gz
sudo mv ${ETCD_NAME}/etcdctl /usr/local/bin/
ETCDCTL_API=3 etcdctl version
```

### 4.5.2. 查看特定表项数据
```shell
etcdctlargs="--endpoints=10.180.254.138:2379 --cacert /etc/pki/CA/cacert.pem --cert /etc/pki/etcd/clientcert.pem --key /etc/pki/etcd/clientkey.pem"
etcdctlargs="--endpoints=cc-etcd-4fa68f17f4c5.config.inner.ivolces.com:2379 --cacert /etc/pki/CA/cacert.pem --cert /etc/pki/etcd/clientcert.pem --key /etc/pki/etcd/clientkey.pem"

ETCDCTL_API=3 etcdctl $etcdctlargs get --prefix  "/data/yourtable"
```

### 4.5.3. 查看主节点
```shell
ETCDCTL_API=3 etcdctl $etcdctlargs get --prefix "/data/leader/" | head -2
```

### 4.5.4. 删除特定 key
```shell
etcdctl $etcdctlargs del --from-key "/data/yourtable123456"
```

## 4.6. Pytest + allure 生成自动测试报告
```shell
# --alluredir 指定 allure 报告数据存档路径
pytest --alluredir=myPytestCase/tmp myPytestCase/test_demo6_param.py

# 执行命令浏览器打开报表
allure serve myPytestCase/tmp

# 生成 html 报表文件到指定目录
# allure generate <报表源数据目录> -o <html_output>
allure generate myPytestCase/tmp --clean -o myPytestCase/html_output
```

## 4.7. 安装 node.js
```shell
# 安装 version 14 （debian 9）
sudo su
curl -fsSL https://deb.nodesource.com/setup_14.x | bash - &&\
apt-get install -y nodejs

# 安装 version 19
sudo su
curl -fsSL https://deb.nodesource.com/setup_19.x | bash - &&\
apt-get install -y nodejs
```

## 4.8. 安装 xunit-viewer
```shell
sudo su
npm i -g xunit-viewer
# check
xunit-viewer --help
```

## 4.9. vscode 多关键字查询
```shell
(word1[\s\S]*word2) | (word2[\s\S]*word1)
```

## 4.10. vscode 正则匹配中文字  [\u4e00-\u9fa5]、
```shell
# [\u4e00-\u9fa5]、#
## \d+.\d+ ##
### \d+.\d+.\d+ ###
```

## 4.11. Python 安装 nnpy 组件
安装 nnpy 及其依赖组件 nanomsg
```shell
# install nanomsg
cd /usr/local/include
git clone https://github.com/nanomsg/nanomsg.git
cd nanomsg/

mkdir build
cd build
cmake ..
cmake --build .
ctest .
sudo cmake --build . --target install
# (if on Linux)
sudo ldconfig

# install nnpy
sudo pip install --default-timeout=100 nnpy -i https://pypi.tuna.tsinghua.edu.cn/simple
```

## 4.12. Python 解决 ImportError: No module named 问题
通过 env PYTHONPATH 添加 临时索引 Include 路径
```shell
e.g. test.py 引用了其他路径的包 /A/B/C/D/target_packet

env "PATH=$PATH" "PYTHONPATH=/A/B/C/D/:$PYTHONPATH" python test.py
```

## 4.13. Mac 模拟鼠标点击工具 Cliclick
```shell
# 获取当前鼠标位置
/opt/homebrew/bin/cliclick p

# 点击指定位置坐标
/opt/homebrew/bin/cliclick c:800,467
# 调用重复点击脚本
sh /Users/admin/code/ShellFunc/loop_click.sh <循环次数>
sh /Users/admin/code/ShellFunc/loop_click.sh 100
```

## 4.14. sendip 发包工具
```shell
## v4
##             -d 正文   -p v4|v6 -is SIP    -id DIP             -p 协议 -us sport -ud dport
sudo sendip -v -d r1024 -p ipv4 -is 1.1.1.1 -id 2.2.2.2 -iy 230 -p udp -us 4321 -ud 1111 2.2.2.2
## v6
sudo sendip -v -d r1024 -p ipv6 -6s fdbd:dcff:0:3::87 -6d fdbd:dcff::110 -6t 230 -p udp -us 4321 -ud 1111 fdbd:dcff::110
```

## 4.15. 时间戳 转 字符串
```shell
## 时间数字 转 格式化字符串
date -d @1668744713 +"%Y-%m-%d %H:%M:%S.%N"

## 时间字符串 转 时间数字
date -d "2022-02-21 18:00:35.916640269" +%s
```

## 4.16. Linux 格式化输出 date
```shell
date +%Y.%m.%d_%H:%M:%S
date +%Y-%m-%d--%H-%M-%S
```

## 4.17. 静默运行
```shell
nohup sh analyze_err_log.sh > /dev/null 2>&1 &
```

## 4.18. gRpc根据proto生成代码

- gRpc 测试时增加 export GRPC_TRACE=all  GRPC_VERBOSITY=DEBUG可查看更多细节
```shell
# version
# protoc             v3.20.3
# protoc-gen-go      v1.28.1
# protoc-gen-go-grpc v1.2.0

brew install protobuf@3   # v3.20.3
protoc --version

export PATH="$PATH:$(go env GOPATH)/bin"
ls -l $GOPATH/bin/
sudo go install google.golang.org/protobuf/cmd/protoc-gen-go@v1.28.1
sudo go install google.golang.org/grpc/cmd/protoc-gen-go-grpc@v1.2.0
protoc-gen-go --version
protoc-gen-go-grpc --version

protoc --go_out=. --go_opt=paths=source_relative --go-grpc_out=. --go-grpc_opt=paths=source_relative gobgp.proto
protoc --go_out=. --go_opt=paths=source_relative --go-grpc_out=. --go-grpc_opt=paths=source_relative attribute.proto
protoc --go_out=. --go_opt=paths=source_relative --go-grpc_out=. --go-grpc_opt=paths=source_relative capability.proto
```
