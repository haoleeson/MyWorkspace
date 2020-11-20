# Golang学习笔记

## 简介（[百科](https://baike.baidu.com/item/go/953521?fromtitle=Go%E8%AF%AD%E8%A8%80&fromid=3246011)）

Go（又称Golang），是Google的 Robert Griesemer，[Rob Pike(罗勃·派克)](https://baike.baidu.com/item/%E7%BD%97%E5%B8%83%C2%B7%E6%B4%BE%E5%85%8B/10983505?fr=aladdin) 及 [Ken Thompson(肯·汤普森)](https://baike.baidu.com/item/Ken%20Thompson/3441433)开发的一种静态强类型、编译型语言，于2009年发布。Go 语言语法与 [C](https://baike.baidu.com/item/C/7252092) 相近，但功能上有：内存安全，[GC](https://baike.baidu.com/item/GC/66426)（垃圾回收），[结构形态](https://baike.baidu.com/item/结构形态/5942010)及 CSP-style [并发计算](https://baike.baidu.com/item/并发计算/9939802)。

## Golang诞生背景（解决什么问题）

* 目前主流编程语言发展明显落后于硬件技术的频繁更新（不能合理利用**多核多CPU**的优势以提升软件系统性能）
* 软件系统复杂度越来越高，维护成本越来越高，目前缺乏一个足够简洁高效的编程语言。（风格不统一，计算能力不够，不适用处理大并发）
* 企业运行维护很多C/C++项目，虽然程序运行速度很快，但编译速度很慢，同时存在内存泄漏等一系列问题的困扰。

## 描述

* Go的语法接近[C语言](https://baike.baidu.com/item/C语言)，但对于变量的声明有所不同。Go支持垃圾回收功能。Go的并行模型是以[东尼·霍尔](https://baike.baidu.com/item/东尼·霍尔)的[通信顺序进程](https://baike.baidu.com/item/通信顺序进程)（CSP）为基础，采取类似模型的其他语言包括[Occam](https://baike.baidu.com/item/Occam)和[Limbo](https://baike.baidu.com/item/Limbo)，但它也具有Pi运算的特征，比如通道传输。在1.8版本中开放插件（Plugin）的支持，这意味着现在能从Go中动态加载部分函数。

* 与C++相比，Go并不包括如[枚举](https://baike.baidu.com/item/枚举)、[异常处理](https://baike.baidu.com/item/异常处理)、[继承](https://baike.baidu.com/item/继承)、[泛型](https://baike.baidu.com/item/泛型)、[断言](https://baike.baidu.com/item/断言)、[虚函数](https://baike.baidu.com/item/虚函数)等功能，但增加了 切片(Slice) 型、并发、管道、垃圾回收、接口（Interface）等特性的语言级支持。

* 不同于[Java](https://baike.baidu.com/item/Java)，Go内嵌了[关联数组](https://baike.baidu.com/item/关联数组)（也称为[哈希表](https://baike.baidu.com/item/哈希表)（Hashes）或字典（Dictionaries）），就像字符串类型一样。

## 应用方向

* 区块链（BT，Blockchain technology）应用。互联网数据库技术（去中心化、公开透明）
* 后端服务器应用（后台数据处理、负载均衡、容错、处理大并发），游戏后台（数据通道：通讯、逻辑、数据存储）
* 分布式、云计算、云服务（CDN，内容分发网络；消息推送云服务，后台所有服务全用go实现）

## Golang语言特点

 Go语言保证了既具备静态编译语言的安全和性能，又具备动态语言开发维护的较高效率（**Go = C + Python**）。

* **自动垃圾回收**，无需开发人员管理。
* 丰富的内置类型，继承了C语言的许多理念，包括：表达式语法、控制结构、基础数据类型、调用参数传值、**指针**等。也保留了和C语言一样的编译执行方式及弱化指针。
* 引入**包概念**（用于组织程序结构）。Go语言的每一个文件都要归属于一个包（不能单独存在）
* **天然主持并发编程**（**重要**）。从语言层面支持并发，较简单用例就能实现并发；goroutine，轻量级线程，**可实现大并发处理**，**高效利用多核**；基于CSP（communicating sequential processes）并发模型实现
* 吸收了**管道通信**机制channel
* **错误处理**
* **匿名函数和闭包**
* **函数多返回值**

```Golang
func calcSumAndSub(num1 int, num2 int) (int, int) {
    sum := num1 + num2
    sub := num1 - num2
    return sum, sub
}
```

* 新增创新：**切片**slice、**延时执行**defer等

## Golang语言开发工具

* 代码编辑工具：VScode、Sublime Text、Vim、Emacs
* IDE：Eclipse、LiteIDE（国人开发的，免费）、JetBrains的系列IDE

## Go环境配置（Windows）

* 方法一：从[官网](https://www.golangtc.com)下载Windows的SDK(eg. go1.9.2.windows-amd64.zip)，并解压到本地安装路径(eg. C:\Go)
* 方法二：下载最新版[MSI installer](https://golang.org/dl/)，eg.[https://dl.google.com/go/go1.15.5.windows-amd64.msi](https://dl.google.com/go/go1.15.5.windows-amd64.msi)，并安装
* 添加环境变量（我的电脑 -> 属性 -> 高级系统配置 -> 系统变量）

| 环境变量 | 值   | 描述 |
| -------- | ---- | ---- |
| GOROOT | C:\Go | 指定GO的SDK的解压路径 |
| Path(追加) | %GOROOT%\bin | 将Go的执行目录添加到Path路径 |
| GOPATH | C:\Workspace\Go | Go项目所在地址 |

* 验证

  打开CMD，输入如下命令，测试返回结果

```powershell
go version
```

安装成功后返回值

```powershell
go version go1.9.2 windows/amd64
```

##  Go语言结构（以hello world为例）

Go 语言的基础组成有以下几个部分：

* **包声明**。必须在源文件中非注释的第一行指明这个文件属于哪个包，package main表示一个可独立执行的程序，每个 Go 应用程序都包含一个名为 main 的包。
* **引入包**。fmt 包实现了格式化 IO（输入/输出）的函数。
* **函数**。每一个可执行程序必须包含main 函数
* 变量。
* 语句 & 表达式
* 注释。行注释、块注释

备注：当标识符（包括常量、变量、类型、函数名、结构字段等等）以一个**大写字母开头**，如：Println，那么使用这种形式的标识符的对象就可以被**外部**包的代码所使用（客户端程序需要先导入这个包），这被称为导出（像面向对象语言中的 public）；标识符如果以**小写字母开头**，则对包外是不可见的，但是他们在整个包的内部是可见并且可用的（像面向对象语言中的 protected ）。
| 标识符首字母大小写 | 包外可见状态 | 类比C++ | 实例 |
|  ---- | ---- | ---- | ---- |
| 大写 | 包外可见 | public | Println |
| 小写 | 包外不可见 | protected | main |

1. 在 %GOPATH%\src\go_code\project1\main 路径下创建 helloworld.go  源文件

```Golang
package main // 【包声明】定义本.go文件所在的包是main，package main表示一个可独立执行的程序
import "fmt" // 【引入包】引入基本包fmt（下方用到打印函数）

/* 
 * 【main函数】
 * 每一个可执行程序必须包含main函数
 */
func main() {
    fmt.Println("hello world!") // 【语句】 打印字符串
}
```

2. 在CMD(或PowerShell)中跳转到%GOPATH%\src\go_code\project1\main 路径，编译helloworld.go 源文件(生成exe文件)

```powershell
cd $env:GOPATH\src\go_code\project1\main
go build .\helloworld.go
```

运行编译好的二进制 helloworld.exe 文件

```powershell
.\helloworld.exe
```

3. 也可通过 go run 命令直接运行 helloworld.go 源文件

```powershell
go run .\helloworld.go
```
## Golang标准库API文档
* API（Application Programming Interface，应用程序编程接口）
* [Go语言中文网：标准库文档](https://studygolang.com/pkgdoc)

## Golang 变量类型

### 继承自C的基础数据类型
* 整数类型：int, int8, int16, int32, int64, uint, uint8, uint16, uint32, uint64, byte
* 浮点类型：float32, float64
* 字符型：（无，使用 byte 保存单个字母字符）
* 布尔型：bool
* 字符串型：string

### 继承自C的非基础数据类型
* 指针：Pointer
* 数组
* 结构体：struct

### 特定数据类型
* 管道：Channel
* 函数
* 切片：slice
* 接口：interface
* map

### 定义Golang变量的方式
1. 静态定义变量类型（若未赋初值，则初始化为默认初值0）
```Golang
var i int
i = 10
```
2. 省略定义变量类型，编译器自行判断变量类型（类型推导）
```Golang
var pi = 3.1415926
```
3. 省略定义"var"及变量类型
```Golang
str := "hello world"
```
4. 多变量声明
```Golang
i, pi, str := 10, 3.1415926, "hello world"
```
5. 定义全局变量
在Golang中，函数体外部定义的变量视为全局变量
6. 变量在同一作用域内不允许重名

## Go 条件语句
### if 语句
 * 不需使用括号将条件包含起来
 * 条件执行块的大括号{}必须存在，即使只有一行语句
 * 左括号必须在if或else的同一行
 * 在if之后，条件语句之前，可以添加变量初始化语句，使用';'进行分隔
 * 在有返回值的函数中，最终的return不能在条件语句中

```Golang
func grade(score uint8) byte {
    if score > 100 {
        return 0
    } else if score > 89 {
        return 'A'
    } else if score > 79 {
        return 'B'
    } else if score > 69 {
        return 'C'
    } else if score > 59 {
        return 'D'
    } else {
        return 'E'
    }
    return 0
}
```

### switch 语句
* 无需在每个 case 执行代码块末尾加 break
* fallthrough，不判断直接执行下一case的执行代码

```Golang
func awardMoney(grade byte) uint8 {
    var money uint8 = 0
    switch grade {
        case 'A':
            money += 100
            fallthrough // 不判断直接执行下一case的执行代码
        case 'B':
            money += 50
            fallthrough // 不判断直接执行下一case的执行代码
        case 'C':
            money += 20
            fallthrough // 不判断直接执行下一case的执行代码
        case 'D':
            money += 10
            fallthrough // 不判断直接执行下一case的执行代码
        case 'E':
        default:
    }
    return money
}
```
### select 语句
select 是 Go 中的一个控制结构，类似于用于通信的 switch 语句。每个 case 必须是一个通信操作，要么是发送要么是接收。 select 随机执行一个可运行的 case。如果没有 case 可运行，它将阻塞，直到有 case 可运行。一个默认的子句应该总是可运行的。

select 语法：
* 每个 case 都必须是一个通信
* 所有 channel 表达式都会被求值
* 所有被发送的表达式都会被求值
* 如果任意某个通信可以进行，它就执行，其他被忽略。
* 如果有多个 case 都可以运行，Select 会随机公平地选出一个执行。其他不会执行。 否则： 1.如果有 default 子句，则执行该语句。2.如果没有 default 子句，select 将阻塞，直到某个通信可以运行；Go 不会重新对 channel 或值进行求值。

## Go 循环语句

### for 循环

Go 语言的 For 循环有 3 种形式，只有其中的一种使用分号。

* 形式1：与C 语言的 for 一样：

```Golang
for init; condition; post { }
```
其中：
1. init： 一般为赋值表达式，给控制变量赋初值；
2. condition： 关系表达式或逻辑表达式，循环控制条件；
3. post： 一般为赋值表达式，给控制变量增量或减量。

示例：

```Golang
func isPrime(num int) bool {
    if num <= 1 {
        return false
    }
    for i := 2; i * i <= num; i++ {
        if num % i == 0 {
            return false
        }
    }
    return true
}
```

* 形式2：与C 语言的while一样，等效while(condition){ } ：

```Golang
for condition { }
```

* 形式3：和 C 的 for(;;) 一样，等效while(true){ }：
```Golang
for condition { }
```

### for-each range 循环

for-each range 循环可以对 slice、map、数组、字符串等进行迭代循环。格式如下：

```Golang
for key, value := range oldMap {
    newMap[key] = value
}
```

## 循环控制语句

|  控制语句 | 描述 |
| ---- | ---- |
| break | 经常用于中断当前 for 循环或跳出 switch 语句 |
| continue | 跳过当前循环的剩余语句，然后继续进行下一轮循环 |
| goto | 将控制转移到被标记的语句 |