layout: post
title: 开源白盒交换机系统 SONIC 简介
date: 2021/9/12 22:30:45
updated: 2021/9/12 22:10:45
comments: true
tags: 
- Network
categories:
- 技术

---

<img src="../../../../uploads/SONICArchitecture.png" class="full-image" />

<!-- more -->

# 1. 发展历程

- <b><font color="red" style="">2016 年</font></b>的 OCP 峰会上，由<b><font color="red" style="">微软</font></b>发布（基于** Debian** GNU/Linux）
- 目标：完善**白盒交换机**生态链
- 2017 “凤凰项目”，推动“**白盒+开源 OS**”的网络生态发展，促进国内开放网络和 SDN 网络的进步。由阿里巴巴、腾讯、**百度**、京东、中国移动和中国联通共同参与的“凤凰项目”成立，<br>项目以** SONiC 开源社区**为依托，选取社区稳定的 SONiC 版本软件，并将** Base OS、SAI、平台驱动**等共同打包制作成可直接加载运行在白盒交换机的**网络 OS 映像文件**，即**凤凰发行版**。<br>其中各公司项目分工如下：阿里巴巴主要负责社区软件评估及发行版制作；腾讯主要负责发行版软硬件兼容性；百度主要负责运维管理体系；中国信息通信研究院主要完成测试验证工作。
- 2017 年微软对 SONiC 的**性能**进行了大幅升级，全面支持 IDV，并且融合了更多的**容器特性**。
- 2018 年微软又在**管理性**上下了大力气（如 ConfigDB），让使用者用起来更加从容。
- 此后，SONiC 又在**深度学习**等** AI 特性**上做了更多的尝试。

# 2. 诞生基础——SAI

- 交换机抽象端口（Switch Abstraction Interface，SAI）。在没有 SAI 之前所有芯片都要**通过自己的 SDK 与上层的软件通信**（相当于用芯片自己的“**方言**”跟上层的操作系统通信），<br>SAI 把这类“方言”**标准化**，大家的芯片用“**标准化的语言**”与上层的控制软件通信。
- 正因为有了 SAI，所以才能建立一个操作系统（通过统一 API 与各交换机各组件通信）。有了 SAI 之后，适配 ASIC 的工作就由芯片厂商完成。
- SAI 本身没有完全开源，不过其却为 SONiC 提供了统一的 API，通过该统一的 API 可以向下对接不同的 ASIC（Application Specific Integrated Circuit，集成电路）。

# 3. 功能&特性
- 实现了数据**控制面**与**转发面**的分离
- 可以直接管理交换机状态
- 能够更快的调试、修复并测试软件
- 通过 **改变软件策略和拓扑** 实现 **新的网络架构**，让网络实践更为灵活
- SONiC 的网络应用都是基于容器构建的，可以非常方便的在生产环境实现 **不停机部署或升级** 应用

# 4. 独特优势

- 提供了将传统交换机 OS 拆分成多个容器化组件的解决方案
- 进而也定义了**控制面的容器化架构**，囊括了诸多组件和编程端口

# 5. SONIC 系统架构

SONIC 采用模块化体系结构，将每个模块放在独立的 **Docker 容器**中。其在保持组件之间的**高内聚性**的同时**减少**组件之间的**耦合**。<br>其主要组件包括：DHCP-Relay、Pmon、Snmp、LLDP、BGP、Teamd、Database、Swss、Syncd。其系统架构如下图所示。

<img src="../../../../uploads/SONICArchitecture.png" class="full-image" />

# 6. SONIC 中各容器功能简介

<table border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th></th>
        <th align="center"><b>容器名</b></th>
        <th align="center"><b>功能</b></th>
    </tr>
    <tr>
        <td align="center">1</td>
        <td align="center">Teamd</td>
        <td>负责实现链路聚合组 (Link Aggregation Group，LAG) 功能</td>
    </tr>
    <tr>
        <td align="center">2</td>
        <td align="center">Pmon</td>
        <td>负责监听“传感器”状态，在紧急状态时告警</td>
    </tr>
    <tr>
        <td align="center">3</td>
        <td align="center">Snmp</td>
        <td>负责实现简单网络管理协议（Simple Network Management Protocol，SNMP）功能，以支持远程管理网络</td>
    </tr>
    <tr>
        <td align="center">4</td>
        <td align="center">DHCP-Relay</td>
        <td>负责实现 DHCP 中继代理功能</td>
    </tr>
    <tr>
        <td align="center">5</td>
        <td align="center">LLDP</td>
        <td>负责实现链路层发现协议（Link Layer Discovery Protocol，LLDP）功能</td>
    </tr>
    <tr>
        <td align="center">6</td>
        <td align="center">BGP</td>
        <td>负责实现边界网关协议（Border Gateway Protocol，BGP）功能</td>
    </tr>
    <tr>
        <td align="center">7</td>
        <td align="center">Database</td>
        <td>承载 Redis 数据库引擎，以供 SONiC 应用程序访问数据</td>
    </tr>
    <tr>
        <td align="center">8</td>
        <td align="center">Swss</td>
        <td>负责交换状态服务（SWitch State Service，SWSS）功能，提供与网络应用程序和网络交换硬件<br>进行通信的数据库接口，以及提供呈现状态的服务。</td>
    </tr>
    <tr>
        <td align="center">9</td>
        <td align="center">Syncd</td>
        <td>提供支持交换机的<b>网络状态</b>与<b>实际硬件/ASIC 同步</b>的机制，包括端口的初始化、配置和 ASIC 电流状态的收集等。</td>
    </tr>
