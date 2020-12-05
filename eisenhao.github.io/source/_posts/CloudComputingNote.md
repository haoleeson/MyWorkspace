layout: post
title: 云计算学习笔记
date: 2019/07/05 15:10:44
updated: 2019/07/15 23:01:45
comments: true
tags:
- 云计算
categories:
- 技术

---
<img src="https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/cloudComputing.jpg" class="full-image" />

## Bigtable————分布式结构化数据表

### Bigtable特点

*  数据种类繁多，满足一系列Google产品的存储要求
* 吞吐量大，响应海量的服务请求
* 高可用性，几乎所有情况下的系统均可用
* 高扩展性，可根据需要随时加入或撤销服务器
* 简单，简单的底层系统，既减小了系统出错概念，又使上层应用开发更简单

<!-- more -->
### Bigtable存储结构

Bigtable是一个分布式多维映射表，表中的数据通过一个行关键字（Row Key）、一个列关键字（Column Key）以及一个时间戳（Time Stamp）进行索引

![CloudComputing-20190617095713134](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/CloudComputing-20190617095713134.png)

#### 行关键字（Row Key）

* 可为任意字符串，最大64KB
* 表中数据根据行关键字排序（词典序）
* 同一地址域的网页关键字会存储在表中连续位置
* 压缩倒排以提高压缩率

#### 列关键字（Column Key）

* 列的关键字应有其意义
* 列的簇名同时也是Bigtable中ACL访问控制的基本单元

#### 时间戳（Time Stamp）

* 相同的内容需要保存不同时刻的数据版本（eg.网页检索数据、用户个性化设置数据）
* 64位整形存储，用户自定义赋值方式和意义

#### Bigtable数据存储及读写操作

* 较新的数据存储在内存中称为内存表（Memtable）的有序缓冲里
* 较旧的数据以SSTable格式保存在GFS中

##### 读写操作有很大差异

![CloudComputing-20190618161018598](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/CloudComputing-20190618161018598.png)

### Bigtable基本架构

![CloudComputing-20190617100822880](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/CloudComputing-20190617100822880.png)

#### 其中Chubby的作用

* 保证一致性（使所有子表服务器选取唯一一个主服务器）
* 获取子表服务器列表。扫描并发现目前活跃的子表服务器列表
* 保存Bigtable的模式信息和ACL访问控制列表。与所有活跃的子表服务器联系，并获取所有子表的分配情况；通过扫描元数据表发现未分配的子表，并将其分配到合适的子表服务器

#### 其中主服务器的作用

* 新子表分配。当新子表产生时，主服务器通过一个加载命令将新子表分配给一个拥有足够空间的子表服务器，子表服务器分割完成后会向主服务器返回一个通知（创建新表、合并表、大表分裂都会产生一个或多个子表）
* 子表服务器集群的状态监控。主服务器对子表服务器状态进行监控，以便于及时监测到服务器的加入和撤销
* 子表服务器之间的负载均衡

#### 其中子表服务器

##### 子表SSTable(Sorted String Table)

每个子表服务器上保存几十～几千哥子表。SSTable是Google为Bigtable设计的内部数据存储格式。所有的SSTable文件都存储在GFS上，用户可以通过键来查询相应的值。

![CloudComputing-20190617104500323](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/CloudComputing-20190617104500323.png)

##### 子表的组成

* 不同子表的SSTable可以共享
* 每个子表服务器上仅保存一个日志文件
* 日志内容按照键值排序
* 每个子表服务器上保存几十～几千个子表（平均100个子表）

![CloudComputing-20190617104904894](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/CloudComputing-20190617104904894.png)

##### 子表地址

Bigtable系统内部采用的是一种类似B+树的三层查询体系

![CloudComputing-20190617110037290](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/CloudComputing-20190617110037290.png)

##### 三种形式压缩之间的关系

![CloudComputing-20190618161124154](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/CloudComputing-20190618161124154.png)


### Bigtable中的性能优化

