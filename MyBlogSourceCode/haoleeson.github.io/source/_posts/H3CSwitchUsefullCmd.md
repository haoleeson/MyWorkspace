layout: post
title: H3C交换机常用命令
date: 2025/3/10 16:33:45
updated: 2025/3/10 16:33:45
comments: true
tags: 
- H3C
- Switch
categories:
- 技术

---

H3C交换机作为业内性价比较高的交换机设备，在业内被广泛使用，本文记录其一些工作中常用的接口、组网和诊断相关命令。

<!-- more -->


# 1. 接口
```shell
# 查看 interface
display interface brief

# 查看指定端口
display interface HGE1/0/11

# 配置双工模式
duplex { auto | full | half }

# 配置以太网接口的速率
speed {10|100 | 1000 |10000|25000|40000 |100000 |auto}

# 查看接口IP
display ip interface brief

# 查看 Vsi 接口
display interface Vsi-interface 148

# 查看 Tunnel 接口 
display interface Tunnel 1
```

## 1.1. 批量配置接口
```shell
# 进入系统视图
system-view

# 指定接口范围，并进入接口批量配置视图
# e.g. interface range HGE1/0/1 to HGE1/0/12
# e.g. interface range HGE1/0/13 to HGE1/0/20
# e.g. interface range HGE1/0/21 to HGE1/0/31
# e.g. interface range HGE1/0/1 to HGE1/0/20
# e.g. interface range HGE1/0/33 to HGE1/0/64
# e.g. interface range HGE1/0/1 to HGE1/0/64
interface range HGE1/0/60 to HGE1/0/61
interface range no1 to no2

undo lldp enable

# 批量设置端口类型为 trunk
port link-type trunk

# 批量配置端口速率 100G
speed 100000

# 批量配置为全双工模式
duplex full

#
display this
```

## 1.2. 端口拆分
```shell
# 进入系统视图
system-view

# 进入 100GE 以太网接口视图
interface hundredgige interface-number
# （或进入 40GE 以太网接口视图）
interface fortygige interface-number

# 将一个 40GE/100GE 接口拆分成四个 10GE 接口 （40/100 -> 4*10）
using tengige
# （或将一个 100GE 接口拆分成四个 25GE 接口 （100 -> 4*25）
using twenty-fivegige
```

## 1.3. 端口合并
```shell
# 进入系统视图
system-view

# 进入任意一个因拆分生成的 10GE 接口视图
# interface ten-gigabitethernet interface-number
interface Ten-GigabitEthernet1/0/61:1

# 进入任意一个因拆分生成的 25GE 接口视图
interface twenty-fivegige interface-number


# 将四个 10GE/25GE 拆分接口合并成一个 100GE 接口（4*10 / 4*25 -> 100）
using hundredgige
# （或将四个 10GE 拆分接口合并成一个 40GE 接口 （4*10 -> 40））
using fortygige
```

## 1.4. 添加 Tunnel 配置
```shell
# 新建 Tunnel
system-view
interface Tunnel 89 mode vxlan

# 设置 Tunnel src/dst ip
source 10.11.113.28
destination 192.168.0.14

# check Tunnel (统计值不会增长)
display interface Tunnel 89

# 更改 dcgw 绑定的 Tunnel
line vty 0 63
# 用新 Tunnel 覆盖
arp static 100.96.0.34 0001-0001-0101 Vsi-interface7000 Tunnel89 vsi Auto_L3VNI7000_7000 vpn-instance Vrf1234567

# 用新 Tunnel 覆盖 v6
ipv6 neighbor FD00:64:0:200::6460:22 0001-0001-0101 Vsi-interface7000 Tunnel89 vsi Auto_L3VNI7000_7000 vpn-instance Vrf1234567
ipv6 neighbor FE80::22 0001-0001-0101 Vsi-interface7000 Tunnel89 vsi Auto_L3VNI7000_7000 vpn-instance Vrf1234567
```

