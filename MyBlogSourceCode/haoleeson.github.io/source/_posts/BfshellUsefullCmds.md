layout: post
title: Bfshell常用命令
date: 2023/2/28 10:30:45
updated: 2023/2/28 10:30:45
comments: true
tags:
- SDE
- Network
- Barefoot
- P4
categories:
- 技术

---

BFShell 作为 Barefoot 开发工具链中的重要一部分，可用于与 Tofino 交换机进行交互，例如加载 P4 程序、调试数据平面或配置交换机行为，此文记录日常调试中常用命令。

<!-- more -->

# 1. 端口
## 1.1. 查看端口

```shell
docker exec -it syncd /opt/bfn/install/bin/bfshell
ucli

# 查看端口信息
pm show
```

## 1.2. 手动 UP/DOWN 端口
bf-sde.pm> 中手动 up down 端口
> ucli
> pm
```shell
port-enb 1/0
port-enb 2/0
port-enb 17/0
port-enb 19/0
port-enb 39/0
port-enb 35/0
port-enb 40/0

port-dis 1/0
port-dis 2/0
port-dis 17/0
port-dis 19/0
port-dis 39/0
port-dis 40/0
```

## 1.3. 使能端口
```shell
bfshell> ucli
pm
port-add 17/0 100G RS
port-add 18/0 100G RS
port-add 19/0 100G RS
port-add 20/0 100G RS
port-add 21/0 100G RS
port-add 22/0 100G RS
port-add 23/0 100G RS
port-add 24/0 100G RS
port-add 25/0 100G RS
port-add 26/0 100G RS
port-add 27/0 100G RS
port-add 28/0 100G RS
port-add 29/0 100G RS
port-add 30/0 100G RS
port-add 31/0 100G RS
port-add 32/0 100G RS

port-add 33/0 100G RS
port-add 34/0 100G RS
port-add 35/0 100G NONE
port-add 36/0 100G NONE
port-add 37/0 100G NONE
port-add 38/0 100G NONE
port-add 39/0 100G RS
port-add 40/0 100G RS
port-add 41/0 100G NONE
port-add 42/0 100G NONE
port-add 43/0 100G NONE
port-add 44/0 100G NONE
port-add 45/0 100G RS
port-add 46/0 100G RS
port-add 47/0 100G RS
port-add 48/0 100G RS
port-add 49/0 100G RS
port-add 50/0 100G NONE
port-add 51/0 100G NONE
port-add 52/0 100G NONE
port-add 53/0 100G NONE
port-add 54/0 100G RS
port-add 55/0 100G RS
port-add 56/0 100G RS
port-add 57/0 100G NONE
port-add 58/0 100G NONE
port-add 59/0 100G NONE
port-add 60/0 100G NONE
port-add 61/0 100G RS
port-add 62/0 100G RS
port-add 63/0 100G RS
port-add 64/0 100G RS

port-loopback 17/0 mac-near
port-loopback 18/0 mac-near
port-loopback 19/0 mac-near
port-loopback 20/0 mac-near
port-loopback 21/0 mac-near
port-loopback 22/0 mac-near
port-loopback 23/0 mac-near
port-loopback 24/0 mac-near
port-loopback 25/0 mac-near
port-loopback 26/0 mac-near
port-loopback 27/0 mac-near
port-loopback 28/0 mac-near
port-loopback 29/0 mac-near
port-loopback 30/0 mac-near
port-loopback 31/0 mac-near
port-loopback 32/0 mac-near

port-enb 17/0
port-enb 18/0
port-enb 19/0
port-enb 20/0
port-enb 21/0
port-enb 22/0
port-enb 23/0
port-enb 24/0
port-enb 25/0
port-enb 26/0
port-enb 27/0
port-enb 28/0
port-enb 29/0
port-enb 30/0
port-enb 31/0
port-enb 32/0
port-enb 33/0
port-enb 34/0
port-enb 35/0
port-enb 36/0
port-enb 37/0
port-enb 38/0
port-enb 39/0
port-enb 40/0
port-enb 41/0
port-enb 42/0
port-enb 43/0
port-enb 44/0
port-enb 45/0
port-enb 46/0
port-enb 47/0
port-enb 48/0
port-enb 49/0
port-enb 50/0
port-enb 51/0
port-enb 52/0
port-enb 50/0
port-enb 51/0
port-enb 52/0
port-enb 53/0
port-enb 54/0
port-enb 55/0
port-enb 56/0
port-enb 57/0
port-enb 58/0
port-enb 59/0
port-enb 60/0
port-enb 61/0
port-enb 62/0
port-enb 63/0
port-enb 64/0
```