#### 局部性群组

Bigtable允许用户将存储在不同区域的数据组织在一个单独的SSTable中（以列簇为单位），以构成一个局部性群组。（类似数据库中两个表的自然连接）

* 可筛选在意的数据内容（类似数据库中投影）
* 改善经常被读取的局部数据的访问速率

![CloudComputing-20190618161816332](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/CloudComputing-20190618161816332.png)

#### 压缩

Bigtable中广泛应用压缩（eg.用于构成局部性群组的SSTable中）

* 利用Bentley & McIlroy方式（BMDiff）在大的扫描窗口将常见的长串进行压缩
* 采取Zippy技术进行快速压缩，它在一个16KB大小的扫描窗口内寻找重复数据，这个过程非常快

#### 布隆过滤器

巴顿·布隆于1970年提出，它实际上是一个很长的二进制向量和一系列随机映射函数。在Bigtable中用于读写操作中确定子表位置

优点：

* 速度快，省空间
* 不会将一个子表误判成不存在

缺点：

* 某些情况下，会将不存在的子表误判成存在

## Megastore————分布式存储系统

### 产生原因（业务驱动）：

* 高负载的交互式应用，传统关系型数据库通过连接（join）提升性能代价过于高昂
* 业务需求中读操作远远大于写操作
* 基于Bigtable这样的key/value存储系统之上，设计存储和查询级联数据的分布式存储系统非常方便

### 说明

* 介于传统关系型数据库和NoSQL之间的存储技术，并尽可能地实现高可用性和高可扩展性的统一。
* 对于高可用性，Megastore实现了一个同步的、容错的、适合远距离传输的**复制机制**
* 对高扩展性，Megastore将数据分割成很多小数据分区（存放于NoSQL数据库中）

![CloudComputing-20190618163837063](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/CloudComputing-20190618163837063.png)

* 在Megastore中，这些小的数据分区被称为实体组集（Entity Groups）
* 每个实体组集包含若干的实体组（Entity Group，相当于分区中表的概念）
* 一个实体组中包含很多的实体（Entity，相当于表中记录的概念）

性能

* 平均读取延迟在**万分之一毫秒**之内，平均写入延迟在**100至400毫秒**之间 

### Megastore数据模型

* 同关系型数据库一样，Megastore的数据模型是在模式（schema）中定义的且是强类型的（strongly typed）
* 每个模式都由一系列的表（tables）构成，表又包含有一系列的实体（entities），每实体中包含一系列属性（properties）
* 属性是命名的且具有类型，这些类型包括字符型（strings）、数字类型（numbers）或者Google的Protocol Buffers。

### Megastore索引

* 局部索引。定义在单个实体组中，作用域仅限于单个实体组（ 如PhotosByTime ）
* 全局索引。可以横跨多个实体组集进行数据读取操作（ 如PhotosByTag ）
* 额外索引。STORING子句、可重复的索引、内联索引

### 在Bigtable中的存储情况

| 行键（Row Key） | **User.name** | **Photo.time** | **Photo.tag**   | **Photo._****url** |
| --------------- | ------------- | -------------- | --------------- | ------------------ |
| 101             | John          |                |                 |                    |
| 101,500         |               | 12:30:01       | Dinner,   Paris | …                  |
| 101,502         |               | 12:15:22       | Betty, Paris    | …                  |
| 102             | Mary          |                |                 |                    |

Bigtable的列名实际上是表名和属性名结合在一起得到，不同表中实体可存储在同一个Bigtable行中

### Megastore中的事务及并发控制

#### 读操作

* current。总是在单个实体组中完成
* snapshot。总是在单个实体组中完成、系统取出已知的最后一个完整提交的事务的时间戳，接着从这个位置读数据
* inconsistent。忽略日志的状态直接读取最新的值

#### 完整的事物周期

* 读。获取最后一次提交的事务的时间戳和日志位置

* 应用逻辑。从Bigtable读取且聚集数据到日志入口

