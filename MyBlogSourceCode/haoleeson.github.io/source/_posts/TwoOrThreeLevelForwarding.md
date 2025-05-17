layout: post
title: 二三层转发
date: 2021/9/5 22:30:45
updated: 2021/9/5 22:10:45
comments: true
tags:
- Network
categories:
- 技术

---

# 2. 二层转发

## 2.1. 简介

- 一种基于OSI中的**数据链路层（第二层）**的数据帧的存储转发技术，二层交换是依靠**MAC地址和VID号**来确定转发方向的。
- 二层转发通过维护MAC地址表以及根据目的MAC查表转发，有效的利用了网络带宽，改善了网络性能。

<!-- more -->

- 二层转发使得二层交换机各端口属于不同的冲突域，不同端口发送和接收的**数据独立**，因此有效地隔离了网络中物理层冲突域，使得通过它互连的主机（或网络）之间不必再担心流量大小对于数据发送冲突的影响。
- 二层转发通过专用集成电路（Application Specific Integrated Circuit，ASIC）来实现**硬件转发**，其转发性能非常高。

## 2.2. 二层转发流程介绍

### 2.2.1. 基础二层转发

二层交换机通过解析和学习以太网帧的<b><font color="red">源MAC地址</font></b>来维护MAC地址与端口的对应关系到**MAC地址表**。转发时，根据<b><font color="blue">目的MAC地址</font></b>检索 **MAC地址表** 来决定向哪个端口转发。

- 二层交换机记录各端口接收到的以太帧的，将其 <b><font color="red">源MAC地址</font></b>与接收的**端口** 的映射关系添加（或覆盖已有，并刷新老化时间）到**MAC地址表**中，作为以后的二层转发依据。
- 转发时，根据以太帧的<b><font color="blue">目的MAC地址</font></b>检索**MAC地址表**：
  - 若无法查到表项，则向除接收端口的所有端口转发；
  - 若可查到表项，
    - 但端口与太网帧的接收端口相同，则丢弃该帧；
    - 反之，则向记录端口转发；

**备注：** 二层交换机虽然能够隔离冲突域，但是它并不能有效的划分广播域，广播报文以及目的MAC查找失败的报文会向所有端口转发。当网络中主机数量增多时，这种情况会消耗大量的网络带宽，并且也会带来安全性相关问题。当然，通过路由器来隔离广播域是一个办法，但是由于路由器的高成本以及转发性能低的特点使得这一方法应用有限。基于这些情况，二层交换中出现了虚拟局域网（Virtual Local Area Network，VLAN）技术。

### 2.2.2. 带VLAN的二层转发

VLAN技术主要根据MAC地址将局域网**从逻辑上**划分为不同网段，从而实现虚拟工作组的一种交换技术。根据MAC地址维护方式的不同，可分为两种方式的二层转发：共享VLAN的MAC地址学习（Shared VLAN Learning，**SVL**）和独立VLAN的MAC地址学习（Independent VLAN Learning，**IVL**）。由于SVL只以**MAC地址作为表项**，学习后存表时不存储VLAN信息，故SVL方式具有 **在不同VLAN中相同MAC地址的多个主机存在通信冲突** 的问题。SVL现已比较少见，这里主要讨论IVL方式的二层转发，其将**MAC地址 + VLAN-ID**作为查找表项（也可理解为——每个VLAN都有自己独立的MAC地址表）。

- 二层交换机记录各个端口接收到以太帧的 <b><font color="red">源MAC地址</font></b> **+ VLAN-ID** 信息，并将其与对应端口的映射关系添加（或覆盖已有）到**MAC地址表中**
- 转发时，根据以太帧的<b><font color="blue">目的MAC地址</font></b> **+ VLAN-ID**检索**MAC地址表**：
  - 若无表项，则在**VLAN-ID**内广播；
  - 若存在表项，
    - 且记录端口与接收端口相同，则丢弃该帧；
    - 反之，则将该以太帧转发到表项记录端口；

## 2.3. MAC地址表的老化
二层交换机的MAC地址老化和刷新通常直接由硬件ASIC芯片来完成，其老化机制如下：
- 在芯片中储存的每一个动态添加的MAC地址表项都有一个 1 bit 的**老化标志**（1——保留；0——删除），同时芯片有一个**老化定时器**用于控制地址老化；
- 在学到MAC地址表项时：
  - 对于新学到的**MAC地址表项**，将其老化标志位置1；
  - 对于学到**MAC地址中已有的表项**（更新），将其老化标志位 置1；
- 在芯片的老化定时器超时触发时：
  - 对于老化标志位为1的表项，修改老化标志位为0；
  - 对于老化标志位为0的表项，删除该条表项记录。

**备注：** 由于新学到表项的时刻随机分布，故对每条表项，其实际老化时间为 1~2 倍的老化定时器周期。

# 3. 三层转发
## 3.1. 简介
- 一种基于OSI七层模型中 **第三层网络层** 的数据帧的存储转发技术，三层交换是主要依靠 **IP地址** 来确定转发方向，以实现不同网络间的通信。

## 3.2. 三层转发特点
- IP报文每经过一次三层转发，<b><font color="red" style="">其源/目的MAC地址都会变化</font></b>，但是<b><font color="blue" style="">其源/目的IP始终不变</font></b>。
- **一次路由，多次交换**。即首包通过CPU参与转发过程，同时建立交换芯片**硬件表项**，后续包由交换芯片**直接硬件转发**
- 交换芯片的硬件转发并不关心路由的具体下一跳IP，硬件三层表项只包含：目的IP地址/网段、目的IP（或下一跳IP）对应的MAC地址、出口VLAN、出端口

## 3.3. 路由器与交换机三层转发对比