## 1.4. 禁用/启用端口相关指令
```shell
# 对比 配置值与实际值
# Compare sw/hw port cfg <dev> <pipe> <port>
warm 0 0 8
warm 0 0 12
warm 0 1 52
warm 0 1 60
warm 0 2 24
warm 0 2 20

# enabled 端口
# bf_port_enable  Enable a port <dev> <pipe> <port>
bf_port_enable 0 0 8
bf_port_enable 0 0 12
bf_port_enable 0 1 52
bf_port_enable 0 1 60
bf_port_enable 0 2 0
bf_port_enable 0 2 4
bf_port_enable 0 2 20

# disabled 端口
# bf_port_disable Disable a port <dev> <pipe> <port>
bf_port_disable 0 0 8
bf_port_disable 0 0 12
bf_port_disable 0 1 52
bf_port_disable 0 1 60
bf_port_disable 0 2 0
bf_port_disable 0 2 4
bf_port_disable 0 2 20

# bf_port_mtu_set Set MTU on a port <dev> <tx_mtu> <rx_mtu> <pipe> <port>
bf_port_mtu_set 0 9000 9000 0 8

# oper 查看端口状态值
oper

# 清除端口状态
# Clear stats on <dev> <pipe> <port>
bf_port_stats_clear 0 0 8
```

## 1.5. 端口的port-sd-show
```shell
pm show
info
bf_pltfm qsfp oper
bf_pltfm qsfp dump-info 33/0
pm port-sd-show 33/0
```

## 1.6. 定位端口丢包信息
```shell
fec
sd perf mon
port-error-show 33/0
port-sd-show 33/0
```

# 2. 光模块
## 2.1. 查看光模块信息
```shell
docker exec -it syncd /opt/bfn/install/bin/bfshell
ucli

# 读取端口1 光模块信息
bf_pltfm qsfp dump-info 1/0
bf_pltfm qsfp dump-info 20/0
bf_pltfm qsfp dump-info 35/0

# 查看光模块DDM信息
get-ddm      # Optical Module Digital Diagnostic Monitoring (DDM)

# 查看光模块信息
qsfp info  #Checking what's plugged in

# 展示光模块信息
qsfp show
```

## 2.2. 重启光模块
```shell
ucli
# 重启光模块 Ethernet34
bf-sde> bf_pltfm qsfp qsfp-reset 34 1
```

## 2.3. 查看光模块眼图信息
```shell
bf-sde.bf_pltfm.rtmr> rtmr_eye_margin_show_all_chan 33 1
```

## 2.4. 查看光模块厂商信息
```shell
# 查看硬件 QSFP 信息
bf-sde.bf_pltfm.qsfp> info

Port  Vendor           PN               rev Serial#          code     Bit Rate     OUI        Class            Media
---------------------------------------------------------------------------------------------------------------------
  1:  HG GENUINE(华工 100G CWDM4)       MTRQ-4CF51       00  CS20410010041    201123   25500 MBps   00:00:00   4 (3.5 W max.)   (SMF): 2 km
  2:  HG GENUINE       MTRQ-4CF51       01  3000027560048    220723   25500 MBps   00:00:00   4 (3.5 W max.)   (SMF): 2 km
 17:  INNOLIGHT(旭创 100G CWDM4)        TR-FC85S-N01     4A  ICMBPR260043     221028   25500 MBps   00:00:00   3 (2.5 W max.)   (Optical): 50 m   (OM3): 70 m
 19:  INNOLIGHT(旭创 100G CWDM4TR)        TR-FC13T-N00     4A  INKAO4981261     20041101 25500 MBps   00:00:00   4 (3.5 W max.)   (SMF): 2 km
 39:  Hisense(海信 100G SR4)          LTA8531-PC+      01  UPAA8000022      200801   25500 MBps   00:00:00   2 (2.0 W max.)   (Optical): 50 m   (OM3): 70 m
 40:  FINISAR CORP.(FINISAR 100G-SM-2KM+)    FTLC4352RJPL     A   X6FARV3          211110   25500 MBps   00:00:00   6 (4.5 W max.)   (SMF): 2 km
```