* 提交。使用Paxos协议达成一致性，将一个入口追加到日志

* 生效。将数据更新到Bigtable中的实体和索引中

* 清除。清除不需要的数据

#### Megastore中的事务机制

![CloudComputing-20190618171208831](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/CloudComputing-20190618171208831.png)

### Megastore基本架构

在Megastore中共有三种副本：

* 完整副本（Full Replica）
* 见证者副本（Witness Replica）
* 只读副本（Read-only Replica）

![CloudComputing-20190618171436506](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/CloudComputing-20190618171436506.png)

### 快速读与快速写

#### 快速读

* 利用本地读取实现快速读，带来更好的用户体验及更低的延迟
* 关键是保证选择的副本上数据是最新的
* 协调者是一个服务，该服务分布在每个副本的数据中心里面。它的主要作用就是跟踪一个实体组集合
* 协调者的状态是由写算法来保证 

#### 快速写

* 如果一次写成功，那么下一次写的时候就跳过准备过程，直接进入接受阶段
* Megastore没有使用专门的主服务器，而是使用leaders 
* leader主要是来裁决哪个写入的值可以获取0号提议
* 客户端、网络及Bigtable的故障都会导致一个写操作处于不确定的状态 

### Megastore核心技术--复制

#### 复制的日志

* 每个副本都存有记录所有更新的数据

* Megastore允许副本不按顺序接受日志，这些日志将独立的存储在Bigtable中

![CloudComputing-20190618171942921](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/CloudComputing-20190618171942921.png)

#### 读取数据

本地查询 -> 发现位置 -> 追赶 -> 验证 -> 查询数据

![CloudComputing-20190618172138062](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/CloudComputing-20190618172138062.png)

#### 写入数据

接收leader -> 准备 -> 接收 -> 失效 -> 生效

![CloudComputing-20190618172312027](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/CloudComputing-20190618172312027.png)

#### 协调者的可用性 

* 协调者在系统中是比较重要的——协调者的进程运行在每个数据中心。每次的写操作中都要涉及协调者，因此协调者的故障将会导致系统的不可用
* Megastore使用了Chubby锁服务，为了处理请求，一个协调者必须持有多数锁。一旦因为出现问题导致它丢失了大部分锁，协调者就会恢复到一个默认保守状态
* 除了可用性问题，对于协调者的读写协议必须满足一系列的竞争条件 

## Dapper————大规模分布式系统的监控基础架构

### 三个基本概念

* 监控树（Trace Tree）。一个同特定事件相关的所有消息
* 区间（Span）。实际上就是一条记录
* 注释（Annotation）。主要用来辅助推断区间关系，也可以包含一些自定义的内容

### 监控信息的汇总

![CloudComputing-20190710111630677](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/CloudComputing-20190710111630677.png)

### 关键性技术

#### 轻量级核心功能库

![CloudComputing-20190710111819223](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/CloudComputing-20190710111819223.png)

* 最关键的代码基础是——基本RPC、线程和控制流函数库的实现
* 主要功能是——实现区间创建、抽样和在本地磁盘上记录日志。
* 将复杂的功能实现限制在一个轻量级的核心功能库中——保证了Dapper的监控过程基本对应用层透明。

#### 二次抽样技术

利用二次抽样技术成功地解决了**低开销及广泛可部署性**的问题。

1. 第一次抽样。实践中，设计人员发现当抽样率低至1/1024时也能够产生足够多的有效监控数据，即在1024个请求中抽取1个进行监控也是可行的，从而可以捕获有效数据
2. 第二次抽样。发生在数据写入Bigtable前，具体方法是将监控id散列成一个标量z（0≤z≤1），如果某个区间的z小于事先定义好的汇总抽样系数，则保留这个区间并将它写入Bigtable，否则丢弃 

### Dapper使用心得