## 1.5. 配置三层 IP
```shell
system-view
interface HundredGigE 1/2/2
ip address 100.106.182.122 31
# (若已有 v6 地址，需要先删再加)
no ipv6 address
ipv6 address FD01:2::3 127
speed 100000
duplex full
description description message
no shutdown

# check
display ip interface HundredGigE 1/2/2 brief
display ipv6 interface HundredGigE 1/2/2 brief
ping ip 100.106.182.122
ping ipv6 FD01:2::3
```

## 1.6. 配置 VLAN
**向 vlan 添加成员端口**:
```shell
# 进入系统视图
system-view

# 创建 VLAN（进入 VLAN 视图）
vlan 100

# 添加端口
port interface-list
```

**为端口指定 vlan**:
```shell
# 进入系统视图
system-view

# 进入二层接口视图
# interface HundredGigE 1/0/21
interface interface-type interface-number
# （进入二层聚合接口视图）
interface bridge-aggregationinterface-number

# 配置端口链路类型为 access（默认）
port link-type access

# 将 Access 端口加入到指定 VLAN
port access vlan vlan-id

# 配置示例
interface HundredGigE 1/0/31
port trunk pvid vlan 1930
port trunk permit vlan 1930
no port trunk permit vlan 1
qu
```

## 1.7. LACP聚合口
```shell
# 显示聚合接口的相关信息
display interface [ { bridge-aggregation | route-aggregation } [ interface-number ] ] [ brief [ description | down ] ]

# 显示本端系统的设备ID
display lacp system-id

# 查看 Device 上所有聚合组的详细信息
display link-aggregation verbose
```

# 2. BGP
## 2.1. 配置 ip prefix-list
```shell
ipv6 prefix-list TO_SERVER_V6 index 10 permit FD01:2::3 64
# check
display ipv6 prefix-list name TO_SERVER_V6
display ipv6 prefix-list name FROM_SERVER_V6
```

## 2.2. 配置 route-policy
```shell
route-policy TO_SERVER_V6 permit node 10
if-match ipv6 address prefix-list TO_SERVER_V6
qu
route-policy TO_SERVER_V6 deny node 20
qu

# check
display route-policy name TO_SERVER_V6

route-policy FROM_SERVER_V6 permit node 10
apply as-path 64751 replace
qu

# check
display route-policy name FROM_SERVER_V6
```

## 2.3. 配置 v4 E-BGP (Group)
```shell
# 查看 BGP Group
display bgp group ipv4

system-view
bgp 64751

# 将 peer 添加到 bgp Group
undo peer 100.106.182.231
peer 100.106.182.225 group P4GW_V4
undo peer 100.106.182.235
peer 100.106.182.235 group P4GW_V4

# check
display bgp peer ipv4 100.106.182.229 verbose
display bgp peer ipv4 100.106.182.235 verbose
```

## 2.4. 配置 v4 E-BGP (非 Group)
```shell
# 查看 BGP routeid

display bgp peer ipv4

system-view
bgp 64751
# 注意：router-id 仅首次执行
# router-id 10.11.113.13
peer 100.106.182.231 as-number 64750
# 使用 Loop0 建立 I-BGP 注意：**E-BGP 无需执行下一行**
# peer 100.106.182.231 connect-interface loopback 0
# set 
peer 100.106.182.231 graceful-restart timer restart extra 240

address-family ipv4 unicast

# 设置 peer 的 keepalive timer 和 hold timer
peer 100.106.182.231 timer keepalive 10 hold 30

# 设置 peer 的同步路由间隔
peer 100.106.182.231 route-update-interval 0

peer 100.106.182.231 enable
quit

peer 100.106.182.235 as-number 64750
# 使用 Loop0 建立 I-BGP 注意：**E-BGP 无需执行下一行**
# peer 100.106.182.235 connect-interface loopback 0
address-family ipv4 unicast
peer 100.106.182.235 enable
quit

# check
display bgp peer ipv4
# display bgp peer ipv4 100.106.222.170 verbose
display bgp peer ipv4 100.106.182.231 verbose
display bgp peer ipv4 100.106.182.235 verbose
```