<table border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th> </th>
        <th align="center"><b>路由器</b></th>
        <th align="center"><b>交换机</b></th>
    </tr>
    <tr>
        <td align="center">成本</td>
        <td align="center">高</td>
        <td align="center">低</td>
    </tr>
    <tr>
        <td align="center">实现方式</td>
        <td align="center">主要依靠CPU计算处理，少部分支持硬件转发</td>
        <td align="center">依靠ASIC硬件芯片集成IP三层转发功能<br>(检查IP报文头、修改存活时间参数、<br>重新计算IP头校验和、IP包的数据链路封装等)</td>
    </tr>
    <tr>
        <td align="center">转发性能</td>
        <td align="center">较弱</td>
        <td align="center">强</td>
    </tr>
    <tr>
        <td align="center">端口数量</td>
        <td align="center">少</td>
        <td align="center">多</td>
    </tr>
</table>

目前三层交换机一般通过VLAN来划分二层网络并实现二层交换（同网段），同时能够实现不同VLAN间的三层IP互访（不同网段）。

## 3.4. 组网一下的三层转发流程详细介绍

组网一如下图所示，源、目的主机都连接在同一台三层交换机上，但它们位于不同的VLAN(网段)。从三层交换机视角来说，源、目的主机都位于其直连网段，基础信息如下：

(**PC_A** , **MAC A**：AA-AA-AA-AA-AA-AA , IP: 1.1.1.2, NetMask: 255.255.255.0, GW: 1.1.1.1)<br>(Ethernet2 1.1.1.1  <->  **L3_SW**, **MAC_L3_SW**:CC-CC-CC-CC-CC-CC, NetMask: 255.255.255.0, <->  Ethernet3 2.1.1.1  )<br>(**PC_B** , **MAC B**：BB-BB-BB-BB-BB-BB , IP: 2.1.1.2, NetMask: 255.255.255.0, GW: 2.1.1.1)

<!-- L3_SW的交换芯片的三层MAC地址表内容如下（交换机的VLAN配置时写入）： -->

<!-- <table border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th align="center">MAC</th>
        <th align="center">VLAN-ID</th>
        <th align="center">Port</th>
    </tr>
    <tr>
        <td align="center">CC-CC-CC-CC-CC-CC</td>
        <td align="center">2</td>
        <td align="center">2</td>
    </tr>
    <tr>
        <td align="center">CC-CC-CC-CC-CC-CC</td>
        <td align="center">3</td>
        <td align="center">3</td>
    </tr>
</table> -->

当 <b><font color="red" style="">PC_A Ping PC_B</font></b> 时，即发起 ICMP 请求时，涉及的三层转发处理流程如下（假设主机均暂未建立任何硬件转发表项）：

<!-- **【1】**  **PC_A进行目标IP网段与自身的异同判断**:  -->
<b><font color="#7E3D76" style="">【1】 PC_A判断目标IP网段与自身的异同: </font></b>

**PC_A**对比报文的目的IP网段与自身网段（发现不在同一网段），需要进行三层转发（即，需通过网关转发报文信息）

<!-- **【2】**  **PC_A查询其ARP缓存表**:  -->
<b><font color="#7E3D76" style="">【2】 PC_A查询其ARP缓存表: </font></b>

**PC_A**检查自己的ARP缓存表，发现网关的MAC地址不在MAC地址表里，此时**PC_A**的ARP缓存表为空：

<table border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th>IP</th>
        <th>MAC</th>
    </tr>
    <tr>
        <td align="center"> </td>
        <td align="center"> </td>
    </tr>
</table>

<!-- **【3】**  **PC_A广播ARP请求报文**:  -->
<b><font color="#7E3D76" style="">【3】 PC_A广播ARP请求报文：</font></b>

**PC_A**在所处物理广播域内广播ARP请求报文（求取**L3_SW**网关IP(1.1.1.1)的MAC地址？），**PC_A**发送的ARP请求帧内容如下（广播）：

<table border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th> </th>
        <th colspan="3">Ethernet II Header</th>
        <th colspan="10">ARP Frame</th>
        <th>End</th>
    </tr>
    <tr>
        <td align="center">字段</td>
        <td align="center">DA</td>
        <td align="center">SA</td>
        <td>Type/Length</td>
        <td>HardwareType</td>
        <td>ProtocolType</td>
        <td>HardwareLen</td>
        <td>ProtocolLen</td>
        <td align="center">OP</td>
        <td align="center">SrcAddr</td>
        <td align="center">SrcIP</td>
        <td align="center">DesAddr</td>
        <td align="center">DesIP</td>
        <td>FilledField</td>
        <td>FCR</td>
    </tr>
    <tr>
        <td align="center">字段长度(Bytes)</td>
        <td align="center">6</td>
        <td align="center">6</td>
        <td align="center">2</td>
        <td align="center">2</td>
        <td align="center">2</td>
        <td align="center">1</td>
        <td align="center">1</td>
        <td align="center">2</td>
        <td align="center">6</td>
        <td align="center">4</td>
        <td align="center">6</td>
        <td align="center">4</td>
        <td align="center">18</td>
        <td align="center">4</td>
    </tr>
    <tr>
        <td align="center">填充值(0x)</td>
        <td align="center"><font color="blue">FF-FF-FF-FF-FF-FF</font></td>
        <td align="center"><font color="red">AA-AA-AA-AA-AA-AA</font></td>
        <td align="center"><b>0x0806</b></font></td>
        <td align="center">0x0001</td>
        <td align="center">0x0800</td>
        <td align="center">0x06</td>
        <td align="center">0x04</td>
        <td align="center"><b>0x01</b></td>
        <td align="center"><font color="red">AA-AA-AA-AA-AA-AA</font></td>
        <td align="center"><font color="red">01-01-01-02</font></td>
        <td align="center"><font color="blue">00-00-00-00-00-00</font></td>
        <td align="center"><font color="blue">01-01-01-01</font></td>
        <td align="center">00...00</td>
        <td align="center">/</td>
    </tr>
</table>

注：
- Ethernet II封装的以太帧头的"Type"字段中，**0x0806**表示其后为**ARP协议**
- OP为操作码，1表示ARP请求、2表示ARP应答、3表示RARP请求、4表示RARP应答
- 因物理传输数据帧最短需不低于64Bytes，故上文ARP帧需在填充区段填充18个字节长度的'0'。