1. 新服务部署中Dapper的使用。利用Dapper对系统延迟情况进行一系列的跟踪，进而发现存在的问题
2. 定位长尾延迟（Addressing Long Tail Latency）。端到端性能和关键路径上的网络延迟有着极大的关系
3. 推断服务间的依存关系（Inferring Service Dependencies）。Google的“服务依存关系”项目使用监控注释和DPAI的MapReduce接口实现了服务依存关系确定的自动化
4. 确定不同服务的网络使用情况。利用Dapper平台构建了一个连续不断更新的控制台，用来显示内部集群网络通信中最活跃的应用层终端
5. 分层的共享式存储系统。没有Dapper之类的工具的情况下对于这种共享式服务资源的争用也同样难以调试
6. 利用Dapper进行“火拼”（Firefighting with Dapper）。Dapper用户可以通过和Dapper守护进程的直接通信，将所需的最新数据汇总在一起 

## Dremel————海量数据的交互式分析工具

### Dremel支持的典型应用

* Web文档的分析
* Android市场的应用安装数据的跟踪
* Google产品的错误报告
* Google图书的光学字符识别
* 欺诈信息的分析
* Google地图的调试
* Bigtable实例上的tablet迁移
* Google分布式构建系统的测试结果分析
* 磁盘I/O信息的统计
* Google数据中心上运行任务的资源监控
* Google代码库的符号和依赖关系分析

## Dremel的数据模型

#### 两方面的技术支撑

* 一方面：统一的存储平台
  实现高效的数据存储，Dremel使用的底层数据存储平台是GFS
* 另一方面：统一的数据存储格式
  存储的数据才可以被不同的平台所使用

#### 面向记录和面向列的存储

Google的Dremel是第一个在嵌套数据模型基础上实现列存储的系统。

![Dremel面向记录和面向列的存储](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/CloudComputing-Dremel.png)

优势：

* 处理时只需要使用涉及的列数据
* 列存储更利于数据的压缩

#### Dremel小结

* Dremel和MapReduce并不是互相替代，而是相互补充的技术。在不同的应用场景下各有其用武之地。
* Drill的设计目标就是复制一个开源的Dremel，但是从目前来看，该项目无论是进展还是影响力都达不到Hadoop的高度。
* 希望未来能出现一个真正有影响力的开源系统实现Dremel的主要功能并被广泛采用。

## PowerDrill————内存大数据分析系统

### PowerDrill产生背景与设计目标

现象：

* 在查询过程中，平均**92.41%**的数据被略去**5.02%**的数据会直接被缓存命中，一般仅须扫描**2.66%**的数据即可得到查询结果
* 超过**70%**的查询是不需要从磁盘访问任何数据的这些查询的平均访问延迟大约是**25秒**，**96.5%**的查询需要访问的磁盘量不超过**1GB**

背景：

* 绝大多数的查询是类似和一致的；
* 存储系统中的表只有一小部分是经常被使用的，绝大部分的表使用频率不高。

目的：

* 尽可能在查询中略去不需要的数据分块；
* 尽可能地减少数据在内存中的占用。（越少的内存占用意味着内存中可加载和处理的数据越多）

### ProwerDrill系统组成

* Web UI
* 一个抽象层
* 列式存储

### PowerDrill数据结构

PowerDrill采用的是一个双层数据字典结构

![CloudComputing-20190710154540235](/Users/eisenhao/Documents/CloudComputing/CloudComputing-20190710154540235.png)

### PowerDrill采用的性能优化

#### 数据分块

* 背景：传统的索引对于PowerDrill的查询场景作用不是很大，因此一个很自然的考虑就是对数据进行分块，过滤查询中不需要的数据块来减少数据量
* 分块方法：常见的分区方法有范围分区、散列分区等。PowerDrill实际采用的是一种组合范围分区方法。
* 分块步骤：a. 领域专家确定若干个划分的域；b. 利用这几个域对数据进行划分；c. 每个块的行数达到阈值时就停止划分。
* 局限性：域的确定需要领域专家（需要经验划分域）

#### 数据编码的优化