## 2.5. 配置 v6 E-BGP (Group)
```shell
display ip prefix-list name TO_SERVER_V4
display ipv6 prefix-list name TO_SERVER_V6
display route-policy name FROM_SERVER_V6
display route-policy name TO_SERVER_V6
display route-policy name FROM_RSW_V6
display route-policy name TO_RSW_V6
# 查看 BGP Group
display bgp group ipv6
# 查看某一 BGP Group
display bgp group ipv6 group-name RSW_V6
display bgp group ipv6 group-name P4GW_V6
display bgp group ipv6 group-name SERVER_V6

system-view
bgp 64751

# 将 peer 添加到 bgp Group
undo peer FD01:2::3
peer FD01:2::3 group P4GW_V6

# check
display bgp peer ipv6
display bgp peer ipv6 FD01:2::3 verbose
```

## 2.6. 配置 v6 E-BGP
```shell
# 查看 BGP routeid

display bgp peer ipv6

system-view
bgp 64751
peer FD01:2::3 as-number 64750
# 使用 Loop0 建立 I-BGP 注意：**E-BGP 无需执行下一行**
# peer FD01:2::3 connect-interface loopback 0

peer FD01:2::3 graceful-restart timer restart extra 240

address-family ipv6 unicast

# 设置 peer 的 keepalive timer 和 hold timer
peer FD01:2::3 timer keepalive 10 hold 30

# 设置 peer 的同步路由间隔
peer FD01:2::3 route-update-interval 0

peer FD01:2::3 enable
quit

peer FD01:2::3 as-number 64750
# 使用 Loop0 建立 I-BGP 注意：**E-BGP 无需执行下一行**
# peer FD01:2::3 connect-interface loopback 0
address-family ipv6 unicast

# 设置 peer 的 keepalive timer 和 hold timer
peer FD01:2::3 timer keepalive 10 hold 30

# 设置 peer 的同步路由间隔
peer FD01:2::3 route-update-interval 0

peer FD01:2::3 enable
quit

# check
display bgp peer ipv6
display bgp peer ipv4 FD01:2::3 verbose
```

## 2.7. 配置 BGP Group
```shell
system-view
bgp 64751
group SERVER_V6 external
peer SERVER_V6 as-number 64512
address-family ipv6
peer SERVER_V6 route-policy FROM_SERVER_V6 import
peer SERVER_V6 route-policy TO_SERVER_V6 export
peer SERVER_V6 advertise-community
peer SERVER_V6 advertise-ext-community

peer SERVER_V6 enable

# add v6 peer
peer FD01:2::3 group SERVER_V6

# check
display bgp group ipv6 group-name SERVER_V6
```

## 2.8. 查看 BGP 配置
```shell
# 查看当前 BGP 配置
display current-configuration configuration bgp

# 查看指定 route-policy 配置
display route-policy name TO_IDC_V4

# 查看指定 prefix-list 配置
display ip prefix-list name TO_IDC_V4
display ipv6 prefix-list name TO_SERVER_V6
# ipv6 prefix-list TO_SERVER_V6 index 10 permit FD01:2::3 64
```

## 2.9. 查看 BGP 配置概览
```shell
# 查看本机 BGP asn
display bgp instance-info

# 查看 v4 邻居
display bgp peer ipv4

display bgp peer ipv4 100.106.222.170 verbose

# 查看当前 bgp 配置详情
display current-configuration by-section include bgp
display current-configuration by-section include route-policy

# 查看 route policy 配置
display route-policy name FROM_BGPSPEAKER_V4
display route-policy name RP_TOVPC_V4_D
```