<!-- **【4】**  **L3_SW接收到ARP请求报文**:  -->
<b><font color="#7E3D76" style="">【4】 L3_SW接收到ARP请求报文：</font></b>

**L3_SW**收到**PC_A**的ARP请求报文，并将**PC_A**的MAC地址学习到自己的MAC地址表和ARP缓存表。<br>**L3_SW**的MAC地址表内容如下：

<!-- <b><font color="red" style="">Q：MAC地址表中，转发标志位缺省值为TRUE么 ?</font></b> -->

<table border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th align="center">MAC</th>
        <th align="center">VLAN-ID</th>
        <th align="center">Port</th>
    </tr>
    <!-- <tr>
        <td align="center">CC-CC-CC-CC-CC-CC</td>
        <td align="center">2</td>
        <td align="center">2</td>
    </tr>
    <tr>
        <td align="center">CC-CC-CC-CC-CC-CC</td>
        <td align="center">3</td>
        <td align="center">3</td>
    </tr> -->
    <tr>
        <td align="center"><font color="green">AA-AA-AA-AA-AA-AA</font></td>
        <td align="center"><font color="green">2</font></td>
        <td align="center"><font color="green">2</font></td>
    </tr>
</table>

**L3_SW**的ARP缓存表内容如下：

<!-- <b><font color="red" style=""> Q：正确么？</font></b> -->

<table border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th align="center">IP</th>
        <th align="center">MAC</th>
    </tr>
    <tr>
        <td align="center"><font color="green">1.1.1.2</font></td>
        <td align="center"><font color="green">AA-AA-AA-AA-AA-AA</font></td>
    </tr>
</table>

注：为提升检索效率，交换机芯片中，MAC地址表与ARP表融合为一张表。

<!-- **【5】**  **L3_SW单播ARP应答报文**:  -->
<b><font color="#7E3D76" style="">【5】 L3_SW单播ARP应答报文：</font></b>

**L3_SW**发现自己的IP与**PC_A**发出ARP请求包的目的IP一致，向**PC_A**响应ARP应答报文，**L3_SW**向**PC_A**发送的ARP应答帧内容如下：

<table border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th> </th>
        <th colspan="3">Ethernet II Header</th>
        <th colspan="10">ARP Frame</th>
        <th>End</th>
    </tr>
    <tr>
        <td align="center">字段</td>
        <td align="center">DA</td>
        <td align="center">SA</td>
        <td>Type/Length</td>
        <td>HardwareType</td>
        <td>ProtocolType</td>
        <td>HardwareLen</td>
        <td>ProtocolLen</td>
        <td align="center">OP</td>
        <td align="center">SrcAddr</td>
        <td align="center">SrcIP</td>
        <td align="center">DesAddr</td>
        <td align="center">DesIP</td>
        <td>FilledField</td>
        <td>FCR</td>
    </tr>
    <tr>
        <td align="center">字段长度(Bytes)</td>
        <td align="center">6</td>
        <td align="center">6</td>
        <td align="center">2</td>
        <td align="center">2</td>
        <td align="center">2</td>
        <td align="center">1</td>
        <td align="center">1</td>
        <td align="center">2</td>
        <td align="center">6</td>
        <td align="center">4</td>
        <td align="center">6</td>
        <td align="center">4</td>
        <td align="center"><b>18</b></td>
        <td align="center">4</td>
    </tr>
    <tr>
        <td align="center">填充值(0x)</td>
        <td align="center"><font color="blue">AA-AA-AA-AA-AA-AA</font></td>
        <td align="center"><font color="red">CC-CC-CC-CC-CC-CC</font></td>
        <td align="center"><b>0x0806</b></td>
        <td align="center">0x0001</td>
        <td align="center">0x0800</td>
        <td align="center">0x06</td>
        <td align="center">0x04</td>
        <td align="center"><b>0x02</b></td>
        <td align="center"><font color="red">CC-CC-CC-CC-CC-CC</font></td>
        <td align="center"><font color="red">01-01-01-01</font></td>
        <td align="center"><font color="blue">AA-AA-AA-AA-AA-AA</font></td>
        <td align="center"><font color="blue">01-01-01-02</font></td>
        <td align="center">00...00</td>
        <td align="center">/</td>
    </tr>
</table>

**PC_A**收到**L3_SW**的ARP应答报文后，**PC_A**学习到**L3_SW**的MAC地址并添加到ARP缓存表。<br>此时**PC_A**的ARP缓存表内容如下：

<table border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th>IP</th>
        <th>MAC</th>
    </tr>
    <tr>
        <td align="center"><font color="green">1.1.1.1</font></td>
        <td align="center"><font color="green">CC-CC-CC-CC-CC-CC</font></td>
    </tr>
</table>

<!-- **【6】**  **PC_A组装并发送ICMP请求**:  -->
<b><font color="#7E3D76" style="">【6】 PC_A组装并发送ICMP请求：</font></b>

接着**PC_A**组装并发出目的IP为**PC_B**IP地址的ICMP请求报文（目的MAC为**L3_SW**的MAC）。**PC_A**向**PC_B**发出的ICMP请求帧内容如下：