# 3. P4 查看 VLAN subinterface 表项
```shell
docker exec -it syncd /opt/bfn/install/bin/bfshell
bf_switch
show hostif handle 2

```

34/0 |41/0|280|2/24|100G   | RS |Ds|Au|YES|ENB|UP |  NONE  |           63753|           63735|

35/0 |42/0|276|2/20|100G   | RS |Ds|Au|YES|ENB|DWN|  NONE  |               0|               0|

> 华工 100G CWDM4:    port 1、2
> 旭创 100G CWDM4:    port 17
> 旭创 100G CWDM4TR:  port 19
> 海信 100G SR4:      port 39
> FINISAR 100G-SM-2KM+: port 40

bf-sde.pm show

# 4. bfrt 按需下业务表项
```shell
bfshell> bfrt_python
bfrt

switch.pipe.SwitchIngress.tunnel.dst_classifyv4.add_with_local_region_hit(0x1000064,31)

switch.servicepipe1.TableServiceEgress.tunnel_rewrite.set_gw_ip.set_default_with_set_gw_src_ip(0xc0c0c01,0xc0c0c010000000000000000)
switch.servicepipe1.tunnel_encap_1.add_with_encap_ipv4_vxlan(0b01,0x12b5)
switch.tablepipe23.TableIngress.tunnel_match.eip_to_eid.add_with_eip_hit(1,0x1000064,0x0007,0x0007)
switch.tablepipe23.TableIngress.tunnel_match.eip_info.add_with_set_eip_info(0x0007,0x0,0xC0A80003,0x0007e6,0xA000005)
switch.tablepipe23.TableIngress.tunnel_match.eid_add_bridge.add_with_encap_tunnel4in4(0x0007,0)
switch.tablepipe23.TableIngress.tunnel_match.eip_in_meter.add_with_set_eip_in_color(0x0007)
switch.tablepipe23.TableIngress.tunnel_match.eip_in_drop.add_with_in_drop_count(0x0007)
```

# 5. bfshell抓包
```shell
# 创建 snapshot（获取返回句柄 0x2581）
snap-create -d 0 -p 2 -s 0 -e 11 -i 0

#
# snap-trig-add -h 0x141 -n hdr_ipv4_dst_addr  -v 0xc0a80000 -m 0x1fff0000

snap-trig-add -h 0x2581 -n local_md_ingress_port -v 0x140 -m 0x1ff

# 开启抓包
snap-state-set -h 0x2581 -e 1
# 关闭抓包
snap-state-set -h 0x2581 -e 0

# 查看抓包结果
snap-capture-get -h 0x2581
```

# 6. 查看流统信息
查看 port 及 queue 流统
> queue.n = 8 * (port.n - 6) + 8 + 32，
> 其中 8 是每个 port 的队列数
> 6 除面板口外初始化的端口数（比如 CPU、RECIRC）
> 32 是 CPU 的队列数

```shell
docker exec -it syncd /opt/bfn/install/bin/bfshell
bf_switch

# 查看所有 port 流统 ( has port.[1~35]     value: only port.[4~7]  对应 front ethernet33~36 )
show counter port all
# 查看 port.6 流统（ port.6 == ethernet35 ）
show counter port handle 6

# 查看所有 queue 流统  ( queue.[1~288] ,          )
show counter queue all
# 查看所有 queue.40 流统  ( queue.[1~288] ,          )
show counter queue handle 40

```

# 7. 其他常用命令

```shell
ucli

# pipeline 管理
pipe_mgr
snap-create/snap-capture-get Packet Capture

# bfrt表项管理入口
bfrt_python
# 表项信息
info
# 导出表项内容
dump
# 添加/删除/查看表项
entry_add/delete/get
```

注：
- 当bfshell要执行的命令较多时，也直接传入文件执行批量命令内容
```shell
/opt/bfn/install/bin/bfshell -b /root/multiple_cmds
```

- 操作action_selector表项删除时出现 coredump

gRPC 使用 ROLLBACK_ON_ERROR 在操作 action_selector 的表项删除时出现 coredump
从 ROLLBACK_ON_ERROR 改成 CONTINUE_ON_ERROR 之后就不 coredump 了