# 3. EVPN
## 3.1. l2vpn evpn 状态检查
```shell
# 查看 BGP 对端 连接状态
display bgp instance MYBGPINS peer l2vpn evpn
# 查看 BGP l2vpn evpn 简要信息
show bgp instance MYBGPINS l2vpn evpn
# 查看 BGP l2vpn evpn 邻居 group 信息
show bgp instance MYBGPINS group l2vpn evpn
# 查看 BGP instance path
show bgp instance MYBGPINS paths
# 查看 BGP instance vpnv4 路由表
show bgp instance MYBGPINS routing-table vpnv4
# [debug] 查看连接状态变更信息
display bgp instance MYBGPINS troubleshooting
# 查看 BGP l2vpn evpn 组更新信息
show bgp instance MYBGPINS update-group l2vpn evpn
```

## 3.2. 查看VPN内路由表
```shell
display ip routing-table vpn-instance Vrf1234567 verbose
display ip routing-table vpn-instance Vrf1234567 verbose
```

## 3.3. 手动配置 L2vpn Evpn peer（GROUP方式，推荐）
```shell
# 恢复 Group 配置
sys
 bgp 65001 instance MYBGPINS
 peer 10.11.119.78 group BGPSPEAKER_V4
display bgp instance MYBGPINS peer l2vpn evpn
```

## 3.4. 手动配置 L2vpn Evpn peer
```shell
bgp 65001 instance MYBGPINS
 peer 10.11.119.78 as-number 137720
 peer 10.11.119.78 source-address 10.11.113.28
address-family l2vpn evpn
  peer 10.11.119.78 enable
  peer 10.11.119.78 route-policy FROM_BGPSPEAKER_V4 import
  peer 10.11.119.78 route-policy RP_TOVPC_V4_D export
  peer 10.11.119.78 route-update-interval 0
  peer 10.11.119.78 password simple routesyncd

display route-policy name FROM_BGPSPEAKER_V4
display route-policy name RP_TOVPC_V4_D
```

## 3.5. 查看VPN内BGP路由
```shell
display bgp instance MYBGPINS routing-table vpnv4
# display bgp instance MYBGPINS routing-table vpnv4 route-distinguisher <VNI>:0
# e.g. 
display bgp instance MYBGPINS routing-table vpnv4 route-distinguisher 1234567:0
```


## 3.6. 添加EVPN v4路由
```shell
system-view
# ip route-static vpn-instance Vrf1234567 192.168.50.1 32 Vsi-interface5656 100.96.0.34 tag 1001
ip route-static vpn-instance Vrf1234567 27.100.34.213 32 HundredGigE 1/1/5.601 20.1.1.1 tag 1002

# check
# display route-static routing-table vpn-instance Vrf1234567
display bgp instance MYBGPINS routing-table vpnv4 route-distinguisher 1234567:0

# 查看 Vsi-interface
display interface Vsi-interface brief

# 删路由
no ip route-static vpn-instance Vrf1234567 27.100.34.213 32 HundredGigE 1/1/5.601 20.1.1.1
```

##  3.7. 添加EVPN v6路由
```shell
# ipv6 route-static vpn-instance Vrf1234567 fe80::216:3eff:fe52:753a 128 Vsi-interface148 fe80::22 tag 1001
ipv6 route-static vpn-instance Vrf1234567 fe80::216:3eff:fe52:753a 128 Vsi-interface148 fd00:64:0:200::6460:22 tag 1001
ipv6 route-static vpn-instance Vrf1234567 80::216:3eff:fe52:753a 128 Vsi-interface148 fd00:64:0:200::6460:22 tag 1001

# check
display bgp instance MYBGPINS routing-table vpnv6 route-distinguisher 1234567:0
```

## 3.8. Vrf ping
```shell
# VifLocalIp
display ip interface brief | include 1234567
display current-configuration interface HundredGigE 1/2/6.2315

# ping -vpn-instance Vrf<Vni> -c <Count> -m <Interval> -t <Timeout> -a <VifLocalIp> peerIp
ping -vpn-instance Vrf1234567 -c 10 -m 1 -t 10 -a 1.1.3.1 101.126.109.96
```