<table width="1900" border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th> </th>
        <!-- <th colspan="7">Ethernet II Header</th> -->
        <th colspan="3">Ethernet II Header</th>
        <th colspan="12">IP Header</th>
        <th colspan="6">ICMP Frame</th>
        <th>End</th>
    </tr>
    <tr>
        <td align="center">字段</td>
        <td align="center">DA</td>
        <td align="center">SA</td>
        <!-- <td align="center">Type</td>
        <td>UserPriority</td>
        <td>Flag</td>
        <td>VLAN-ID</td> -->
        <td align="center">Type</td>
        <td>Version</td>
        <td>HeaderLen</td>
        <td>Priority</td>
        <td>TotalLen</td>
        <td>Identification</td>
        <td align="center">Flags</td>
        <td align="center">FragmentOffset</td>
        <td align="center">TTL</td>
        <td align="center">Protocol</td>
        <td align="center">Checksum</td>
        <td align="center">SrcIP</td>
        <td align="center">DesIP</td>
        <td align="center">Type</td>
        <td align="center">Code</td>
        <td align="center">Checksum</td>
        <td align="center">Identifier</td>
        <td align="center">SequenceNumber</td>
        <td align="center">OptionalData</td>
        <td align="center">FCR</td>
    </tr>
    <tr>
        <td align="center">字段长度(Bytes)</td>
        <td align="center">6</td>
        <td align="center">6</td>
        <!-- <td align="center">2</td>
        <td align="center">3bits</td>
        <td align="center">1bit</td>
        <td align="center">12bits</td> -->
        <td align="center">2</td>
        <td align="center">4bits</td>
        <td align="center">4bits</td>
        <td align="center">1</td>
        <td align="center">2</td>
        <td align="center">2</td>
        <td align="center">3bits</td>
        <td align="center">13bits</td>
        <td align="center">1</td>
        <td align="center">1</td>
        <td align="center">1</td>
        <td align="center">6</td>
        <td align="center">6</td>
        <td align="center">1</td>
        <td align="center">1</td>
        <td align="center">2</td>
        <td align="center">2</td>
        <td align="center">2</td>
        <td align="center">/</td>
        <td align="center">4</td>
    </tr>
    <tr>
        <td align="center">填充值(0x)</td>
        <td align="center"><font color="blue">CC-CC-CC-CC-CC-CC</font></td>
        <td align="center"><font color="red">AA-AA-AA-AA-AA-AA</font></td>
        <!-- <td align="center"><b>0x8100</b></td>
        <td align="center">000B</td>
        <td align="center">0B</td>
        <td align="center"><b>10B</b></td> -->
        <td align="center"><b>0x0800</b></td>
        <td align="center">0100B</td>
        <td align="center">0101B</td>
        <td align="center">0x00</td>
        <td align="center">0x005F</td>
        <td align="center">0x0000</td>
        <td align="center">000B</td>
        <td align="center">0B</td>
        <td align="center">0xFF</td>
        <td align="center"><b>0x01</b></td>
        <td align="center">/</td>
        <td align="center"><font color="red">01-01-01-02</font></td>
        <td align="center"><font color="blue">02-01-01-02</font></td>
        <td align="center"><b>0x08</b></td>
        <td align="center">0</td>
        <td align="center">/</td>
        <td align="center">/</td>
        <td align="center">0x01000001</td>
        <td align="center">0...0</td>
        <td align="center">/</td>
    </tr>
</table>

注：
- Ethernet II封装的以太帧头的"Type"字段中，**0x0800**表示其后为**IP协议**
- 在IP帧头的"Protocol"字段中，**0x01**表示其后为**ICMP协议**
- ICMP帧头的"Type"字段中，**0x08**表示请求，**0x00**表示响应。

<!-- **【7】**  **L3_SW接收ICMP报文，判断转发方式，查表**:  -->
<b><font color="#7E3D76" style="">【7】 L3_SW接收ICMP报文，判断转发方式，查表：</font></b>

**L3_SW**收到**PC_A**的ICMP请求报文。根据 **目的MAC地址+VLAN** 检索MAC地址表 或 查询 MyStation表是否存在目的MAC：
- 若存在则交换机需对该报文进行三层转发。
- 但实际不存在，接着根据 **目的IP(2.1.1.2)** 查找交换机芯片三层表项：
  - 若能查到，则进行硬件三层转发；
  - 但实际未查到，将报文送到CPU处理，CPU根据ICMP请求报文的 **目的IP(2.1.1.2)** 查找其**软件路由表**：
    - 若未能匹配，不同交换机处理方式不同（丢弃/ARP查询到后转发）
    - 匹配了一个直连网段<b><font color="blue">2.1.1.0</font></b>（即PC_B所在的网段），接着继续查找其**软件ARP表**中是否存在 **IP(2.1.1.2)** 的表项：
      - 若能查到，则更新源/目的MAC，并向 **IP(2.1.1.2)** 转发ICMP报文。
      - 但实际未查到，则需先发送ARP请求到 **IP(2.1.1.2)** 的MAC地址，再更新源/目的MAC和转发ICMP报文。

<br>此时**L3_SW**的交换芯片的MAC地址表内容如下：

<!-- <b><font color="red" style=""> Q：默认添加到交换芯片的表项的转发Flag值？</font></b> -->

<table border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th align="center">MAC</th>
        <th align="center">VLAN-ID</th>
        <th align="center">Port</th>
    </tr>
    <!-- <tr>
        <td align="center"><font color="blue">CC-CC-CC-CC-CC-CC</font></td>
        <td align="center"><font color="blue">2</font></td>
        <td align="center">2</td>
    </tr>
    <tr>
        <td align="center">CC-CC-CC-CC-CC-CC</td>
        <td align="center">3</td>
        <td align="center">3</td>
    </tr> -->
    <tr>
        <td align="center">AA-AA-AA-AA-AA-AA</td>
        <td align="center">2</td>
        <td align="center">2</td>
    </tr>
</table>

**L3_SW**的ARP缓存表内容如下：

<table border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th align="center">IP</th>
        <th align="center">MAC</th>
    </tr>
    <tr>
        <td align="center">1.1.1.2</td>
        <td align="center">AA-AA-AA-AA-AA-AA</td>
    </tr>
</table>

**L3_SW**的软件路由表内容如下：

<table border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th>NetworkDestination</th>
        <th>SubnetMask</th>
        <th>Gateway</th>
        <th>Interface</th>
        <th>Metric</th>
    </tr>
    <tr>
        <td align="center">1.1.1.1</td>
        <td align="center">255.255.255.0</td>
        <td align="center">1.1.1.0</td>
        <td align="center">Ethernet 2</td>
        <td align="center">/</td>
    </tr>
    <tr>
        <td align="center">2.1.1.1</td>
        <td align="center">255.255.255.0</td>
        <td align="center"><font color="blue">2.1.1.0</font></td>
        <td align="center">Ethernet 3</td>
        <td align="center">/</td>
    </tr>
</table>