</table>

## 6.1. Teamd container

在 SONiC 设备中运行链路聚合功能 (LAG)。

- **teamd**：负责基于 Linux 的 LAG 协议的开源实现。

- **teamsyncd**：进程支撑“teamd”与南部子系统之间相互作用。

## 6.2. Pmon container

这是一个**守护进程**，负责监听“传感器”状态，包括定期记录硬件组件的传感器读数，并在高危情景下发出告警信号。

- **fancontrol**: 对风扇进行控制
- **sensord**：负责监听各传感器的状态

##  6.3. Snmp container

主要负责实现简单网络管理协议（Simple Network Management Protocol，SNMP），以远程管理网络。这个容器中有两个相关的进程，snmpd 和 snmp-agent (sonic_ax_impl)。

- **snmpd**：负责处理来自外部网络的 **snmp 轮询**。
- **snmp-agent**：是 SONiC 对可扩展代理协议 (Agent Extensibility，AgentX) 的实现。这个子代理向主代理 (snmpd) 提供 Redis 引擎 SONiC 数据库中汇聚后的信息。

## 6.4. Dhcp-relay container

负责实现 DHCP 中继代理功能。DHCP 中继代理可实现在不同子网和物理网段之间处理和转发 DHCP 信息的功能。

- **dhcprelay**：实现 DHCP 中继代理功能

## 6.5. LLDP container

负责实现链路层发现协议（Link Layer Discovery Protocol，LLDP）功能。该容器提供 hosts lldp 链路层发现协议功能，其主要包含三个相关进程：

- **lldp**：具有链路层发现功能的实际 LLDP 守护进程。负责与外部对等点建立 LLDP 连接，以接收或发布系统功能
- **lldp_syncd**：负责**上传** LLDP 发现的结果到集中式系统消息组件 (Redis-engine)。以便于其他组件（如：snmp）消费此 LLDP 状态信息。
- **lldpmgrd**：负责为 LLDP 守护进程提供**增量配置**功能。该容器通过订阅 Redis-engine 中的 STATE_DB 表来实现这一功能。

## 6.6. BGP container

负责实现边界网关协议（Border Gateway Protocol，BGP）功能。BGP 协议是一种实现自治系统（Autonomous System，AS）之间的路由可达，并**选择最佳路由**的距离矢量路由协议。运行支持的路由堆栈的 Quagga（路由软件工具）或 FRR（IP 快速重路由技术，Fast ReRoute）。尽管该容器是以 BGP 命名的，但实际上，这些路由协议栈还可以运行各种其他协议，如：OSPF、ISIS、LDP 等。容器主要包含三个进程：

- **bgpd**：负责**边界网关协议**功能的实现。通过 TCP/UDP 套接字接收来自外部各方的路由状态，并通过 zebra/fpmsyncd 端口下放到转发平面。
- **zebra**：充当传统的 IP **路由管理器**，负责跨不同协议提供内核路由表更新、端口查找和路由重分发服务。Zebra 还负责将计算出的转发信息库（Forwarding Information Base，FIB）推送到**内核**（通过进程间通信接口 Netlink）和（转发过程中所涉及的）**南向组件**（通过转发平面管理器 Forwarding Plane Manager，FPM 端口）。
- **fpmsyncd**：小型**守护进程**，负责收集 Zebra 生成的 FIB 状态，并将其内容转储到 Redis 引擎中的应用表 (APPL_DB)。

## 6.7. Database container

承载 Redis 数据库引擎，此引擎中保存的数据库可供 SONiC 应用程序<b>通过由 Redis-daemon 公开的 UNIX 套接字接口</b>访问。SONIC 中包含五个主要的数据库 DB：

