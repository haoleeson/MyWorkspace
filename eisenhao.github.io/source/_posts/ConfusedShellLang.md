layout: post
title: Shell易混淆基本语法总结
date: 2020/05/29 21:44:44
updated: 2020/05/29 21:44:45
comments: true
tags:

- Shell
categories:
- 技术

---
<img src="https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/ConfusedShellLang.jpg" class="full-image" />

主要整理了常用易混淆Shell语法，以备不时查询之需。

<!-- more -->

# 1. 单引号、双引号、倒引号的区别
## 1.1. 单引号 ‘ vs 双引号 “
- 单引号作用：将位于单引号之间的所有内容全部视为普通字符，即不处理任何特殊字符
- 双引号作用：先将双引号之间的特殊字符做预处理（若存在），再将双引号之间的内容（特殊字符的结果）视为字符串
- 示例：
```Shell
#!/bin/bash
ans=15
# 单引号，不处理特殊字符
echo ‘Petter: 3 * 5 = $ans’
# 双引号，处理特殊字符
echo “Petter: 3 * 5 = $ans”

# 执行结果如下
Petter: 3 * 5 = $ans
Petter: 3 * 5 = 15
```

## 1.2. 倒引号 `
- 坐标：位于键盘Esc键下方及数字1键左侧。
- 作用：用位于倒引号之间的命令执行结果替换倒引号及之间的命令。等价于$()，新用法$()中则不需要考虑\的问题，推荐使用后者。
- 示例：
```Shell
#!/bin/bash
echo "this path is `pwd`"
echo "this path is $(pwd)"

# 执行结果如下
this path is /home
this path is /home
```

# 2. 括号() vs 花括号{}
## 2.1. 作用
对命令的执行
## 2.2. 应用场景
变量名后要附加一些内容时（如：字符串、数字、下划线），为了分割变量名与附加内容；用执行命令的结果替换字符串中的部分内容；需要在括号内执行一串命令时；
- 举例：批量改名（加后缀）
```Shell
#!/bin/bash
for fileName in $(ls)
do
    mv $fileName $(fileName).tmp
done
```
## 2.3. 括号()与花括号{}的异同
\\|括号()|花括号{}
:----|:----:|:----:
执行位置|对一串命令重开一个子Shell执行|对一串命令在当前Shell执行
变量作用域|可视为局部变量|会改变全局同名变量的值
分号|最后一个命令可以不用分号结尾|最后一个命令要用分号结尾
空格|不必用空格与括号隔开|第一个命令和左括号之间必须要有一个空格
重定向|括号里的某个命令的重定向只影响该命令，括号外的重定向则影响到括号里的所有命令|括号里的某个命令的重定向只影响该命令，括号外的重定向则影响到括号里的所有命令

# 3. 几种特殊的替换用法
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
- 若变量非空，则用其值，若变量为空，则输出string到标准错误中后退出脚本${var:?string}
```Shell
#!/bin/bash
var1=abc
var2=
echo ${var1:+FULL}
echo ${var2:+FULL}

# 执行结果如下：
FULL
```
# 4. 支持POSIX标准的扩展计算$((exp))
其中exp为符合C语言的运算符
## 4.1. 举例说明
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
1
5
6
```

# 5. 四种模式匹配替换
\# 是去掉左边(在键盘上\#在\$之左边)；\% 是去掉右边(在键盘上\%在\$之右边)；\#和\%中的单一符号是最小匹配，两个相同符号是最大匹配。这四种模式中都不会改变variable的值，其中，只有在pattern中使用了\*匹配符号时，%和%%，#和##才有区别。结构中的pattern支持通配符，\*表示零个或多个任意字符，\?表示仅与一个任意字符匹配，[...]表示匹配中括号里面的字符，[!...]表示不匹配中括号里面的字符。

## 5.1. 第一种模式：${variable%pattern}
说明：shell在variable中查找，判断variable是否以pattern结尾，如果是，就从命令行把variable中的内容去掉右边*最短的*匹配模式
## 5.2. 第二种模式：${variable%%pattern}
说明：shell在variable中查找，判断variable是否以pattern结尾，如果是，就从命令行把variable中的内容去掉右边*最长的*匹配模式
## 5.3. 第三种模式：${variable#pattern}
说明：shell在variable中查找，判断variable是否以pattern开始，如果是，就从命令行把variable中的内容去掉左边最短的匹配模式
## 5.4. 第四种模式：${variable##pattern}
shell在variable中查找，判断variable是否以pattern开始，如果是，就从命令行把variable中的内容去掉右边最长的匹配模式
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
(空)
M2.${VAR%%?$PATTERN1}
ABCABCDE
M3.${VAR#*$PATTERN2}
ABCDEFDEF
M4.${VAR##*$PATTERN2}
DEFDEF
M4.${VAR##$PATTERN2*}
(空)
```

# 6. 变量判空
- 判空必要性：某些环境下执行空变量可能造成严重后果，如执行rm删除操作时，rm -rf 空路径变量会删除根目录，造成无法挽回的严重后果。

- 正确操作：
```Shell
#!/bin/bash
# 判断DIR变量非空，才会执行rm命令
[ -n $DIR ] && rm -rf $DIR
```
- 变量判空常用方法
```Shell
#!/bin/bash
para=
# 判空方式1. 直接判断变量
if [ ! $para ];then
    echo "NULL"
fi
# 判空方式2. 作字符串判空
if [ ! -n "$para" ];then
    echo "NULL"
fi
# 判空方式3. 与“空字符串”比较判空
if [ "$para" = "" ];then
    echo "NULL"
fi
# 判空方式4. 利用test判空
if test -z "$para"
then
    echo "NULL"
fi
```

# 7. 参考文档
- [Shell 命令中的特殊替换、模式匹配替换、字符串提取和替换](https://blog.csdn.net/zhan570556752/article/details/80515376?utm_source=blogxgwz1)