## 3.9. 查看路由表
```shell
# 查看是否收到 宣告的 10.11.113.137/32 
show ip routing-table 10.11.113.137 32

show ip routing-table 10.8.104.254 32

show ip routing-table 172.20.0.0 16
show ip routing-table 172.21.0.0 16


# 查看是否收到 宣告的 FD01:2::3/128
show ipv6 routing-table FD01:2::3 128
# 查看是否收到 宣告的 fd03::1/128
show ipv6 routing-table fd03::1 128
# 查看是否收到 宣告的 fd01::/64
show ipv6 routing-table fd01:: 64
```



# 4. 诊断
## 4.1. 查看历史日志
```shell
display diagnostic-logfile summary

# 查看过去 20 分钟日志
display logbuffer last-mins 20

display logfile
display security-logfile
display trace-logfile
```

## 4.2. 过滤日志中指定端口内容
```shell
display logbuffer | include 1/0/60
```


## 4.3. snmp
### 4.3.1. snmp查询交换机系统及端口统计信息
```shell
H3C_VTEP='10.0.0.2'

# 查看 H3C 交换机所有物理组件名 (entPhysicalName)，可获取 Board phy_index
snmpwalk -v 2c -c immense1 $H3C_VTEP .1.3.6.1.2.1.47.1.1.1.1.7

# 查看 H3C 交换机所有物理组件名 (entPhysicalName)
snmpwalk -v 2c -c immense1 $H3C_VTEP .1.3.6.1.2.1.47.1.1.1.1.7

# 查看H3C交换机【Board CPU 使用率】 (hh3cEntityExtCpuUsage)
# snmpwalk -v 2c -c immense1 $H3C_VTEP .1.3.6.1.4.1.25506.2.6.1.1.1.1.6.<phy_index>
snmpwalk -v 2c -c immense1 $H3C_VTEP .1.3.6.1.4.1.25506.2.6.1.1.1.1.6.14

# 查看H3C交换机【Board MEM 使用率】 (hh3cEntityExtMemUsage)
# snmpwalk -v 2c -c immense1 $H3C_VTEP .1.3.6.1.4.1.25506.2.6.1.1.1.1.8.<phy_index>
snmpwalk -v 2c -c immense1 $H3C_VTEP .1.3.6.1.4.1.25506.2.6.1.1.1.1.8.14
```