1.  <font color="red">APPL_DB</font>： 存储所有应用程序容器<b>生成的状态</b>，包括：路由、下一跳、邻居等。这是与 SONiC 其他子系统交互的应用程序南方入口点。
2.  <b><font color="red">CONFIG_DB</font></b>： 存储由 SONiC 应用程序创建的 <b>配置状态</b> ，如：端口配置、VLAN 等。
3.  <font color="red">STATE_DB</font>： STATE_DB 存储了<b>跨模块依赖所必需的所有状态</b>，以用于解决 SONiC 不同子系统之间的 <b>依赖关系</b>。如：LAG 端口通道（由 teamd 子模块定义的）可引用系统中可能存在/不存在的物理端口。另一个例子是 VLAN 的定义（通过 vlanmgrd 组件） ，它可以引用在系统中存在不确定的端口成员。
4.  <b><font color="red">ASIC_DB</font></b>： 存储驱动特殊应用集成电路（Application Specific　Integrated Circuit，ASIC）的<b>配置和操作所需的状态</b>。这里的状态以 ASIC 友好的格式保存，以便于 Syncd 和 ASIC SDK 之间的交互。
5.  <font color="red">COUNTERS_DB</font>： 存储系统中每个端口相关联的<b>计数器/统计</b>信息。该信息可用于响应 CLI 的本地请求（查询统计信息）或用于为远程遥测提供信息。

SONIC 各**容器**与**各 Redis 表**间数据流交互关系如下图所示（详细交互流程可参见：[SONIC Architecture](https://github.com/Azure/SONiC/wiki/Architecture)）：

<img src="../../../../uploads/DataflowBetweenSONICContainerAndRedisTable.png" class="full-image" />

## 6.8. Swss container

负责交换状态服务（SWitch State Service，SWSS）功能，提供与网络应用程序和网络交换硬件进行通信的数据库接口，以及提供呈现状态的服务。该容器通过一组工具使得 SONiC 所有模块之间能够有效的通信，Swss 容器主要负责：提供了促进所有不同模块之间的**通信**的机制、承载了负责与 SONiC 应用层北向相互作用的进程、提供了允许 SONiC 应用程序和 SONiC 集中消息基础结构 (Redis-engine) 之间连接的方法。该容器主要包含三个**状态生成**进程和三个**状态分发**进程。

三个**状态生成进程**：

- **portsyncd**：侦听与端口相关的网络链接事件。在启动过程中，portsyncd 通过解析系统的硬件配置文件获取物理端口信息。**portsyncd** 最终将所有收集到的状态推送到 APPL_DB 中，如：端口速度、通道和 MTU 等属性。
- **Intfsyncd**：侦听与端口相关的网络链接事件，并将收集的状态 **推送到 APPL_DB** 中。如与端口关联的属性：新增/更改的 IP 地址。
- **Neighsyncd**：监听（由于 ARP 处理而被新发现的邻居触发的）与邻居相关的网络链接事件，如：MAC 地址和邻居的 Address-family 等属性的处理。这种状态最终将被用于构建 L2 时，重写所需的数据平面中的邻接表，并且所有收集到的状态最终都将被传输到 APPL_DB。

三个**状态分发进程**：

- **Orchagent**：作为 Swss 容器中最关键的组成部分，Orchagent 进程负责逻辑提取由 \*syncd 守护进程输入的相关状态（APPL_DB）、相应地处理和发送这些信息、并最终将其推送到其南向端口（ASIC_DB）。由此可知，Orchagent 既作为消费者（消费来自 APPL_DB 的状态），又作为生产者（将状态写入 ASIC_DB）。
- **IntfMgrd**：响应来自 APPL_DB、CONFIG_DB 和 STATE_DB 的状态，以在 Linux 内核中配置**端口**。（此步骤只有在所监听的所有数据库中没有冲突或不一致的状态时进行）
- **VlanMgrd**：响应来自 APPL_DB、CONFIG_DB 和 STATE_DB 的状态，以在 Linux 内核中配置** vlan-interfaces**。（只有在的依赖状态/条件全部满足时，才尝试执行此步骤）

## 6.9. Syncd container

提供一种允许交换机的**网络状态**与交换机的**实际硬件**/ASIC **同步**的机制，包括端口的初始化、配置和 ASIC 电流状态的收集等。其主要包含三个主要逻辑组件：

- **Syncd**：负责执行上面提到的同步逻辑的进程。在编译时与硬件供应商提供的 ASIC SDK 库进行同步链接，并通过调用 SDK 提供的端口将状态写入 ASIC。Syncd 既通过订阅 ASIC_DB 以接收来自 SWss 的状态，又作为发布者来上传硬件的状态。
- **SAI API**：交换机抽象端口定义的 API，提供一种独立于供应商的控制/转发接口，即交换 ASIC、NPU 或软件交换机的统一调用接口。
- **ASIC SDK**：硬件供应商预计将提供一个用于驱动其 ASIC 的、支持系统架构演进（System Architecture Evolution，SAE）的 SDK。此 SDK 通常以动态链接库的形式提供，负责驱动其执行的驱动进程。

# 7. 参考资料

- [SONIC 社区 WiKi](https://github.com/azure/sonic/wiki)
- [SONiC 用户手册](https://github.com/Azure/SONiC/blob/master/doc/SONiC-User-Manual.md)
- [SONIC 命令行参考](https://github.com/Azure/sonic-utilities/blob/master/doc/Command-Reference.md)
