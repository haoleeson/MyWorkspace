layout: post
title: 数据中心网络DCN常见缩写词
date: 2022/1/23 22:30:45
updated: 2022/1/23 22:10:45
comments: true
tags: 
- Network
categories:
- 技术

---

|缩写词|全称|说明|
| :---- | :---- | :---- |
| DCN | Data Communicate Network | 数据通信网络 |
| ADC | Advance Data center Core | 高级数据中心，承载普通IDC数据中心到B1流量和不同机房间的直通流量 |
| CADC | Cloud Advance Data center Core | 高级云数据中心，承载公有云数据中心到B1流量和不同AZ间的直通流量 |
| DC | Data Center | 数据中心，承担普通IDC机房内集群间流量。当机房内多于一个集群时，增加DC设备，避免集群数量多、ADC设备端口紧张的问题，例如阳泉机房 |
| CDC | Cloud Data center Core | 公有云数据中心，承担公有云机房内集群间流量，当机房内多于一个集群时，增加CDC设备 |
| IC | Internal Core | 普通IDC数据中心中的内网核心 |
| CIC | Cloud Internal Core | 公有云机房中的内网核心 |
| IB | Internal Border | 普通IDC数据中心的ToR设备 |
| CIB | Cloud Internal Border | 公有云数据中心的ToR设备 |
| EC | External Core | 外网核心层交换机 |
| EB | External Border | 外网汇聚层交换机 |
| BC | Backbone Core | 外网核心层交换机|
| TOR | Top of Rack | 接入层交换机 |
| IB | Inner Border | 内网接入层交换机 |
| IC | Inner Core | 内网核心层交换机 |
| SC | Super Core | 内网超级核心层交换机 |
| 4 Post | | 一个集群由四个数据中心普通核心组成的网络架构，集群内为两层结构（ToR-IC），扩展性较弱 |
| CLOS | | 利用三层无阻塞网络构成组成集群的网络架构，集群内为三层结构（ToR-Leaf-Spine），扩展、备份、容灾性强 |
| Spine | | 核心层Spine交换机，在不同Pod间负责无阻塞连通的网络元素 |
| Leaf | | 汇聚层Leaf交换机，连接ToR的网络元素 |
| SV | | Server服务器 |
| PoD | | CLOS架构下，四个Leaf及下联设备构成的单元 |
| 服务器PoD | | 仅包含业务服务器的PoD |
| 基础服务PoD | | 包含基础服务IBGW、BIGNAT服务器的PoD |
| 出口PoD | | 负责集群间连接的PoD |