<!-- **【8】**  **L3_SW发送ARP请求**： -->
<b><font color="#7E3D76" style="">【8】 L3_SW发送ARP请求：</font></b>

**L3_SW**向目标网段广播ARP请求报文（求取2.1.1.2的MAC地址），ARP请求帧内容如下：

<table border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th> </th>
        <th colspan="3">Ethernet II Header</th>
        <th colspan="10">ARP Frame</th>
        <th>End</th>
    </tr>
    <tr>
        <td align="center">字段</td>
        <td align="center">DA</td>
        <td align="center">SA</td>
        <td>Type/Length</td>
        <td>HardwareType</td>
        <td>ProtocolType</td>
        <td>HardwareLen</td>
        <td>ProtocolLen</td>
        <td align="center">OP</td>
        <td align="center">SrcAddr</td>
        <td align="center">SrcIP</td>
        <td align="center">DesAddr</td>
        <td align="center">DesIP</td>
        <td>FilledField</td>
        <td>FCR</td>
    </tr>
    <tr>
        <td align="center">字段长度(Bytes)</td>
        <td align="center">6</td>
        <td align="center">6</td>
        <td align="center">2</td>
        <td align="center">2</td>
        <td align="center">2</td>
        <td align="center">1</td>
        <td align="center">1</td>
        <td align="center">2</td>
        <td align="center">6</td>
        <td align="center">4</td>
        <td align="center">6</td>
        <td align="center">4</td>
        <td align="center">18</td>
        <td align="center">4</td>
    </tr>
    <tr>
        <td align="center">填充值(0x)</td>
        <td align="center"><font color="blue">FF-FF-FF-FF-FF-FF</font></td>
        <td align="center"><font color="red">CC-CC-CC-CC-CC-CC</font></td>
        <td align="center"><b>0x0806</b></td>
        <td align="center">0x0001</td>
        <td align="center">0x0800</td>
        <td align="center">0x06</td>
        <td align="center">0x04</td>
        <td align="center"><b>0x01</b></td>
        <td align="center"><font color="red">CC-CC-CC-CC-CC-CC</font></td>
        <td align="center"><font color="red">02-01-01-01</font></td>
        <td align="center"><font color="blue">00-00-00-00-00-00</font></td>
        <td align="center"><font color="blue">02-01-01-02</font></td>
        <td align="center">00...00</td>
        <td align="center">/</td>
    </tr>
</table>

<!-- **【9】**  **PC_B接收报文并学习ARP表**:  -->
<b><font color="#7E3D76" style="">【9】 PC_B接收报文并学习ARP表：</font></b>

**PC_B**收到ARP请求报文，更新ARP表。此时**PC_B**的ARP缓存表内容如下：

<table border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th>IP</th>
        <th>MAC</th>
    </tr>
    <tr>
        <td align="center"><font color="green">2.1.1.1</font></td>
        <td align="center"><font color="green">CC-CC-CC-CC-CC-CC</font></td>
    </tr>
</table>

<!-- **【10】**  **PC_B回应ARP应答报文**:  -->
<b><font color="#7E3D76" style="">【10】 PC_B回应ARP应答报文：</font></b>

PC_B发现目的IP是自己，于是向**L3_SW**发送ARP应答报文，ARP应答帧内容如下：

<table border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th> </th>
        <th colspan="3">Ethernet II Header</th>
        <th colspan="10">ARP Frame</th>
        <th>End</th>
    </tr>
    <tr>
        <td align="center">字段</td>
        <td align="center">DA</td>
        <td align="center">SA</td>
        <td>Type/Length</td>
        <td>HardwareType</td>
        <td>ProtocolType</td>
        <td>HardwareLen</td>
        <td>ProtocolLen</td>
        <td align="center">OP</td>
        <td align="center">SrcAddr</td>
        <td align="center">SrcIP</td>
        <td align="center">DesAddr</td>
        <td align="center">DesIP</td>
        <td>FilledField</td>
        <td>FCR</td>
    </tr>
    <tr>
        <td align="center">字段长度(Bytes)</td>
        <td align="center">6</td>
        <td align="center">6</td>
        <td align="center">2</td>
        <td align="center">2</td>
        <td align="center">2</td>
        <td align="center">1</td>
        <td align="center">1</td>
        <td align="center">2</td>
        <td align="center">6</td>
        <td align="center">4</td>
        <td align="center">6</td>
        <td align="center">4</td>
        <td align="center">18</td>
        <td align="center">4</td>
    </tr>
    <tr>
        <td align="center">填充值(0x)</td>
        <td align="center"><font color="blue">CC-CC-CC-CC-CC-CC</font></td>
        <td align="center"><font color="red">BB-BB-BB-BB-BB-BB</font></td>
        <td align="center"><b>0x0806</b></td>
        <td align="center">0x0001</td>
        <td align="center">0x0800</td>
        <td align="center">0x06</td>
        <td align="center">0x04</td>
        <td align="center"><b>0x02</b></td>
        <td align="center"><font color="red">BB-BB-BB-BB-BB-BB</font></td>
        <td align="center"><font color="red">02-01-01-02</font></td>
        <td align="center"><font color="blue">CC-CC-CC-CC-CC-CC</font></td>
        <td align="center"><font color="blue">02-01-01-01</font></td>
        <td align="center">00...00</td>
        <td align="center">/</td>
    </tr>
</table>

**L3_SW**收到**PC_B**的ARP应答报文后，**L3_SW**学习到**PC_B**的MAC地址并添加到ARP缓存表（三层表项，注：此后对三层交换机L3_SW来说，L3_SW到PC_A或PC_B的三层表项均已学习到，这样后续PC_A和PC_B之间经过交换机L3_SW互发报文时，可直接通过交换机芯片进行硬件三层转发）。<br>此时**L3_SW**的ARP缓存表内容如下：

<table border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th align="center">IP</th>
        <th align="center">MAC</th>
    </tr>
    <tr>
        <td align="center">1.1.1.2</td>
        <td align="center">AA-AA-AA-AA-AA-AA</td>
    </tr>
    <tr>
        <td align="center"><font color="green">2.1.1.2</font></td>
        <td align="center"><font color="green">BB-BB-BB-BB-BB-BB</font></td>
    </tr>
