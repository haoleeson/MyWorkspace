layout: post
title: Shell 实用指令记录
date: 2020/05/29 21:44:30
updated: 2021/10/29 21:44:45
comments: true
tags:
- Shell
categories:
- 技术

---
<img src="../../../../uploads/ConfusedShellLang.jpg" class="full-image" />

博文记录了一些实用 Shell 指令，以备不时之需。

<!-- more -->

# 1. 几种特殊的替换用法
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

# 2. 支持 POSIX 标准的扩展计算
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

# 3. 四种模式匹配替换
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

# 4. 变量判空
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

# 5. Shell 字符分割
```shell
tmux a -t $(tmux ls | grep build2021 | awk '{ print $1 }' | cut  -d \: -f 1)
```

# 6. shell 字符变量切分
```shell
str1="I am chinese"
# 根据空格分割为数组
array1=(${str1// / })
```

# 7. 获取字符串变量长度
```shell
STR='hello'; echo ${#STR}
```

# 8. 字符串截取
## 8.1. 头部截取（最大 -* 匹配）
从右往左匹配最后遇到的'-'字符及之后的部分（减掉表达式"-*"最大匹配的部分"-serial-14210"），结果："/dev/tty.usb"
```shell
STR="/dev/tty.usb-serial-14210"; echo ${STR%%-*}
```

## 8.2. 头部截取（最小 -* 匹配）
从右往左匹配最先遇到的'-'字符及之后的部分（减掉表达式"-*"最大匹配的部分"-14210"），结果："/dev/tty.usb-serial"
最后一个'-'之前的部分，结果："/dev/tty.usb-serial"
```shell
STR="/dev/tty.usb-serial-14210"; echo ${STR%-*}
```

## 8.3. 尾部截取（ *- 最大匹配）
从左往右匹配最后遇到的'-'字符及之前的部分（减掉表达式"*-"最大匹配的部分"/dev/tty.usb-serial-"），结果："14210"
```shell
STR="/dev/tty.usb-serial-14210"; echo ${STR##*-}
```

## 8.4. 尾部截取（ *- 最小匹配）
从左往右匹配最先遇到的'-'字符及之前的部分（减掉表达式"*-"最小匹配的部分"/dev/tty.usb-"），结果："serial-14210"
```shell
STR="/dev/tty.usb-serial-14210"; echo ${STR#*-}
```

## 8.5. cut 截取命令 （以截取 ip "192.168.3.35/24"中'/'字符前部为例）
```shell
ip addr | grep 'eth0' | awk '{ print $2 }' | cut -d / -f 1
```

# 9. 变量转大小写
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

# 10. 输出内容的 字符替换 & 字符删除
```shell
# 替换
echo 'ABCDABCD' | sed 's/ABC/DEF/g'
# tr 替换，注意是字符集合替换
echo 'ABCDABCD' | tr 'AD' 'C'

# 删除
echo 'ABCDABCD' | sed 's/ABC//g'
echo 'ABCDABCD' | tr -d 'AC'
```

# 11. 显示文件列表
```shell
ls -l -A --color=auto --group-directories-first /var/log/
```

# 12. 查看个人进程
```shell
ps -ef |grep lih |fgrep -v vscode | fgrep -v baas
```

# 13. 查找文件（过滤无效信息）
```shell
sudo find / -name "makefile" -print 2>&1 | fgrep -v "Operation not permitted" | fgrep -v "No such file"
```

# 14. 统计第 2 列总类型
```shell
command | awk '{ print $2 }' | uniq | sort | uniq

cat ~/1.txt  | awk '{ for(i=2;i<=NF;i++) printf $i""FS;print "" }' | uniq | sort | uniq
```
# 15. 只打印 第 n~最末 列
```shell
cat xxx.log | awk '{ for(i=1; i<=3; i++){ $i="" }; print $0 }'
``` 

# 16. grep 查找命令说明
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

## 16.1. 倒序查看 n 行 符合条件行
```shell
sudo grep -E 'Psu|Fan|Sff|Linecard' /var/log/syslog | sort -r | head -n 40
```

# 17. 查看某容器中 打印到 某文件的进程列表
```shell
grep -a "bgp" /var/log/syslog | awk '{ print $7 }' | uniq | sort | uniq
grep -a "bgp" /var/log/user.log | awk '{ print $7 }' | uniq | sort | uniq
```

# 18. 查看某进程打印日志的类别 列表
```shell
grep -a "database" /var/log/user.log | awk '{ print $4 }' | uniq | sort | uniq
```

# 19. shell 脚本中临时调用 pexpect
```shell
expect -c "
spawn scp lih@10.32.19.100:/home/lih/pexpect-2.3.tar.gz $RUN_PATH

expect \"assword:\"
send \"$PASSWD\r\"
expect eof
"
```

# 20. tmux 常用命令

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

# 21. tmux 快捷键
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