### 4.3.2. snmp 查询交换机 Qos queue 信息
```shell
H3C_VTEP='10.0.0.2'
IF_INDEX='5'  # HundredGigE1/1/1
IF_INDEX='37'  # FourHundredGigE1/0/31
QUEUE_ID='2'

# 查看H3C交换机指定 IF 指定 QUEUE_ID 的【已转发的报文 包数】 (hh3cIfQoSPassPackets)
snmpwalk -v 2c -c immense1 $H3C_VTEP .1.3.6.1.4.1.25506.2.65.1.1.2.1.1.1.${IF_INDEX}.${QUEUE_ID}

# 查看H3C交换机指定 IF 指定 QUEUE_ID 的【已转发的报文 字节数】 (hh3cIfQoSPassBytes)
snmpwalk -v 2c -c immense1 $H3C_VTEP .1.3.6.1.4.1.25506.2.65.1.1.2.1.1.3.${IF_INDEX}.${QUEUE_ID}

# 查看H3C交换机指定 IF 指定 QUEUE_ID 的【转发 报文速率 PPS】 (hh3cIfQoSPassPPS)
snmpwalk -v 2c -c immense1 $H3C_VTEP .1.3.6.1.4.1.25506.2.65.1.1.2.1.1.4.${IF_INDEX}.${QUEUE_ID}

# 查看H3C交换机指定 IF 指定 QUEUE_ID 的【转发 字节速率 BPS】 (hh3cIfQoSPassBPS)
snmpwalk -v 2c -c immense1 $H3C_VTEP .1.3.6.1.4.1.25506.2.65.1.1.2.1.1.5.${IF_INDEX}.${QUEUE_ID}

# 查看H3C交换机指定 IF 指定 QUEUE_ID 的【丢包 包数】 (hh3cIfQoSDropPackets)
snmpwalk -v 2c -c immense1 $H3C_VTEP .1.3.6.1.4.1.25506.2.65.1.1.2.1.1.2.${IF_INDEX}.${QUEUE_ID}

# 查看H3C交换机指定 IF 指定 QUEUE_ID 的【丢包 字节数】 (hh3cIfQoSDropBytes)
snmpwalk -v 2c -c immense1 $H3C_VTEP .1.3.6.1.4.1.25506.2.65.1.1.2.1.1.6.${IF_INDEX}.${QUEUE_ID}



# (不支持). 查看H3C交换机指定 IF 指定 QUEUE_ID 的【队列长度 包数】 (hh3cIfQoSQueueLengthInPkts)
snmpwalk -v 2c -c immense1 $H3C_VTEP .1.3.6.1.4.1.25506.2.65.1.1.2.1.1.7.${IF_INDEX}.${QUEUE_ID}

# (不支持). 查看H3C交换机指定 IF 指定 QUEUE_ID 的【队列长度 字节数】 (hh3cIfQoSQueueLengthInBytes)
snmpwalk -v 2c -c immense1 $H3C_VTEP .1.3.6.1.4.1.25506.2.65.1.1.2.1.1.8.${IF_INDEX}.${QUEUE_ID}

# (不支持). 查看H3C交换机指定 IF 指定 QUEUE_ID 的【当前排队的报文 包数】 (hh3cIfQoSCurQueuePkts)
snmpwalk -v 2c -c immense1 $H3C_VTEP .1.3.6.1.4.1.25506.2.65.1.1.2.1.1.9.${IF_INDEX}.${QUEUE_ID}

# (不支持). 查看H3C交换机指定 IF 指定 QUEUE_ID 的【转发峰值速率 PPS】 (hh3cIfQoSPeakPassPPS)
snmpwalk -v 2c -c immense1 $H3C_VTEP .1.3.6.1.4.1.25506.2.65.1.1.2.1.1.24.${IF_INDEX}.${QUEUE_ID}

# (不支持). 查看H3C交换机指定 IF 指定 QUEUE_ID 的【转发峰值速率 BPS】 (hh3cIfQoSPeakPassBPS)
snmpwalk -v 2c -c immense1 $H3C_VTEP .1.3.6.1.4.1.25506.2.65.1.1.2.1.1.25.${IF_INDEX}.${QUEUE_ID}
```


## 4.4. LLDP邻居信息
（缺省关闭）
```shell
system-view
voice-vlan track lldp

# 显示全局和所有接口的 LLDP 状态信息
display lldp status

# 显示LLDP本地信息
# display lldp local-information [ global | interface interface-type interface-number ]
display lldp local-information
display lldp local-information interface HundredGigE 1/0/32

# 查看 lldp 邻居
# display lldp neighbor-information [ [ [ interface interface-type interface-number ] [ agent { nearest-bridge | nearest-customer | nearest-nontpmr } ] [ verbose ] ] | list [ system-name system-name ] ]
display lldp neighbor-information
display lldp neighbor-information interface HundredGigE 1/0/32
```

## 4.5. QinQ
```shell
# 显示开启了QinQ功能的端口
# display qinq [ interface interface-type interface-number ]
display qinq
display qinq interface HundredGigE 1/0/1
```

## 4.6. Ping
```shell
ping A.B.C.D
```

## 4.7. 收集H3C设备诊断信息
```shell
display diagnostic-information flash:/di.tar.gz
```

## 4.8. 查询 H3C 设备 SN Serial Number
```shell
display device manuinfo
```


# 5. 配置
## 5.1. 查看当前配置
```shell
display current-configuration
display current-configuration | include arp | include 1234567
display current-configuration | include neighbor | include 1234567
```

## 5.2. 保存配置
保存位置：/
```shell
save back_cfg.cfg
```

## 5.3. 回滚配置
```shell
configuration replace file back_cfg.cfg
```