</table>

此时**L3_SW**的交换芯片的MAC地址表内容如下：

<table border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th align="center">MAC</th>
        <th align="center">VLAN-ID</th>
        <th align="center">Port</th>
    </tr>
    <tr>
        <td align="center">AA-AA-AA-AA-AA-AA</td>
        <td align="center">2</td>
        <td align="center">2</td>
    </tr>
    <tr>
        <td align="center"><font color="blue">BB-BB-BB-BB-BB-BB</font></td>
        <td align="center"><font color="blue">3</font></td>
        <td align="center">3</td>
    </tr>
</table>

<!-- **【11】**    **L3_SW接收ARP应答报文后，修改并转发ICMP请求**:  -->
<b><font color="#7E3D76" style="">【11】 L3_SW接收ARP应答报文后，修改并转发ICMP请求：</font></b>

**L3_SW**修改**PC_A**的ICMP请求包的源/目的MAC地址（目的MAC修改为**PC_B的MAC地址**、源MAC修改为**自己的MAC地址**），并转发给PC_B。转发的ICMP请求帧内容如下：

<table width="1900" border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th> </th>
        <!-- <th colspan="7">Ethernet II Header</th> -->
        <th colspan="3">Ethernet II Header</th>
        <th colspan="12">IP Header</th>
        <th colspan="6">ICMP Frame</th>
        <th>End</th>
    </tr>
    <tr>
        <td align="center">字段</td>
        <td align="center">DA</td>
        <td align="center">SA</td>
        <!-- <td align="center">Type</td>
        <td>UserPriority</td>
        <td>Flag</td>
        <td>VLAN-ID</td> -->
        <td align="center">Type</td>
        <td>Version</td>
        <td>HeaderLen</td>
        <td>Priority</td>
        <td>TotalLen</td>
        <td>Identification</td>
        <td align="center">Flags</td>
        <td align="center">FragmentOffset</td>
        <td align="center">TTL</td>
        <td align="center">Protocol</td>
        <td align="center">Checksum</td>
        <td align="center">SrcIP</td>
        <td align="center">DesIP</td>
        <td align="center">Type</td>
        <td align="center">Code</td>
        <td align="center">Checksum</td>
        <td align="center">Identifier</td>
        <td align="center">SequenceNumber</td>
        <td align="center">OptionalData</td>
        <td align="center">FCR</td>
    </tr>
    <tr>
        <td align="center">字段长度(Bytes)</td>
        <td align="center">6</td>
        <td align="center">6</td>
        <!-- <td align="center">2</td>
        <td align="center">3bits</td>
        <td align="center">1bit</td>
        <td align="center">12bits</td> -->
        <td align="center">2</td>
        <td align="center">4bits</td>
        <td align="center">4bits</td>
        <td align="center">1</td>
        <td align="center">2</td>
        <td align="center">2</td>
        <td align="center">3bits</td>
        <td align="center">13bits</td>
        <td align="center">1</td>
        <td align="center">1</td>
        <td align="center">1</td>
        <td align="center">6</td>
        <td align="center">6</td>
        <td align="center">1</td>
        <td align="center">1</td>
        <td align="center">2</td>
        <td align="center">2</td>
        <td align="center">2</td>
        <td align="center">/</td>
        <td align="center">4</td>
    </tr>
    <tr>
        <td align="center">填充值(0x)</td>
        <td align="center"><font color="blue">BB-BB-BB-BB-BB-BB</font></td>
        <td align="center"><font color="red">CC-CC-CC-CC-CC-CC</font></td>
        <!-- <td align="center"><b>0x8100</b></td>
        <td align="center">000B</td>
        <td align="center">0B</td>
        <td align="center"><b>10B</b></td> -->
        <td align="center"><b>0x0800</b></td>
        <td align="center">0100B</td>
        <td align="center">0101B</td>
        <td align="center">0x00</td>
        <td align="center">0x005F</td>
        <td align="center">0x0000</td>
        <td align="center">000B</td>
        <td align="center">0B</td>
        <td align="center">0xFF</td>
        <td align="center"><b>0x01</b></td>
        <td align="center">/</td>
        <td align="center"><font color="red">01-01-01-02</font></td>
        <td align="center"><font color="blue">02-01-01-02</font></td>
        <td align="center"><b>0x08</b></td>
        <td align="center">0</td>
        <td align="center">/</td>
        <td align="center">/</td>
        <td align="center">0x01000001</td>
        <td align="center">0...0</td>
        <td align="center">/</td>
    </tr>
</table>

<!-- **【12】**   **PC_B接收并响应ICMP报文**:  -->
<b><font color="#7E3D76" style="">【12】 PC_B接收并响应ICMP报文：</font></b>

PC_B收到L3_SW转发的ICMP请求后，向**PC_A**发送应答ICMP报文（目的MAC为**网关MAC地址**）。其中ICMP报文内容如下：

