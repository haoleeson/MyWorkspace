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

# 1. 查看端口

```shell
docker exec -it syncd /opt/bfn/install/bin/bfshell
ucli

# 查看端口信息
pm show
```

# 2. 进 sde 查看 光模块信息
```shell
docker exec -it syncd /opt/bfn/install/bin/bfshell
ucli

# 读取端口1 光模块信息
bf_pltfm qsfp dump-info 1/0
bf_pltfm qsfp dump-info 20/0
bf_pltfm qsfp dump-info 35/0
```

# 3. 查看设备眼图信息
```shell
bf-sde.bf_pltfm.rtmr> rtmr_eye_margin_show_all_chan 33 1
```

# 4. 端口的port-sd-show
```shell
pm show
info
bf_pltfm qsfp oper
bf_pltfm qsfp dump-info 33/0
pm port-sd-show 33/0
```

# 5. P4 查看 VLAN subinterface 表项
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

# 6. 禁用/启用端口相关指令
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

# 7. 手动 UP/DOWN 端口
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

# 8. 查看光模块厂商信息
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
