layout: post
title: OpenConfig北向接口简介
date: 2022/01/27 22:30:45
updated: 2022/01/27 22:50:45
comments: true
tags: 
- Common
categories:
- Network

---

# 1. 北向接口简介

## 1.1. 背景
SDN（Software-Defined Networking，软件定义网络）能够很好地实现网络服务的可定制化，包括网络的可编程性、控制与转发相分离和集中化控制。用户可通过 SDN 的北向接口对网络资源进行编排以定制出满足自身需求的服务

<!-- more -->

SDN控制器有南/北向两个接口，其中:
- 南向接口：用于连接底层网络。以 OpenFlow 为理论基础实现的南向接口已经在业内得到了广泛共识
- 北向接口：用于连接上层应用。由于网络资源的编排复杂度较高，各厂商技术积累和利益相关差异，导致北向接口尚未在业内形成统一标准

## 1.2. 北向接口定义
北向接口（Northbound Interface），为其他厂商或运营商提供的接入管理网络的接口。SDN北向接口的协议制定仍为当前SDN领域竞争的焦点，其标准化还处于起步阶段

## 1.3. 北向接口作用
- 可将不同的南向技术和协议进行归一化，为上层应用统一抽取南向视图
- 北向接口的标准化和开放接口传输，可克服传送网络设备的互操作困难，促进SDN网络的创新、自动化和智能管理
- 可提供开放的与设备供应商低相关的，可交互操作方式

# 2. 北向接口应用场景介绍
北向接口在友商中的应用场景介绍：
- 提升部署运维管理效率
- 赋能云网一体化平台
- 网络虚拟化——计算联动

## 2.1. 应用场景1：提升部署运维管理效率
华为开发了 AgileController-DCN，提供标准北向接口（支持协议：OpenFlow/OVSDB/NetConf/SNMP），可实现：
- 基于租户网络资源的动态发放
- 方便快捷的网络开通和资源调整
- 缩短业务上线周期

（北向接口赋能OpenStack）解决的传统问题：
- 业务部署效率低  -->  网络资源的池化和自动化部署、网络的建模和实例化
- 资源利用率低  -->  网络集中管控、协同虚拟与物理网络、应用到物理网络的自动映射
- 运维管理复杂  -->  构建全网视图、可视化运维、网络业务动态调度

## 2.2. 应用场景2：赋能云网一体化平台
华为基于AgileController-DCN提供的标准北向接口，搭建了统一虚拟化平台FusionSphere。其优势为：
- 统一资源管理
- 硬件兼容性强
- 业务调度自动化程度高

## 2.3. 应用场景3：实现网络虚拟化-计算联动
华为将 AgileController-DCN 提供的北向接口能力，应用于非云化数据中心，可实现计算与网络分开管理。其优势为：
- 基于AgileController-DCN提供的标准北向接口，进行网络自动化配置
- 与计算资源平台联动，协同分配调度资源，进行灵活而便捷的资源管理和业务下发

# 3. 网络设备可编程方式对比

||优势|不足|
|:----|:----|:----|
|CLI（命令行）|开发、调用简便|不同厂商、款型、软件版本的网络设备的CLI命令存在差异和兼容问题；<br>管理侧适配不同厂商、版本的cli命令工作量大，不适用于大规模、自动化管理与配置；<br>基于“cli命令翻译”的方式耦合度高，不便于维护（若命令发生变更，需指令变更-指令下发-设备全线适配）；|
|SNMP|应用广泛，在网络监控（信息采集、异常告警、可视化报表等）方面具有优势|在配置方面能力较欠缺或相对复杂|
|Netconf|与设备的具体命令解耦，管理/配置仅需关注各厂商提供Netconf内容层的配置和状态数据（Json、XML）|不同厂商的配置数据结构不同，管理侧需适配不同厂商的Netconf配置数据结构;<br>管理侧无法基于一套JSON（或XML）数据结构适配所有厂商的设备|
|NetConf 与结合 YANG|与具体的配置数据结构解耦（YANG）。开发配置简单，仅需关注YANG模型定义的配置数据/状态数据结构，并按需传入相应读取/配置RESTful请求参数即可|各设备厂商的私有YANG模型不兼容；<br>各设备厂商需使用自己的 SDN Controller 控制自己的设备，且互不兼容；<br>需适配各厂商SDN Controller或自研一个通用的SDN Controller（管理侧仍需须兼容维护各厂商设备）|
|OpenConfig|与设备厂商完全解耦，管理侧无需关注设备兼容及底层数据处理和传输，仅需基于“标准化”OpenConfig YANG及提供的gNMI接口，来管理和配置网络设备<br>（无需考虑底层数据传输、兼容适配等问题，由设备厂商来适配OC YANG）|尚处于推广阶段|