<table width="1900" border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th> </th>
        <!-- <th colspan="7">Ethernet II Header</th> -->
        <th colspan="3">Ethernet II Header</th>
        <th colspan="12">IP Header</th>
        <th colspan="6">ICMP Frame</th>
        <th>End</th>
    </tr>
    <tr>
        <td align="center">字段</td>
        <td align="center">DA</td>
        <td align="center">SA</td>
        <!-- <td align="center">Type</td>
        <td>UserPriority</td>
        <td>Flag</td>
        <td>VLAN-ID</td> -->
        <td align="center">Type</td>
        <td>Version</td>
        <td>HeaderLen</td>
        <td>Priority</td>
        <td>TotalLen</td>
        <td>Identification</td>
        <td align="center">Flags</td>
        <td align="center">FragmentOffset</td>
        <td align="center">TTL</td>
        <td align="center">Protocol</td>
        <td align="center">Checksum</td>
        <td align="center">SrcIP</td>
        <td align="center">DesIP</td>
        <td align="center">Type</td>
        <td align="center">Code</td>
        <td align="center">Checksum</td>
        <td align="center">Identifier</td>
        <td align="center">SequenceNumber</td>
        <td align="center">OptionalData</td>
        <td align="center">FCR</td>
    </tr>
    <tr>
        <td align="center">字段长度(Bytes)</td>
        <td align="center">6</td>
        <td align="center">6</td>
        <!-- <td align="center">2</td>
        <td align="center">3bits</td>
        <td align="center">1bit</td>
        <td align="center">12bits</td> -->
        <td align="center">2</td>
        <td align="center">4bits</td>
        <td align="center">4bits</td>
        <td align="center">1</td>
        <td align="center">2</td>
        <td align="center">2</td>
        <td align="center">3bits</td>
        <td align="center">13bits</td>
        <td align="center">1</td>
        <td align="center">1</td>
        <td align="center">1</td>
        <td align="center">6</td>
        <td align="center">6</td>
        <td align="center">1</td>
        <td align="center">1</td>
        <td align="center">2</td>
        <td align="center">2</td>
        <td align="center">2</td>
        <td align="center">/</td>
        <td align="center">4</td>
    </tr>
    <tr>
        <td align="center">填充值(0x)</td>
        <td align="center"><font color="blue">CC-CC-CC-CC-CC-CC</font></td>
        <td align="center"><font color="red">BB-BB-BB-BB-BB-BB</font></td>
        <!-- <td align="center"><b>0x8100</b></td>
        <td align="center">000B</td>
        <td align="center">0B</td>
        <td align="center"><b>10B</b></td> -->
        <td align="center"><b>0x0800</b></td>
        <td align="center">0100B</td>
        <td align="center">0101B</td>
        <td align="center">0x00</td>
        <td align="center">0x005F</td>
        <td align="center">0x0000</td>
        <td align="center">000B</td>
        <td align="center">0B</td>
        <td align="center">0xFF</td>
        <td align="center"><b>0x01</b></td>
        <td align="center">/</td>
        <td align="center"><font color="red">02-01-01-02</font></td>
        <td align="center"><font color="blue">01-01-01-02</font></td>
        <td align="center"><b>0x00</b></td>
        <td align="center">0</td>
        <td align="center">/</td>
        <td align="center">/</td>
        <td align="center">0x01000001</td>
        <td align="center">0...0</td>
        <td align="center">/</td>
    </tr>
</table>

<!-- **【13】**  **L3_SW硬件转发ICMP应答报文**:  -->
<b><font color="#7E3D76" style="">【13】 L3_SW硬件转发ICMP应答报文：</font></b>

**L3_SW**收到**PC_B**响应**PC_A**的应答报文后，根据 **目的MAC地址+VLAN** 检索MAC地址地址表：
- 能查到，则需对其进行三层转发。然后根据 **目的IP(1.1.1.2)** 查找交换机芯片三层表项：
  - 能查到，则通过交换机芯片实现**硬件三层转发**该ICMP应答报文（目的MAC修改为PC_A的MAC地址、源MAC修改为自己的MAC地址）。<br>

此时**L3_SW**的交换芯片的MAC地址表内容如下（交换机的VLAN配置时写入）：

<table border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th align="center">MAC</th>
        <th align="center">VLAN-ID</th>
        <th align="center">Port</th>
    </tr>
    <tr>
        <td align="center"><font color="blue">AA-AA-AA-AA-AA-AA</font></td>
        <td align="center">2</td>
        <td align="center">2</td>
    </tr>
    <tr>
        <td align="center">BB-BB-BB-BB-BB-BB</td>
        <td align="center">3</td>
        <td align="center">3</td>
    </tr>
</table>

**L3_SW**的ARP缓存表内容如下：

<table border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th align="center">IP</th>
        <th align="center">MAC</th>
        <!-- <th align="center">VLAN-ID</th>
        <th align="center">Port</th> -->
    </tr>
    <tr>
        <td align="center"><font color="blue">1.1.1.2</font></td>
        <td align="center"><font color="blue">AA-AA-AA-AA-AA-AA</font></td>
        <!-- <td align="center">2</td>
        <td align="center">2</td> -->
    </tr>
    <tr>
        <td align="center">2.1.1.2</td>
        <td align="center">BB-BB-BB-BB-BB-BB</td>
        <!-- <td align="center">3</td>
        <td align="center">3</td> -->
    </tr>
</table>

**L3_SW**硬件转发**PC_B**响应**PC_A**的应答报文内容如下：