* 对于不同的块，如果我们可以确定块中不同值的数量，那么就可以根据这个数量值来选择可变的比特位来记录块id
* 有一个专有名词用于统计一组数中不同值的个数，称为“基数估计”
* 对于小规模的数据集，可以比较容易地统计出精确的基数。但是在大数据的环境下，精确的基数统计非常耗时，因此能保证一定精度的基数估计就可以满足实际的需求
* 基数估计的方法很多，大多利用了散列函数的一些特性，Google内部使用的是一种称为Hyperloglog的基数估计方法的变种

#### 全局字典优化

特性：

* 全局字典是有序的
* 排序后的数据常常有共同的前缀

备注：

* 实际使用中为了进一步减少查询中需要加载到内存的全局字典，对全局字典又进行了分块
* 对每个全局字典块还会维护一个布隆过滤器（bloom filter）来快速确定某个值是否在字典中

#### 压缩算法

不管压缩算法的解压速度多快，总会消耗一定的物理资源与时间。对此PowerDrill采用了一种**冷热数据**分别对待的策略。

在冷热数据切换策略中，比较常用的是LRU算法。PowerDrill开发团队采用了**启发式的缓存策略**来代替原始的LRU算法。

#### 行的重排

PowerDrill在实际生产环境中对数据分块时选定的那几个域按照字典序进行排序来得到重排的结果。数据压缩的算法有很多，比较常用的一种称为游程编码（Run-Length Encoding，RLE），又称行程长度编码，其好处是压缩和解压缩都非常快。

### PowerDrill与Dremel的对比

| **设计目标** | **处理非常大量的数据集**                 | **分析少量的核心数据集**                           |
| ------------ | ---------------------------------------- | -------------------------------------------------- |
| **设计理念** | 处理的数据来自外存                       | 处理的数据尽可能地存于内存                         |
|              | 未进行数据分区，分析时要扫描所有需要的列 | 使用了组合范围分区，分析时可以跳过很多不需要的分区 |
|              | 数据通常不需要加载，增加数据很方便       | 数据需要加载，增加数据相对不便                     |

## Google应用程序引擎

Google App Engine是一个由Python应用服务器群、Bigtable数据库及GFS数据存储服务组成的平台，它能为开发者提供一体化的可自动升级的在线应用服务。

特点：

* Google App Engine可以让开发人员在Google的基础架构上运行网络应用程序。
* 在Google App Engine中，用户可以使用appspot.com域上的免费域名为应用程序提供服务，也可以使用Google企业应用套件从自己的域为它提供服务。
* 可以免费使用Google App Engine。注册一个免费账户即可开发和发布应用程序，而且不需要承担任何费用和责任。

### Google App Engine的整体架构

![CloudComputing-20190710161656740](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/CloudComputing-20190710161656740.png)

### 应用程序环境的特性

* **动态网络服务**功能。能够完全支持常用的网络技术。
* 具有**持久存储的空间**。在这个空间里平台可以支持一些基本操作，如查询、分类和事务的操作。
* 具有自主平衡网络和系统的负载、自动进行**扩展**的功能。
* 可以对用户的**身份进行验证**，并且支持使用Google账户发送邮件。
* 有一个功能完整的**本地开发环境**，可以在自身的计算机上模拟Google          App Engine环境。
* 支持在指定时间或定期触发事件的**计划任务**。

### 沙盒的限制

* 用户的应用程序只能通过Google App Engine提供的网址抓取API和电子邮件服务API来访问互联网中其他的计算机，其他计算机如请求与该应用程序相连接，只能在标准接口上通过HTTP或HTTPS进行
* 应用程序无法对Google App Engine的文件系统进行写入操作，只能读取应用程序代码上的文件，并且该应用程序必须使用Google App Engine的Data Store数据库来存储应用程序运行期间持续存在的数据
* 应用程序只有在响应网络请求时才运行，并且这个响应时间必须极短，在几秒之内必须完成。与此同时，请求处理的程序不能在自己的响应发送后产生子进程或执行代码