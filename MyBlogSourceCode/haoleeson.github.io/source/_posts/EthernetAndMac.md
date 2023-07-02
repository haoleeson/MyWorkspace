layout: post
title: 以太帧与MAC
date: 2021/7/23 22:30:45
updated: 2021/7/23 22:10:45
comments: true
tags: 
- Network
categories:
- 技术

---


# 1. 以太网数据帧结构
##  1.1. 802.3 Type 以太帧数据结构（又称 Ethernet II 封装，目前使用最广泛）：

<!-- more -->

<table border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th>字段名</th>
        <th>字段长度(Bytes)</th>
        <th>说明</th>
    </tr>
    <tr>
        <td align="center">Preamble</td>
        <td align="center">7</td>
        <td>与SFD共同构成前导码，内容为"101010..."1和0交替，通知接收方有数据帧到来；<br>同时同步时钟</td>
    <tr>
        <td align="center">SFD</td>
        <td align="center">1</td>
        <td>与Preamble共同构成前导码，内容为0xAB，标识下一字段为目的MAC；<br>物理层添加，非帧的一部分</td>
    </tr>
    <tr>
        <td align="center">DA</td>
        <td align="center">6</td>
        <td>目的MAC地址</td>
    </tr>
    <tr>
        <td align="center">SA</td>
        <td align="center">6</td>
        <td>源MAC地址</td>
    </tr>
    <tr>
        <td align="center">Type/Length</td>
        <td align="center">2</td>
        <td>若取值为0x0000 ~ 0x05DC，表示字段长度（0x05DC = 1500）；<br>若取值为0x0600 ~ 0xFFFF，表示该字段为Type</td>
    </tr>
    <tr>
        <td align="center">Payload</td>
        <td align="center">46 ~ 1500</td>
        <td>有效负荷（帧携带数据）</td>
    </tr>
    <tr>
        <td align="center">FCR</td>
        <td align="center">4</td>
        <td>校验和</td>
    </tr>
</table>

除上述Ethernet II封装格式外，以太网还有如下几种封装格式：

##  1.2. 802.3/802.2 LLC封装

<table border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th>字段名</th>
        <th>DA</th>
        <th>SA</th>
        <th>Length</th>
        <th>DSAP</th>
        <th>SSAP</th>
        <th>Ctrl</th>
        <th>Data</th>
    </tr>
    <tr>
        <td>字段长度(Bytes)</td>
        <td align="center">6</td>
        <td align="center">6</td>
        <td align="center">2</td>
        <td align="center">1</td>
        <td align="center">1</td>
        <td align="center">1</td>
        <td align="center">46 ~ 1500</td>
    </tr>
</table>

DSAP、SSAP用来标志上层协议，eg.NetBios时均为0xF0, IPX时均为0xE0

##  1.3. 802.3/802.2 SNAP封装

<table border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th>字段名/固定内容</th>
        <th>DA</th>
        <th>SA</th>
        <th>Length</th>
        <th>0xAA</th>
        <th>0xAA</th>
        <th>0x03</th>
        <th>Org Code</th>
        <th>PID</th>
        <th>Data</th>
    </tr>
    <tr>
        <td>字段长度(Bytes)</td>
        <td align="center">6</td>
        <td align="center">6</td>
        <td align="center">2</td>
        <td align="center">1</td>
        <td align="center">1</td>
        <td align="center">1</td>
        <td align="center">3</td>
        <td align="center">2</td>
        <td align="center">46 ~ 1500</td>
    </tr>
</table>

Org Code代表机构编码；PID为协议标志，很少使用

##  1.4. 802.3/802.2 SNAP RFC 1042封装

<table border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th>字段名/固定内容</th>
        <th>DA</th>
        <th>SA</th>
        <th>Length</th>
        <th>0xAA</th>
        <th>0xAA</th>
        <th>0x03</th>
        <th>00-00-00</th>
        <th>Type</th>
        <th>Data</th>
    </tr>
    <tr>
        <td>字段长度(Bytes)</td>
        <td align="center">6</td>
        <td align="center">6</td>
        <td align="center">2</td>
        <td align="center">1</td>
        <td align="center">1</td>
        <td align="center">1</td>
        <td align="center">3</td>
        <td align="center">2</td>
        <td align="center">46 ~ 1500</td>
    </tr>
</table>

一般说SNAP封装都指SNAP RFC1042封装

IP协议支持两种封装（**Ethernet II** 和 **SNAP RFC1042**封装，Type均为**0x0800**）。



# 2. MAC地址简介
MAC（Media Access Control）地址，是OSI模型第二层（数据链路层）数据包转发的依据，一个MAC地址有6字节，足以标识281万亿台设备，一般联网设备在出厂时会打上具有唯一标识的物理MAC地址。
## 2.1. MAC地址应用
上文介绍了传输中的以太网数据帧的各类封装结构，它们都包含一个目的MAC地址和一个源MAC地址，它的作用是标志帧的源节点和目的节点的**物理地址**。一个MAC地址有48bit（**6个字节**），从应用上可以分为**单播地址**、**组播地址**、**广播地址**：

<table border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th>地址类型</th>
        <th>格式</th>
        <th>示例</th>
        <th>说明</th>
    </tr>
    <tr>
        <td>单播地址</td>
        <td>第1字节的最低位为0</td>
        <td>00-AA-AA-AA-AA-AA</td>
        <td>用于标志唯一的设备</td>
    </tr>
    <tr>
        <td>组播地址</td>
        <td>第1字节的最低位为1</td>
        <td>01-BB-BB-BB-BB-BB</td>
        <td>用于标志同属一组的多个设备</td>
    </tr>
    <tr>
        <td>广播地址</td>
        <td>所有bit全为1</td>
        <td>FF-FF-FF-FF-FF-FF</td>
        <td>用于标志同一网段的所有设备</td>
    </tr>
</table>


# 3. 参考文献
* 《H3C网络之路第六期——交换专题》