<table width="1900" border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th> </th>
        <!-- <th colspan="7">Ethernet II Header</th> -->
        <th colspan="3">Ethernet II Header</th>
        <th colspan="12">IP Header</th>
        <th colspan="6">ICMP Frame</th>
        <th>End</th>
    </tr>
    <tr>
        <td align="center">字段</td>
        <td align="center">DA</td>
        <td align="center">SA</td>
        <!-- <td align="center">Type</td>
        <td>UserPriority</td>
        <td>Flag</td>
        <td>VLAN-ID</td> -->
        <td align="center">Type</td>
        <td>Version</td>
        <td>HeaderLen</td>
        <td>Priority</td>
        <td>TotalLen</td>
        <td>Identification</td>
        <td align="center">Flags</td>
        <td align="center">FragmentOffset</td>
        <td align="center">TTL</td>
        <td align="center">Protocol</td>
        <td align="center">Checksum</td>
        <td align="center">SrcIP</td>
        <td align="center">DesIP</td>
        <td align="center">Type</td>
        <td align="center">Code</td>
        <td align="center">Checksum</td>
        <td align="center">Identifier</td>
        <td align="center">SequenceNumber</td>
        <td align="center">OptionalData</td>
        <td align="center">FCR</td>
    </tr>
    <tr>
        <td align="center">字段长度(Bytes)</td>
        <td align="center">6</td>
        <td align="center">6</td>
        <!-- <td align="center">2</td>
        <td align="center">3bits</td>
        <td align="center">1bit</td>
        <td align="center">12bits</td> -->
        <td align="center">2</td>
        <td align="center">4bits</td>
        <td align="center">4bits</td>
        <td align="center">1</td>
        <td align="center">2</td>
        <td align="center">2</td>
        <td align="center">3bits</td>
        <td align="center">13bits</td>
        <td align="center">1</td>
        <td align="center">1</td>
        <td align="center">1</td>
        <td align="center">6</td>
        <td align="center">6</td>
        <td align="center">1</td>
        <td align="center">1</td>
        <td align="center">2</td>
        <td align="center">2</td>
        <td align="center">2</td>
        <td align="center">/</td>
        <td align="center">4</td>
    </tr>
    <tr>
        <td align="center">填充值(0x)</td>
        <td align="center"><font color="blue">AA-AA-AA-AA-AA-AA</font></td>
        <td align="center"><font color="red">CC-CC-CC-CC-CC-CC</font></td>
        <!-- <td align="center"><b>0x8100</b></td>
        <td align="center">000B</td>
        <td align="center">0B</td>
        <td align="center"><b>10B</b></td> -->
        <td align="center"><b>0x0800</b></td>
        <td align="center">0100B</td>
        <td align="center">0101B</td>
        <td align="center">0x00</td>
        <td align="center">0x005F</td>
        <td align="center">0x0000</td>
        <td align="center">000B</td>
        <td align="center">0B</td>
        <td align="center">0xFF</td>
        <td align="center"><b>0x01</b></td>
        <td align="center">/</td>
        <td align="center"><font color="red">01-01-01-02</font></td>
        <td align="center"><font color="blue">02-01-01-02</font></td>
        <td align="center"><b>0x00</b></td>
        <td align="center">0</td>
        <td align="center">/</td>
        <td align="center">/</td>
        <td align="center">0x01000001</td>
        <td align="center">0...0</td>
        <td align="center">/</td>
    </tr>
</table>

PC_A成功接收到PC_B发出的ICMP应答报文后整个Ping过程结束。<br>此后PC_A和PC_B之间往返报文都将（经过查MAC地址表，查交换机芯片三层转发表后）由交换芯片**直接完成硬件三层转发**。<br>经过上述流程的分析可知，三层交换机充分利用“**一次路由、多次转换**”的原理实现了转发性能与三层交换复杂业务的完美统一。

注：
-  一次路由：即首包通过CPU参与 **请求/转发**，再根据应答 **学习/建立** 交换芯片 **硬件表项**的“路由”过程（相对较慢，完成三层交换的必须的表项学习/建立流程）
-  多次交换：后续往返报文都可由交换芯片**直接硬件三层转发**（更快，提升转发性能）

## 3.5. 组网二下的三层转发流程介绍

另一种组网示例如下图所示，图中标明了两台主机的MAC、IP、网关以及两台三层交换机的MAC、不同VLAN配置的三层接口IP。且两台交换机分别预配置了静态路由：<br>其中 L3_SW1 静态路由配置为 ip route 2.1.1.0 255.255.255.0 3.1.1.2，L3_SW2 静态路由配置为 ip route 1.1.1.0 255.255.255.0 3.1.1.1。

当 <b><font color="red" style="">PC_A Ping PC_B</font></b> ，即发起 ICMP 请求时，三层转发处理流程如下（假设主机均暂未建立任何硬件转发表项）：

由于组网转发中间许多转发详细流程与具体请求帧分析已在3.5中介绍，这里不再赘述，下面主要介绍此组网示例下三层转发流程：

总结，其与组网一的主要区别在于第7步，组网一的L3_SW交换机在CPU查找软件路由表时**匹配了目的IP的直连网段**（2.1.1.0），然后广播找到直连网段内的PC_B并建立通信；而在本组网二中，L3_SW1交换机在CPU查找软件路由时<b><font color="red" style="">匹配了静态路由表项中某一下一跳网段（2.1.1.0/24）</font></b>。组网二多出的流程为，需将ICMP报文转发给下一跳(L3_SW2交换机)，并由L3_SW2交换机重复执行类似的CPU软件路由表查询、建表、转发ICMP请求报文、并最终转发ICMP应答报文回到L3_SW1，其他过程与组网一类似。

# 4. 总结

## 4.1. 二三层转发对比

<table border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th> </th>
        <th align="center"><b>二层转发</b></th>
        <th align="center"><b>三层转发</b></th>
    </tr>
    <tr>
        <td align="center">转发依据</td>
        <td align="center">MAC地址和VID号</td>
        <td align="center">IP地址</td>
    </tr>
    <tr>
        <td align="center">数据交换范围</td>
        <td align="center">同一网段</td>
        <td align="center">跨网段</td>
    </tr>
    <tr>
        <td align="center">所属OSI网络模型层级</td>
        <td align="center">数据链路层（第二层）</td>
        <td align="center">网络层（第三层）</td>
    </tr>
    <tr>
        <td align="center">是否需要二次封装</td>
        <td align="center">否</td>
        <td align="center">是</td>
    </tr>
</table>

## 4.2. 主机间通信机制及何时二三层转发？
- 当前主机收到以太网数据帧，解析**目的IP**
- 判断目的IP与自己IP是否位于同一网段（和掩码逻辑与）：
  - 若位于同一网段，则采用**二层转发**。（流程为：当前主机广播ARP请求（获取目的MAC地址），然后填充目的MAC并发送报文。）
  - 若为不同网段，则采用**三层转发**，通过网关转发报文。流程为：当前主机向网关发送ARP请求（获取网关的MAC地址），然后将网关MAC地址作为目的MAC地址并发送报文（注：此时目的IP仍未改动）

**其他判定方式**：交换芯片中的**MAC地址表**中会记录三层接口MAC+VID表项，且存在**MyStation表**。当报文进来时，用报文的目的MAC检索这两张表，若存在则需**三层转发**。

# 5. 参考资料
- 《H3C网络之路第六期——交换专题》
- [ARP 基础知识解析](https://blog.csdn.net/zqixiao_09/article/details/51170795)
- [ARP请求的详细过程](https://blog.csdn.net/qq_38902271/article/details/110213222)
