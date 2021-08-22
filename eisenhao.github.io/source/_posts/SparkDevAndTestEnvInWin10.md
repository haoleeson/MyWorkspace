layout: post
title: 基于 Win10 和 IDEA 的 Spark 开发&测试环境搭建
date: 2020/06/25 19:41:44
updated: 2020/06/25 19:41:45
comments: true
tags:

- Spark
categories:
- 技术

---
<img src="https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/SparkDevAndTestEnvInWin10.jpg" class="full-image" />

试想一下，将精心编写的Spark业务代码Jar包上传到Spark集群环境，却出现了简单错误或预期之外的结果，势必会破坏一天的心情和积极性，这时一套桌面级的Spark开发&测试环境的优势就展露无遗了。可以在本地开发Spark代码，并测试基础功能，让开发者可以不必担心上传jar包的代码逻辑正确性、代码质量等基础问题。接下来就跟随本文一起搭建一套Win10下的Spark开发&测试环境吧！

<!-- more -->

{% note success %}
环境信息
Java            1.8.0_251
Scala sdk       2.11.12
Spark lib       2.4.5
IDEA Community  2020.1.2
{% endnote %}

## 准备工作

### 搭建Java环境
- [Oracle官网](https://www.oracle.com/java/technologies/javase-jdk14-downloads.html)下载所需要的JDK(eg.[jdk-14.0.1_windows-x64_bin.exe](https://download.oracle.com/otn-pub/java/jdk/14.0.1+7/664493ef4a6946b186ff29eb326336a2/jdk-14.0.1_windows-x64_bin.exe))
- 安装JDK
- 配置环境变量：此电脑 -> 属性 -> 高级系统设置 -> 环境变量 -> 系统变量 -> 新建"JAVA_HOME"变量，其值为上一步JDK安装路径；新建"CLASSPATH"变量，其值为".;%JAVA_HOME%\lib;%JAVA_HOME%\lib\dt.jar;%JAVA_HOME%\lib\tools.jar"；最后编辑"Path"变量，追加字段"%JAVA_HOME%\bin;%JAVA_HOME%\jre\bin;"
```Shell
eg.
新建环境变量
JAVA_HOME       C:\Java\jdk1.8.0_251
CLASSPATH       .;%JAVA_HOME%\lib;%JAVA_HOME%\lib\dt.jar;%JAVA_HOME%\lib\tools.jar
修改Path变量（追加）
Path            %JAVA_HOME%\bin;%JAVA_HOME%\jre\bin;
```
- 在PowerShell输入 java -version 判断是否安装成功
```Shell
eg.
PS C:\Windows\system32> java -version
java version "1.8.0_251"
Java(TM) SE Runtime Environment (build 1.8.0_251-b08)
Java HotSpot(TM) 64-Bit Server VM (build 25.251-b08, mixed mode)
PS C:\Windows\system32>
```

### 搭建Scala环境
注：Scala依赖Java 8 JDK (或 Java 11 JDK)以后的版本；目前最新版本为2.13.2，但若需要调试Spark强烈建议下载2.11.x版本，因为Spark主要适配的是2.11.x版本，最新Scala版本可能出现与Spark不兼容问题
- [Scala官网](https://www.scala-lang.org/download/)下载Scala可安装程序版[msi安装包](https://downloads.lightbend.com/scala/2.11.12/scala-2.11.12.msi)(大小109 MB) 或 [Zip版本](https://downloads.lightbend.com/scala/2.11.12/scala-2.11.12.zip)(大小27.8 MB，推荐)。msi版可直接安装，Zip版需解压。
- 配置环境变量：此电脑 -> 属性 -> 高级系统设置 -> 环境变量 -> 系统变量 -> 新建"SCALA_HOME"变量，其值为上一步Zip版解压路径或msi版安装路径；最后编辑"Path"变量，追加字段"%SCALA_HOME%\bin;"
```Shell
eg.
新建环境变量
SCALA_HOME      C:\Scala\scala-2.11.12
修改Path变量（追加）
Path            %SCALA_HOME%\bin;
```
- 在PowerShell输入 scala 判断是否安装成功
```Shell
eg.
PS C:\Windows\system32> scala
Welcome to Scala 2.11.12 (Java HotSpot(TM) 64-Bit Server VM, Java 1.8.0_251).
Type in expressions for evaluation. Or try :help.

scala> print("hello")
hello
scala>
```

### 搭建Hadoop环境
注：此步未配置将会导致执行scala程序时因缺少Hadoop环境如“winutils.exe”文件而无法执行，抛IOException
- 登录[GitHub](https://github.com/)搜索"hadoop win"，下载Spark运行所需的Hadoop win环境（如：[steveloughran/winutils](https://github.com/steveloughran/winutils)），否则将无法运行Spark工程，报"java.io.IOException: Could not locate executable null\bin\winutils.exe in the Hadoop binaries."
- 解压相应Hadoop版本到指定文件夹
- 需确保bin下有如下两个文件：hadoop.dll、winutils.exe
- 配置环境变量：此电脑 -> 属性 -> 高级系统设置 -> 环境变量 -> 系统变量 -> 新建"HADOOP_HOME"变量，其值为上一步解压路径；最后编辑"Path"变量，追加字段"%HADOOP_HOME%\bin;"

```Shell
eg.
新建环境变量
HADOOP_HOME     C:\hadoop-2.7.1
修改Path变量（追加）
Path            %HADOOP_HOME%\bin;
```

### 下载 Spark 的 Jar 依赖包
Idea中Spark工程会用到Spark的jar依赖，故需下载spark的依赖包。

下载[spark-2.4.5-bin-hadoop2.7.tgz](https://mirrors.tuna.tsinghua.edu.cn/apache/spark/spark-2.4.5/spark-2.4.5-bin-hadoop2.7.tgz)后解压备用


### 安装Intellij IDEA Community（社区免费版）
[官网](https://www.jetbrains.com/idea/)下载[Intellij IDEA Community（社区免费版）](https://download.jetbrains.8686c.com/idea/ideaIC-2020.1.2.exe)，并安装

### IDEA 安装 Scala 插件
有两种插件安装方式，即在线安装和离线安装，推荐网络不稳定的小伙伴选择后者（注意Scala插件版本应与IDEA版本匹配）
#### 在线安装 Scala 插件（超时、失败）
IDEA -> Settings -> plugins -> search plugins in marketplace(“scala”) -> install -> restart IDEA
#### 离线安装 Scala 插件
- 浏览器访问 [IDEA 离线插件库](https://plugins.jetbrains.com/plugin/1347-scala)，点击右上角"Get"按钮，并下载支持IDEA版本(2020.1.2)的 [Scala 插件](https://plugins.jetbrains.com/files/1347/89709/scala-intellij-bin-2020.1.39.zip?updateId=89709&pluginId=1347&family=INTELLIJ)（支持2020.1 — 2020.1.2）

- IDEA -> Settings -> plugins -> 点击小齿轮 -> Install plugin form disk -> select package -> restart IDEA

{% note success %}准备工作至此结束{% endnote %}

## 创建Scala项目
- 新建Scala工程
Run IDEA -> File -> New -> Project -> Scala -> IDEA -> NEXT
- 填写工程基础信息

指定工程的工程名、路径、Java JDK、Scala JDK。设置Scala JDK时点击右侧"Create"按钮会自动识别准备工作中安装的Scala JDK(2.11.12)

- 添加Spark依赖的jar到此工程
也可直接将整个jars目录导入到Libraries

File –> Project Steuccture –> Libraries –> 点击"+"按钮 –> Java –> 选择准备工作中已解压备用的"spark-2.4.5-bin-hadoop2.7"文件夹里的"jars"目录 –> OK

- 新建一个object

左侧工程结构中点击 src -> new -> scala clas -> 输入文件名("SparkPi.scala") -> 选择Object

- 编写Spark简易程序：计算圆周率Pi

```Scala
import scala.math.random
import org.apache.spark.sql.SparkSession

/**
 * Spark 简易程序：计算圆周率 Pi
 *
 * 原理：随机落在与正方形相切的同心圆内的概率为：S圆 / S正 = Pi / 4
 * 注：根据大数定律，当随机抛点次数达到百万次时，据概率所计算出Pi才具有参考意义
 */
object SparkPi {
    def main(args: Array[String]) {

        val spark = SparkSession
          .builder
          .appName("Spark Pi")
          .getOrCreate()
        val slices = if (args.length > 0) args(0).toInt else 2
        val n = math.min(1000000L * slices, Int.MaxValue).toInt // avoid overflow
        val count = spark.sparkContext.parallelize(1 until n, slices).map { i =>
            val x = random * 2 - 1
            val y = random * 2 - 1
            if (x * x + y * y < 1) 1 else 0
        }.reduce(_ + _)
        println("Pi is roughly " + 4.0 * count / (n - 1))
        spark.stop()
    }
}
```

- 设置启动参数

注：未设置会报"SparkException: A master URL must be set in your configuration"异常

设置vm options：点击菜单栏Run -> Edit Configurations -> VM options -> 填写如下启动参数，让Spark程序以local模式运行
```Shell
-Dspark.master=local
```

- 运行Spark程序

点击"object SparkPi"旁的绿色小三角即可运行Spark程序（注意设置启动参数）


## 参考博文
- [IntelliJ IDEA（Community版本）的下载、安装和WordCount的初步使用](https://www.cnblogs.com/zlslch/p/5880926.html)
- [基于windows，IDEA配置hadoop运行环境遇到的问题和解决（null\bin\winutils.exe）](https://blog.csdn.net/LiangEdward/article/details/106845276)
- [ERROR SparkContext: Error initializing SparkContext.](https://blog.csdn.net/streamery/article/details/106752423)