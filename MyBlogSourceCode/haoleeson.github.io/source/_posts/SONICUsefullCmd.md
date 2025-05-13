layout: post
title: SONiC常用命令
date: 2024-01-20 22:30:45
updated: 2024-01-20 22:30:45
comments: true
tags:
- SONiC
- Network
categories:
- 技术

---

本文记录SONiC常用配置与排障命令

<!-- more -->

# 1. 端口

## 1.1. 查看端口状态
```shell
# 查看端口状态
show interfaces status

# 查看端口统计 出入包、错包统计、速率
show interfaces counters -p 60
```

## 1.2. 端口up/down
```shell
# DOWN 端口
sudo config interface shutdown Ethernet14

# DOWN 多端口（201911 无效）
sudo config interface shutdown Ethernet13,Ethernet16-20,Ethernet32

# UP 端口
sudo config interface startup Ethernet1
sudo config interface startup Ethernet33-35

# UP 多端口（201911 无效）
sudo config interface startup Ethernet33,Ethernet34-35
```

## 1.3. 添加三层IP
- 方法1：**修改配置文件**(/etc/sonic/config_db.json)
检查：
```shell
grep -A 10 MGMT_INTERFACE  /etc/sonic/config_db.json
```
配置：
```shell
"MGMT_INTERFACE": {
    "eth0|10.32.124.119/24": {
        "gwaddr": "10.32.124.1"
    },
    "eth0|FC00:2::32/64": {
        "gwaddr": "fc00:2::1"
    }
},
```

- 方法2：命令行
```shell
# 为端口添加三层 IP
##  - config interface ip add <interface_name> <ip_addr>
sudo config interface ip add Ethernet2 10.0.0.5/24
sudo config interface ip add Ethernet3 20.0.0.5/24
sudo config interface ip add Ethernet63 10.11.12.13/24
sudo config interface ip add eth0 20.11.12.13/24 20.11.12.254
sudo config interface ip add eth0 10.32.124.119/24 10.32.124.1

# 添加 IP
sudo ip addr add fdbd:ff1:ce00:14::129/128 dev eth0
sudo ip addr del fdbd:ff1:ce00:14::129/128 dev eth0

# 删除三层 IP
sudo config interface ip remove Ethernet2 10.0.0.5/24
sudo config interface ip remove Ethernet3 10.0.0.4/31
sudo config interface ip remove Ethernet8 20.0.0.1/24
sudo config interface ip remove Ethernet4 10.0.0.1/24
```

- 方法3：cli 配置管理 IP
```shell
cli
sonic> configure terminal
sonic(config)# interface-config
sonic(interface config)# management
sonic(interface mgmt)# ipv4-family
sonic(interface mgmt v4)# address 192.168.3.35/24
```

## 1.4. 聚合链路
```shell
# 查看
show interfaces portchannel

# 创建/删除 聚合链路
##  - config portchannel (add | del) <portchannel_name> [--min-links <num_min_links>] [--fallback (true | false)  [--fast-rate (true | false)]
sudo config portchannel add PortChannel0011
sudo config portchannel del PortChannel0011

# 聚合链路 添加/移除 成员端口
##  - config portchannel member (add | del) <portchannel_name> <member_portname>
sudo config portchannel member add PortChannel0011 Ethernet13
sudo config portchannel member del PortChannel0011 Ethernet13
```

## 1.5. VLAN
**命令行方式**：
```shell
# 查看
show vlan brief
show vlan config

# 添加删除 VLAN
##  - config vlan (add | del) <vlan_id>
sudo config vlan add 100
sudo config vlan del 100

# 添加删除 VLAN 成员端口
##  - config vlan member add/del [-u|--untagged] <vlan_id> <member_portname>
### （带 tag）
sudo config vlan member add 100 Ethernet13
sudo config vlan member del 100 Ethernet13
### （不带 tag）
sudo config vlan member add -u 100 Ethernet14
sudo config vlan member del 100 Ethernet14
```

**cli方式**：
eg. cli 配置 3.57 设备上直连端口 55 的三层 IP

```shell
# 查看物理端口（all / 端口 55）
/usr/bin/cli -c 'show interfaces status ethernet 63'
/usr/bin/cli -c 'show interfaces status ethernet 32'
# 查看已配置 VLAN 信息
/usr/bin/cli -c 'show vlan brief'
# 查看设备当前三层接口状态
/usr/bin/cli -c 'show ip interfaces'

cli
configure terminal
vlan-config         # 进入 vlan 视图
vlan 1055           # 创建 vlan 1055
member port 55      # 将 55 端口添加到此 vlan（此 55 已配在 Portchannle 4）
member portchannel 4 # 或将 Portchannel4 添加到此 vlan（此 Portchannel 4 已配在 vlan60）

# 切换到 interface 视图
SONiC(vlan member)# exit
SONiC(vlan)# exit
SONiC(vlan config)# exit
SONiC(config)# interface-config

# 创建三层接口并进入 vlan-interface 视图
SONiC(interface config)# vlan-interface <1-4094>

# 配置 ipv4/ipv6 地址
SONiC(interface vlanif)# ipv4-family
SONiC(interface vlanif v4)# address X.X.X.X/M
SONiC(interface vlanif)# ipv6-family
SONiC(interface vlanif v6)# address X:X::X:X/M
```

**删除VLAN**：
```shell
cli
configure terminal
SONiC(config)# interface-config
sonic(interface config)# no vlan-interface 101
sonic(interface config)# exit
sonic(config)# vlan-config
sonic(vlan config)# no vlan 101
```

## 1.6. 光模块
```shell
# 显示光模块 eeprom 信息
sudo sfputil show eeprom
show interfaces transceiver eeprom

# 光模块-在位状态
sudo sfputil show presence
show interfaces transceiver presence

# 光模块-低功耗模式
sudo sfputil show lpmode
show interfaces transceiver lpmode

# 查看特定模块
show interfaces transceiver eeprom --dom Ethernet1

# 开启光模块低功耗模式 sfputil lpmode <端口>
sudo sfputil lpmode Ethernet12

# 复位光模块 sfputil reset <端口>
sudo sfputil reset Ethernet1
```

# 2. 常用 cli 命令
## 2.1. 从 cli 进入 Linux shell
```shell
start shell bash
```

## 2.2. bcmsh 下执行脚本模拟端口震荡
```shell
# bcmsh 下执行脚本模拟端口震荡
for i=0,1000 'port ce en=0; sleep 2; port xe en=1; sleep 8'
```

## 2.3. 常用 cli 命令
```shell
# 查看设备当前三层接口状态
/usr/bin/cli -c 'show ip interfaces'

# 查看端口简要状态信息（all / 端口 55）
/usr/bin/cli -c 'show interfaces status'
/usr/bin/cli -c 'show interfaces status ethernet 1'

# 查看 portchannle 信息
/usr/bin/cli -c 'show interfaces portchannel'

# 查看已配置 VLAN 信息
/usr/bin/cli -c 'show vlan brief'

# 查看交换机 AAA 配置
/usr/bin/cli -c 'show system-config aaa'
/usr/bin/cli -c 'show system-config tacacs'

# 查看端口详细统计信息
/usr/bin/cli -c 'show interfaces detail ethernet 1'

# 查看端口计数信息
/usr/bin/cli -c 'show interfaces counters'

# 查看 bgp 信息
/usr/bin/cli -c 'show bgp summary'

# 查看 bgp 路由信息
/usr/bin/cli -c 'show route ipv6 bgp'

# cli 查看端口统计
/usr/bin/cli -c 'show interfaces brief'
/usr/bin/cli -c 'show interfaces detail ethernet 55'

# cli 清零端口统计计数
/usr/bin/cli -c 'clear interface statistics port 55'
```

# 3. 路由
## 3.1. 增删路由
```shell
# add
# config route add prefix <A.B.C.D/M> nexthop <dev <dev_name>>
sudo config route add prefix 10.32.124.0/24 nexthop dev eth0
sudo config route add prefix 10.32.124.0/24 nexthop dev management0

# del
sudo config route del prefix 10.32.124.0/24 nexthop dev eth0

# 添加路由
sudo ip route add 10.0.0.0/24 dev eth0
sudo ip route add 20.0.0.2 dev Ethernet8
sudo ip route add 20.0.0.2/24 via 10.201.40.80 dev eth0
sudo ip route add 20.0.0.2 dev Ethernet8 scope link protocol kernel src 10.0.0.5
sudo ip route add 20.0.0.1 scope link protocol kernel src 10.0.0.5

sudo ip route add 20.0.0.5 via 10.0.0.5 dev Ethernet4

sudo ip route add 20.0.0.5 dev Ethernet4 scope link protocol kernel src 10.0.0.5

# 删除
ip route del 10.201.40.0/24 via 10.201.40.65
ip route del 10.201.40.0/24 via 10.201.40.69 10.201.40.65

ip route del 10.201.40.0/24 via 10.201.40.65
ip route del 10.201.40.0/24 via 10.201.40.65 dev eth0
```

## 3.2. 查看arp表
```shell
# 查看 arp 表
sudo arp -vn | grep ''
# 或
sudo arp -n

# 删除指定 ip 的 arp 表项
arp -d 192.168.0.8

arp -s <host> <hwaddr>
arp -s 10.0.0.33 660102030405

# 清除指定 interface 的 arp
sudo ip link set arp off dev Ethernet2; sudo ip link set arp on dev Ethernet2

# 刷新所有记录的 arp 表项
ip -s -s neigh flush all

## 删除所有 arp 表项
arp -d -a
```

# 4. BGP
## 4.1. 配置 BGP 邻居
```shell
configure terminal
    router bgp <唯一 AS 号>                      # 进入 bgp 视图
    bgp router-id <本地环回地址>                # 配置环回地址作为 route-id
    bgp fast-external-failover                # 使能 fast-external-failover
    bgp network import-check                  # 开启 network 路由检查
    bgp graceful-restart                      # 启用 graceful-restart
    # bgp bestpath as-path multipath-relax    # 使能 ecmp
    # bgp always-compare-med                  # 启用 always-compare-med

    address-family ipv4
        maximum-paths 64                  # 设置 ipv4 ecmp 最大路径数量
        network <本地环回地址>/32           # 发布 v4 路由（宣告本地环回地址）
        redistribute kernel	              # 重分发 kernel 路由
    exit-address-family

    # 添加 BGP 邻居
    neighbor <邻居端直连端口的三层 IP> remote-as <邻居唯一 AS 号>
    # 激活邻居
    address-family ipv4
        neighbor <邻居端直连端口的三层 IP> activate
    exit-address-family
```

## 4.2. 停止/打开BGP邻居
```shell
# 停止/打开 所有 BGP Neighbor 链路（发 ADMIN_SHUTDOWN notify）
sudo config bgp shutdown all
sudo config bgp startup all

# 停止/打开 某一 BGP Neighbor 链路
sudo config bgp shutdown neighbor 10.0.0.37
sudo config bgp startup neighbor 10.0.0.37

# 通过改 redis 表项停止/打开 某一BGP Neighbor 链路
redis-cli -h 127.0.0.1 -n 4 -p 6379 HSET "BGP_NEIGHBOR|10.0.0.57" 'admin_status' 'down'
redis-cli -h 127.0.0.1 -n 4 -p 6379 HSET "BGP_NEIGHBOR|10.0.0.57" 'admin_status' 'up'
```

## 4.3. 查看 BGP 宣告网段
```shell
# vtysh -c 'show run' | grep network | cut -d \  -f4
vtysh -c 'show running bgpd' | grep network
```

## 4.4. 查看 bgp 指定邻居宣告路由
```shell
vtysh -c 'show bgp ipv4 neighbors 100.106.105.228 advertised-routes'
```

# 5. vtysh

## 5.1. 查看配置
```shell
# 查看 interface 信息
/usr/bin/vtysh -c 'show interface brief'

# 查看日志配置
/usr/bin/vtysh -c 'show rsyslog configuration'

# 查看 当前 BGP 运行配置
vtysh -c 'show running-config'
```

## 5.2. 通过 route-map 过滤路由
```shell
vtysh
configure terminal

# 创建拒收网段的 ip prefix-list
ip prefix-list V4_BGP_IN_FILTER_PFXLIST seq 1001 deny 3.1.1.1/32
ip prefix-list V4_BGP_IN_FILTER_PFXLIST seq 1002 deny 3.3.3.3/32
ip prefix-list V4_BGP_IN_FILTER_PFXLIST seq 9999 permit 0.0.0.0/0 le 32
# check
do show ip prefix-list V4_BGP_IN_FILTER_PFXLIST

# 创建拒收 v4 路由的 route-map 规则 （注：route-map 默认 Matching Policy 是 deny）
route-map V4_BGP_IN_FILTER_ROUTEMAP permit 5
    match ip address prefix-list V4_BGP_IN_FILTER_PFXLIST
    set community 5060:12345 additive
    # check
    do show route-map V4_BGP_IN_FILTER_ROUTEMAP

# 将 Route MAP 应用到所有 neighbor
router bgp 65000
    address-family ipv4 unicast
    neighbor 172.31.251.190 route-map V4_BGP_IN_FILTER_ROUTEMAP in
    neighbor 172.31.251.192 route-map V4_BGP_IN_FILTER_ROUTEMAP in
    exit-address-family

# check route filter
do show ip bgp neighbor 172.31.251.190 advertised-routes
```

## 5.3. 添加bgp peer
```shell
vtysh
configure terminal

# add prefix-list 注意区分 ip/ipv6
ipv6 prefix-list FROM_SW_V6 seq 10 permit any
ipv6 prefix-list TO_SW_V6 seq 10 permit any

# add BGP peer
router bgp 64512
neighbor fdbd:dc00:46::646a:b67c remote-as 64751
address-family ipv6
neighbor fdbd:dc00:46::646a:b67c prefix-list FROM_SW_V6 in
neighbor fdbd:dc00:46::646a:b67c prefix-list TO_SW_V6 out
neighbor fdbd:dc00:46::646a:b67c activate
# 多条链接时需指定最大链接数, server-2 (10.11.112.33)
neighbor fdbd:dc00:46::646a:b67c ebgp-multihop 3

# (opt) announce network 需在 v4 | v6 address-family 下
address-family ipv6
network fdbd:dcfd:0:999::3/128
address-family ipv4
network 192.168.1.2/32

# check
do show ip prefix-list
do show ipv6 prefix-list
do show bgp neighbors fdbd:dc00:46::646a:b67c
do show bgp summary
```

## 5.4. 宣告路由
```shell
vtysh
configure terminal
# 需：本机手工加待宣告 v4 网段的黑洞路由 （在 config 视图下操作）
ipv4 route-static 172.20.0.0/16 blackhole
ipv4 route-static 172.21.0.0/16 blackhole
# 需：本机手工加待宣告 v6 网段的黑洞路由 （在 config 视图下操作）
ipv6 route-static fd01::/64 blackhole
ipv6 route-static fd02::/64 blackhole

router bgp 65000
# 允许免检查宣告网段
no bgp network import-check

neighbor 172.31.252.71 peer-group A00T2_4
neighbor 172.31.252.75 peer-group A00T2_4
neighbor 172.31.252.79 peer-group A00T2_4
neighbor 172.31.252.83 peer-group A00T2_4
neighbor fdbd:dc00:46::ac1f:fc47 peer-group A00T2_6
neighbor fdbd:dc00:46::ac1f:fc4b peer-group A00T2_6
neighbor fdbd:dc00:46::ac1f:fc4f peer-group A00T2_6
neighbor fdbd:dc00:46::ac1f:fc53 peer-group A00T2_6

do show ip bgp peer-group A00T2_4
do show ip bgp peer-group A00T2_6

# 查看指定邻居 宣告路由
do show ip bgp neighbor 172.31.252.71 advertised-routes
# 查看指定邻居 收到路由
# 不支持 do show ip bgp neighbor 172.31.252.71 received-routes
# 宣告路由（注：network 只宣告本机路由表已有的网段，若没有则不会宣告）
# vtysh
# configure terminal
# address-family ipv4 unicast
# 本机 loopback1，已有路由表
network 10.8.104.254/32
network 172.20.0.0/16
network 172.21.0.0/16

network 3.10.0.1/32
network 3.10.0.14/32
network 10.32.125.114/32
# exit-address-family
# address-family ipv6 unicast
network fd03::1/128
network fd01::/64
network fd02::/64
# exit-address-family

# check 指定宣告路由情况
# lambda-cli
# configure terminal
do show ip bgp network 3.10.0.1/32
do show ip bgp network 3.10.0.14/32
do show ip bgp network 10.32.125.114/32
do show ip bgp network 10.8.104.254/32
do show ip bgp network 172.20.0.0/16
do show ip bgp network 172.21.0.0/16
do show ip bgp network fd03::1/128
do show ip bgp network fd01::/64
do show ip bgp network fd02::/64
end
```

## 5.5. 添加路由
```shell
vtysh
configure terminal
ip route 20.0.0.2 255.255.255.0 20.0.0.1
do show ip route
```

## 5.6. vrf 命令
```shell
# 查看 vrf 有哪些接口
show vrf vrf36012

# 查看 vrf bgp
vtysh -c 'show bgp vrf vrf36012 summary'

# 查看 bfd 信息
vtysh -c 'show bfd peers brief'
vtysh -c 'show bfd vrf vrf36012 peers brief'

# 查看所有 vrf 路由
vtysh -c 'show ip route vrf all json'
vtysh -c 'show ipv6 route vrf all json'

# 查看指定 vrf 邻居
vtysh -c 'show bgp vrf vrf36012 ipv4'
vtysh -c 'show bgp vrf vrf36012 ipv4 summary'
vtysh -c 'show bgp vrf vrf36012 ipv4 json'
vtysh -c 'show bgp vrf vrf36012 ipv6'
vtysh -c 'show bgp vrf vrf36012 ipv6 summary'
vtysh -c 'show bgp vrf vrf36012 ipv6 json'

# 查看指定 vrf 邻居简要信息
vtysh -c 'show bfd vrf vrf36012 peers brief'

# 查看指定 vrf 邻居接收到或宣告的路由信息
vtysh -c 'show bgp vrf vrf36012 neighbors 3001:100::1 received-routes'
vtysh -c 'show bgp vrf vrf36012 neighbors 3001:100::1 advertised-routes'
vtysh -c 'show bgp vrf vrf36012 neighbors 3001:100::1 received-routes json'
vtysh -c 'show bgp vrf vrf36012 neighbors 3001:100::1 advertised-routes json'

# 查看指定 vrf 路由
vtysh -c 'show bgp vrf vrf36012 ipv4 cidr-only wide'
vtysh -c 'show bgp vrf vrf36012 ipv4 cidr-only json'
vtysh -c 'show bgp vrf vrf36012 ipv4 json'
vtysh -c 'show bgp vrf vrf36012 ipv4'
vtysh -c 'show bgp vrf vrf36012 ipv6 cidr-only wide'
vtysh -c 'show bgp vrf vrf36012 ipv6 cidr-only json'
vtysh -c 'show bgp vrf vrf36012 ipv6 json'
vtysh -c 'show bgp vrf vrf36012 ipv6'

# 查看指定 evpn vni instance 信息
vtysh -c 'show evpn vni 36013'

# 查看 vrf arp 信息
vtysh -c 'show evpn arp-cache vni 36012'

# 查看指定 vrf 指定邻居  宣告路由
vtysh -c 'show bgp vrf vrf36012 neighbors 3001:100::1 advertised-routes json'

# 查看指定 vrf 指定邻居  收到路由
vtysh -c 'show bgp vrf vrf36012 neighbors 3001:100::1 received-routes json'

# 查看 bfd 简信
show bfd summary

# Vrf ping
timeout 1 ping -4 -I vrf36012 -c 3 -i 0.2 30.1.2.1
timeout 1 ping -6 -I vrf36012 -c 3 -i 0.2 3001:100::1
```

# 6. BMC
## 6.1. Accton 设备串口 切换 BMC/COME
> 串口服务器登录账号密码：admin\Admin123!@#

> 65x: 9600/8N1
> xlt: 115200/8N1

方法 1：CTRL + U 快捷键
```shell
# （将串口访问的）BMC 切 COME
按下 CTRL + U 后（1~2秒）松开，按数字 1，再按回车

# （将串口访问的）COME 切 BMC
按下 CTRL + U 后（1~2秒）松开，按数字 2，再按回车
```

方法 2：sol.sh
```shell
# （将串口访问的）BMC 切 COME
# 执行 sol.sh，按数字 1，回车
/usr/local/bin/sol.sh

# （将串口访问的）COME 切 BMC
长按 CTRL + X ; 或键入英文下的 ~. (若无反应再试一次就行)
```

注意: 若在 BMC sol.sh 进入 COME，则需按快捷键 ~. 回车重返 BMC，此时**CTRL + U 快捷键无法返回 BMC**

## 6.2. Accton 通过 usb0 口 SSH 访问 OpenBMC
```shell
ping -6 -c 3 fe80::ff:fe00:1%usb0

curl http://[fe80::ff:fe00:1%usb0]:8080/api/sys/bmc/tmp/mavericks

# 65X 获取 BMC 平台信息（通过 curl 从 BMC 获取信息）
curl http://[fe80::ff:fe00:1%usb0]:8080/api/sys/mb/fruid
curl http://[fe80::1%usb0]:8080/api/sys/mb/fruid

# ssh 访问（ root/0penBmc ）
ssh -6 root@fe80::ff:fe00:1%usb0
```

## 6.3. BMC IP 配置
以 Accton 设备为例
```shell
# 查看 BMC 版本
ipmitool mc info

# 查询 BMC IP
ipmitool lan print

# 配置 BMC 网络 IP
ipmitool lan set 1 ipaddr 10.32.124.155
ipmitool lan set 1 netmask 255.255.255.0
ipmitool lan set 1 defgw ipaddr 10.32.124.1
# ipmitool lan set 1 macaddr  fc:76:92:00:03:11
```

## 6.4. BMC 侧重启 COME 侧
```shell
config_power -d cpu -a cycle
```

## 6.5. BMC 侧重启 SONiC
```shell
wedge_power.sh reset;sol.sh

# Accton XLT
ipmitool power cycle
ipmitool power reset
```

# 7. vEOS
## 7.1. 进入 cli
```shell
/usr/bin/Cli
enable
```

## 7.2. 查看 BGP 信息
```shell
# 进入 vEOS cli
/usr/bin/Cli
enable
# 查看 BGP 简要信息
show ip bgp summary
show ipv6 bgp summary
# 查看特定 neighbor
show ip bgp neighbor 192.168.0.2
show ip bgp neighbor 10.0.0.40
show ip bgp neighbor 10.0.0.56
show ipv6 bgp neighbor fc00::51
show ip bgp neighbors
# 其他
show lacp neighbor

show bgp convergence
show bgp instance
show bgp labeled-unicast tunnel
show bgp statistics
show ip route bgp
show ipv6 route bgp
```

# 8. 编译
## 8.1. 手动创建 SONiC 编译容器
```shell
SONIC_DIR='/home/haoleeson/code/sonic'
SLAVE_IMAGE='sonic-slave-stretch-haoleeson:c883792fe60'

docker run -dit --name my-sonic-image-build-env --privileged \
    -v $SONIC_DIR:/sonic \
    -e "https_proxy=http://a.b.c.d:8118" \
    -e "http_proxy=http://a.b.c.d:8118" \
    -e no_proxy="10.20.30.40,10.20.30.40" \
    -w /sonic $SLAVE_IMAGE
```

## 8.2. 全量编译（博通）
```shell
cd /home/haoleeson/code/sonic
rm -rf target/
make init
make configure PLATFORM=broadcom
make target/baidu-sonic.bin
```

## 8.3. 全量编译（Barefoot）
```shell
cd /home/haoleeson/code/sonic
make init
make configure PLATFORM=barefoot
make target/sonic-barefoot.bin
```

## 8.4. P4 SDE9.3.2 编译
```shell
./p4studio_build.py -up switch_p416_profile_sai15 -sp x1_tofino
```

# 9. 排障
## 9.1. 查看基础信息
```shell
# 查看设备 SN 序列号
show version | grep 'Serial Number'  | awk '{ print $NF }'

# 查看 SONIC 版本信息
show version | grep 'Version'

# 查看设备类型
# - TD4：BT200H0,BT200R0
# - TH4:BS400H0,BS400R0
show version | grep 'HwSKU'
```

## 9.2. 查看平台硬件信息
### 9.2.1. 平台信息
```shell
# 查看平台简介信息
show platform summary

# 查看存储在 eeprom 上的信息
show platform syseeprom

# 查看电源状态
show platform psustatus

# 查看风扇状态
show platform fan

# 查看各平台设备温度
show platform temperature
```

### 9.2.2. 系统状态信息
```shell
show clock
show boot

# 显示系统硬件信息（CPU 电压&温度, 内存温度，风扇转速，电源电压&温度&功率&转速，出入口温度，交换芯片温度）
show environment

# 显示日志内容
show logging | more

# 显示传感器日志
show logging sensord
```

### 9.2.3. 查看 Tofino 芯片是否能被识别
```shell
# COME 端执行
lspci | egrep '1d1c|Tofino'
# 回显示例
# 05:00.0 Unassigned class [ff00]: Barefoot Networks, Inc. Tofino 1 (rev 10)
# 06:00.0 Unassigned class [ff00]: Barefoot Networks, Inc. Tofino 1 (rev 10)
# 06:00.0 Unassigned class [ff00]: Device 1d1c:0010 (rev 10)
```

### 9.2.4. 查看BIOS版本
```shell
# （sonic侧）查看设备  BIOS Version
sudo dmidecode -t bios | grep Ver | cut -d : -f 2
```

### 9.2.5. 查看 eeprom SN
```shell
# （sonic 侧）查看设备 SN
sudo decode-syseeprom -d | grep Serial | cut -c 31-
```

### 9.2.6. i2c设备
```shell
# i2c 路径，每个 i2c-x 对应一个 port
ls /dev/i2c-*

# 读取 i2c 硬件信息
i2cget -y -f 33 0x62 0x1
i2cget -y -f 33 0x62 0x2
i2cget -y -f 34 0x64 0x1
i2cget -y -f 34 0x64 0x2

# 读取 i2c 端口 17 信息
hexdump -C /sys/bus/i2c/devices/17-0050/sfp_eeprom

# 罗列检测到的 i2c 设备
i2cdetect -l | sort

# 检测 i2c 设备
i2cdetect -y 1
i2cdetect -r -y 1
i2cdump -y 1 0x44
ls -l /sys/bus/i2c/devices/i2c-*
```

### 9.2.7. i2c 定位指令
```shell
# 查看 i2c 设备
i2cdetect -l | sort

# 查看指定驱动 ast（开启会影响 公版 XLT 初始化，导致端口未 ready）
lsmod | grep -i ast

# 卸载 i2c 驱动
modprobe -r i2c_dev
modprobe -r ast

# 安装 i2c 驱动
modprobe i2c_dev

# 安装驱动方式 2
insmod /usr/lib/modules/4.19.0-12-2-amd64/extra/bf_kdrv.ko

# 重新扫描 pcie 硬件
echo 1 > /sys/bus/pci/rescan

# 查看 d message 信息
dmesg
# 清理 d message 信息
dmesg -C

# 卸载 i2c-33
echo 0x62 > /sys/bus/i2c/devices/i2c-33/delete_device

# 卸载 i2c-17
echo 0x50 > /sys/bus/i2c/devices/i2c-17/delete_device

# dump i2c 0x33 信息
i2cdetect -y 33

# dump 指定 i2c 信息
i2cget -y -f 33 0x62 0x2
i2cget -y -f 34 0x64 0x1

# 查找驱动
find / -name 'ast*.ko*' 2>&1 | fgrep -v 'find:'
```

## 9.3. 过滤 Err 日志
```shell
grep -i err syslog | fgrep -v liblogging | fgrep -v lldp | fgrep -v telemetry | fgrep -v snmp | fgrep -v ntpd | fgrep -v 'INFO kernel' | fgrep -v 'INFO containerd'

# sudo zgrep -aE ' ERR| Err| err| FAIL| Fail| fail|ABRT|Traceback' /var/log/syslog.x.gz
```

## 9.4. sonic-cfggen 常用命令
```shell
# 打印 configdb 数据库内容
sonic-cfggen -d
sonic-cfggen -d --print-data

sonic-cfggen -d -v 'BGP_NETWORK'
sonic-cfggen -d -v 'DEVICE_METADATA'
sonic-cfggen -d -v 'DEVICE_METADATA.localhost.hwsku'
sonic-cfggen -d -v 'DEVICE_METADATA.localhost.platform'

sonic-cfggen -d -v 'VERSIONS'
```

## 9.5. 服务容器启停的
不应通过docker命令直接停启SONiC中服务容器，而应通过 service 的方式
```shell
# 列出系统所有服务
systemctl list-units --all --type=service

# 停止 radv 容器（服务）
sudo service radv stop

# 启动 radv 容器（服务）
sudo service radv start
```

## 9.6. iic 死锁问题解决方法
1. 设备下电重启（因为 reboot 并非所有设备都下电）

2. 软件使用9clk来reset
```shell
1:拔掉所有光模块
# 在 bmc下执行
# enable one time generation of 9 clk
i2cset -y -f 12 0x31 0x42 0x02;
# delay to allow 9 clk cycles
usleep 10000;
# disable one time generation of 9 clk
i2cset -y -f 12 0x31 0x42 0x0;
# 使用 9clk reset cp2112
i2cset -y -f 12 0x31 0x39 0xfd ; usleep 10000; i2cset -y -f 12 0x31 0x39 0xff;

# BMC 侧 重启 COME 侧电源
wedge_power.sh reset
```

## 9.7. Accton交换机无法找到cdc_ethernet端口修复方法
```shell
# 1. 串口登录设备 bmc，或通过其他设备 bmc ssh 登录 bmc
记录此设备 bmc eth0 IPv6

# 2. 关闭 COME 侧电源
wedge_power.sh off
# check
wedge_power.sh status

# 3. (opt). 执行修复 iic 死锁问题
i2cset -y -f 12 0x31 0x42 0x02;
usleep 10000;
i2cset -y -f 12 0x31 0x42 0x0;
i2cset -y -f 12 0x31 0x39 0xfd ; usleep 10000; i2cset -y -f 12 0x31 0x39 0xff;

# 4. (opt). 在 bmc 侧执行，让 Tofino 芯片随设备一起 reset
i2cset -f -y 12 0x31 0x32 0xf

# 5. 等待 COME 侧 stop 10 min

# 6. 重启 BMC，尝试软件达到 "整机断电目的"
reboot
```

## 9.8. Accton tofino 驱动无法识别问题
在 BMC 侧执行以下指令，（无串口时可通过其他同网段 BMC ssh 到目标设备 BMC）
```shell
# 在 bmc 侧执行，让 Tofino 芯片随设备一起 reset
i2cset -f -y 12 0x31 0x32 0xf
# bmc 侧让 come 下电上电
wedge_power.sh off
wedge_power.sh on
# 风扇控制
# fand
```

## 9.9. Accton交换机查看BMC硬件信息
```shell
# 查看 BMC 版本
cat /etc/issue
# 查看 EEPROM 信息
weutil
# 查看传感器信息（电压、电流、功率、温度、风扇转速）
sensors
# 查看 12, 5, 3.3, 2.5, 1.8, 1.5, 1.2, 0.9 V 实际电压
btools.py --UCD sh v
# 查看光模块电压
btools.py --IR sh v
```

## 9.10. SONiC版本升级
```shell
sudo sonic_installer install -f sonic-barefoot-xxx.xxx.bin
sudo reboot
# sonic的默认用户名：root，密码：YourPaSsWoRd
```

## 9.11. 排查端口抖动
```shell
# - 查询指定时段 端口抖动日志
# （正常 DOWN 端口无此日志；config reload 也会产生，故需筛查在无 reload时段）
rm /tmp/start > /etc/null 2>&1; touch --date "2024-01-17 0:00:00" /tmp/start && \
    rm /tmp/end > /etc/null 2>&1; touch --date "2024-01-20 23:00:00" /tmp/end && \
    rm $HOME/port_flapping.log; cd /var/log/; \
    find -type f -name 'syslog*' -newer /tmp/start -not -newer /tmp/end -printf "%T@\t%p\n" | sort -n | cut -f 2- | xargs -t -I {} zgrep -E 'Bridge: port [[:digit:]]{1,2}\((Ethernet[[:digit:]]{1,2}|dummy)\) entered disabled state' {} >> $HOME/port_flapping.log; wc -l $HOME/port_flapping.log

# - 查询指定时段 端口 up_to_down 日志
rm /tmp/start > /etc/null 2>&1; touch --date "2024-01-17 0:00:00" /tmp/start && \
    rm /tmp/end > /etc/null 2>&1; touch --date "2024-01-20 23:00:00" /tmp/end && \
    rm $HOME/port_up_to_down.log; cd /var/log/; \
    find -type f -name 'syslog*' -newer /tmp/start -not -newer /tmp/end -printf "%T@\t%p\n" | sort -n | cut -f 2- | xargs -t -I {} zgrep -C 30 -E 'updatePortOperStatus: Port Ethernet[[:digit:]]{1,2} oper state set from up to down' {} >> $HOME/port_up_to_down.log; wc -l $HOME/port_up_to_down.log

# - 查询指定时段 手动操作端口 DOWN 日志
rm /tmp/start > /etc/null 2>&1; touch --date "2024-01-17 0:00:00" /tmp/start && \
    rm /tmp/end > /etc/null 2>&1; touch --date "2024-01-20 23:00:00" /tmp/end && \
    rm $HOME/set_port_down.log; cd /var/log/; \
    find -type f -name 'syslog*' -newer /tmp/start -not -newer /tmp/end -printf "%T@\t%p\n" | sort -n | cut -f 2- | xargs -t -I {} zgrep -E 'doTask: Configure Ethernet[[:digit:]]{1,2} admin status to down' {} >> $HOME/set_port_down.log; wc -l $HOME/set_port_down.log
```

## 9.12. 查看端口配置文件
```shell
# x86_64-accton_wedge100bf_65x-r0
cat /usr/share/sonic/device/x86_64-accton_wedge100bf_65x-r0/mavericks/port_config.ini
# XLT
cat /usr/share/sonic/device/x86_64-accton_csp7551-r0/Accton-CSP7551/port_config.ini
# 恒扬
cat /usr/share/sonic/device/x86_64-semptian_ps7350_32x-r0/SEMPTIAN-PS7350-32X/port_config.ini
```

## 9.13. 通过sonic-cfggen获取网关v6 IP
```shell
len=$(sonic-cfggen -d -v "MGMT_INTERFACE.values()" | grep -o gwaddr | wc -l)
v6gwip=''

for ((i=0; i<$len; i++)); do
  ip=$(sonic-cfggen -d -v "MGMT_INTERFACE.values()[$i].gwaddr" 2>&1) > /dev/null
  echo "ip:    $ip"
  if [[ $ip == *":"* ]]; then
    v6gwip=$ip
  fi
done

if [[ -n "$v6gwip" ]]; then
    echo "v6gwip:    $v6gwip"
fi
```

## 9.14. ONIE 查看系统 efi 启动顺序
```shell
# 查看顺序
efibootmgr

# 执行 efibootmgr 回显值：设备启动执行顺序
ONIE:/ # efibootmgr
BootCurrent: 0019
Timeout: 3 seconds
BootOrder: 0019,001A,0002,0010,0012,0013,0015,0016,0017,0000,0001
Boot0000  SONiC-OS
Boot0001  Hard Drive
Boot0002* UEFI: Built-in EFI Shell
Boot0010* UEFI: PXE IP4 Intel(R) I210 Gigabit  Backplane Connection
Boot0012* UEFI: PXE IP6 Intel(R) I210 Gigabit  Backplane Connection
Boot0013* UEFI: Network Card
Boot0015* UEFI: Network Card
Boot0016* UEFI: Network Card
Boot0017* UEFI: Network Card
Boot0019* ONIE: Open Network Install Environment
Boot001A* SONiC-OS
MirroredPercentageAbove4G: 0.00
MirrorMemoryBelow4GB: false
ONIE:/ #

ONIE:/var/log # efibootmgr
BootCurrent: 0019
Timeout: 3 seconds
BootOrder: 0019,001A,0002,0010,0012,0013,0015,0016,0017,0000,0001
Boot0000  SONiC-OS
Boot0001  Hard Drive
Boot0002* UEFI: Built-in EFI Shell
Boot0010* UEFI: PXE IP4 Intel(R) I210 Gigabit  Backplane Connection
Boot0012* UEFI: PXE IP6 Intel(R) I210 Gigabit  Backplane Connection
Boot0013* UEFI: Network Card
Boot0015* UEFI: Network Card
Boot0016* UEFI: Network Card
Boot0017* UEFI: Network Card
Boot0019* ONIE: Open Network Install Environment
Boot001A* SONiC-OS
MirroredPercentageAbove4G: 0.00
MirrorMemoryBelow4GB: false
ONIE:/var/log #

# 更改启动顺序（BootOrder: 后的值）
efibootmgr -o 001A,0019,0002,0010,0012,0013,0015,0016,0017,0000,0001

```

## 9.15. gdb调试coredump文件
```shell
# 拷贝解压后的 core 到 HOST 的 ~/core_files/
# 解压 gz（保留源文件）
# gunzip -c x.core.gz > x.core

# To debug a core file in non-SONiC environment that supports docker
docker load -i docker-<name>-dbg.gz
docker load -i docker-orchagent-dbg.gz
docker load -i docker-syncd-bfn-dbg.gz

docker tag f3e7100d47f1 docker-syncd-bfn-dbg__65x_release_20230110:sde932

# copy your unzipped core file into ~/core_files
# CONTAINER_NAME='orchagent_dbg__xlt'
# IMAGE_NAME='docker-orchagent-dbg__xlt_20221104:sde990'
# CONTAINER_NAME='syncd_dbg__xlt'
# IMAGE_NAME='docker-syncd-bfn-dbg__xlt_20221104:sde990'
# CONTAINER_NAME='orchagent_dbg__65x'
# IMAGE_NAME='docker-orchagent-dbg__65x_release_20230110:sde932'
# CONTAINER_NAME='syncd_dbg__65x__230110'
# IMAGE_NAME='docker-syncd-bfn-dbg__65x_release_20230110:sde932'

CONTAINER_NAME='syncd_dbg__65x__230110_ugw_r'
IMAGE_NAME='docker-syncd-bfn-dbg__65x_release_20230110:sde932'

CONTAINER_NAME='syncd_dbg__65x__230110_try_ugw_r'
IMAGE_NAME='docker-syncd-bfn-dbg__65x_release_20230110:sde932_try_ugw_r'

# CONTAINER_NAME='bgp_dbg__65x'
# IMAGE_NAME='docker-bgp-dbg__65x_release_20230110:sde932'

docker run -dit --name $CONTAINER_NAME --entrypoint=/bin/bash -v ~/core_files:/core_files -w /core_files/ $IMAGE_NAME
docker exec -it $CONTAINER_NAME bash

# 在容器中安装 libc6 调试库（带符号表）
apt-get install -y --force-yes libc6-dev libc6-dbg libthread_db

apt-cache search glibc | grep -i dbg

# 安装 libstdc++ 调试符号表
apt-cache search libstdc++ | grep -i dbg
apt-get install -y --force-yes libstdc++6-6-dbg
apt-get install -y --force-yes libstdc++6-7-dbg
apt-get install -y --force-yes libstdc++6-8-dbg

exit
docker stop $CONTAINER_NAME

# core_files
gdb -q /usr/bin/<your binary> -c /core_files/<your core>
gdb -q /usr/bin/orchagent -c /core_files/orchagent.1667560417.35.core
gdb -q /usr/bin/syncd -c /core_files/syncd.1667749314.25.core

# 查看 堆栈信息
bt

# 查找出现Crash的最后一个函数
f 0

## 查看此函数入参
info args

## 查看函数局部变量
info locals

# 检查有哪些链接库缺失符号表
info sharedlibrary

# 查看哪些库未加载
i sharelibrary

# 调试正在运行的程序
gdb attach pid
```

常用调试命令：
```shell
# 进入 GDB 调试
gdb ${二进制执行文件} ${.core 文件}

# 设置入参
set args "argv1" "argv2"
set args "-p"

# 查看 堆栈信息
BT

# 设置断点
break func 或 line
# 查看断点信息
break info

# 运行程序（到断点处暂停）
r  (-- run )
# 单条语句执行
n  (-- next )
# 继续运行程序
c  (-- continue )
# 打印变量 i 的值
p i  (--  print )
```

多线程调试：
> [循环调试命令](https://www.csdn.net/tags/MtjaEgzsNzg0MTItYmxvZwO0O0OO0O0O.html)

```shell
# (1).方法一:
# gdb --batch -ex "thread apply all bt" -p <被分析的进程的pid>  将这条命令的打印dump出来
# --batch: 执行批处理，不进入交互模式
# --ex: 执行gdb 命令
# "thread apply all bt full": 打印所有线程堆栈
gdb --batch -ex "thread apply all bt" -p <被分析的进程的pid>  将这条命令的打印dump出来

# (2).方法二:
# gdb -q --batch --ex "set height 0" -ex "thread apply all bt full" [可执行文件] [core文件]
# -q: 不打印gdb的版权消息
# --batch: 执行批处理，不进入交互模式
# --ex: 执行gdb 命令
# "set height 0": 不对输出进行分页
# "thread apply all bt full": 打印所有线程堆栈
gdb -q --batch --ex "set height 0" -ex "thread apply all bt full" /usr/bin/orchagent /core_files/orchagent.1667560417.35.core
```

## 9.16. Logrotate
每十分钟周期检测，超过其文件阈值的才会压缩，一般不会：
```shell
cat /etc/cron.d/logrotate
*/10 * * * * root /usr/bin/pkill -9 logrotate > /dev/null 2>&1; /usr/sbin/logrotate /etc/logrotate.conf > /dev/null 2>&1
```

强制压缩轮转命令
```shell
sudo /usr/sbin/logrotate -f /etc/logrotate.d/rsyslog
```

轮转某目录下多个文件（通配符）
> 需先手动创建 /var/log/news/old

新建配置文件：/etc/logrotate.d/multiple

```shell
/var/log/news/ABC-*.log {
    size 100K
    rotate 10
    olddir /var/log/news/old
    missingok
    notifempty
    compress
    sharedscripts
    postrotate
        /bin/kill -HUP $(cat /var/run/rsyslogd.pid)
    endscript
}
```

测试 OK：
```shell
# 强制轮转
/usr/sbin/logrotate -vf /etc/logrotate.d/multiple

# 定时任务调起也正常
```

## 9.17. 系统内存超出 OOM 解决方法
无法执行任何命令时
```shell
# 手动触发OOM Killer
sudo su root
# 启用 SysRq 所有功能
echo 1 > /proc/sys/kernel/sysrq
# 调用 oom Killer 来杀死占用内存的进程
echo f > /proc/sysrq-trigger
# | b | 将立即重新启动系统，而不同步或卸载磁盘。 |
# | c | 如果配置，将执行系统崩溃并进行故障转储。 |
# | d | 显示所有持有的锁。 |
# | e | 向除 init 之外的所有进程发送 SIGTERM。 |
# | f | 将调用 oom Killer 来杀死占用内存的进程，但如果无法杀死任何进程，请不要惊慌。 |
# | g | 由 kgdb（内核调试器）使用 |
# | h | 将显示帮助（实际上，除了此处列出的键之外的任何其他键都将显示帮助。但h很容易记住:-) |
# | i | 向除 init 之外的所有进程发送 SIGKILL。 |
# | j | 强制“解冻”- 文件系统被 FIFREEZE ioctl 冻结。 |
# | k | 安全访问密钥 (SAK) 终止当前虚拟控制台上的所有程序。注意：请参阅下面 SAK 部分的重要注释。 |
# | l | 显示所有活动 CPU 的堆栈回溯。 |
# | m | 将当前内存信息转储到您的控制台。 |
# | n | 用于使 RT 任务变得更好 |
# | o | 将关闭您的系统（如果已配置并支持）。 |
# | p | 将当前寄存器和标志转储到您的控制台。 |
# | q | 将转储所有武装 hrtimers 的每个 CPU 列表（但不是常规的 timer_list 计时器）以及有关所有 Clockevent 设备的详细信息。 |
# | r | 关闭键盘原始模式并将其设置为 XLATE。 |
# | s | 将尝试同步所有已安装的文件系统。 |
# | t | 将当前任务列表及其信息转储到您的控制台。 |
# | u | 将尝试以只读方式重新挂载所有已挂载的文件系统。 |
# | v | 强制恢复帧缓冲区控制台 |
# | v | 导致 ETM 缓冲区转储 [ARM 特定] |
# | w | 转储处于不可中断（阻塞）状态的任务。 |
# | x | 由 ppc/powerpc 平台上的 xmon 接口使用。显示 sparc64 上的全局 PMU 寄存器。转储 MIPS 上的所有 TLB 条目。 |
# | y | 显示全局 CPU 寄存器 [SPARC-64 特定] |
# | z | 转储 ftrace 缓冲区 |
# | 0-9 | 设置控制台日志级别，控制将哪些内核消息打印到控制台。（0，例如，只有紧急消息（例如 PANICs 或 OOPSes）才会发送到您的控制台。） |

# 或（下方触发oom Killer命令可能无内存 fork 执行）
sudo sysctl -w vm.oom_kill_allocating_task=1

# 禁用 SysRq 所有功能
echo 0 > /proc/sys/kernel/sysrq

# 重启设备
/sbin/reboot -f > /dev/null 2>&1 &

# 检查
sudo apt install htop
sudo htop
click F6 to sort and select PERCENT_MEM -> Enter
Select the programs that you do not need but are eating most of the memory ( up and down arrow can be used)
F9 and SIGKILL
```

## 9.18. vEOS 版本
[官网](https://www.arista.com)
[EOS Command-Line Interface (CLI) - Arista](https://www.arista.com/en/um-eos/eos-command-line-interface-cli#xx1097818)

镜像：

ls -l /home/sonic/veos-vm/images/
-rw-r--r-- 1 sonic sonic   5242880 Nov  9  2020 Aboot-veos-serial-8.0.0.iso
-rw-r--r-- 1 sonic sonic 662503424 Nov  9  2020 vEOS-lab-4.20.15M.vmdk

## 9.19. vEOS 配置 BGP
[官方 cli 命令](https://www.arista.com/en/um-eos/eos-border-gateway-protocol-bgp#xx1115278)
```shell
/usr/bin/Cli
ebable
switchA(config)# router bgp 100
switchA(config-router-bgp)# neighbor 10.100.100.2 remote-as 100
switchA(config-router-bgp)# network 10.10.1.0/24
switchA(config-router-bgp)# network 10.10.2.0/24
# switchA(config-router-bgp)# neighbor 10.100.100.2 export-localpref 150
switchA(config-router-bgp)# timer bgp 30 90
```

## 9.20. 启动加载文件
```shell
cat /mnt/flash/boot-config

# 对应 ansible/roles/eos/files/boot-config
```

# 10. 其他
## 10.1. 配置 Loopback IP
- 方法 1： 手动配置
```shell
# check
ip addr show Loopback1

sudo config interface ip add Loopback1 10.8.104.20/32
sudo config interface ip add loopback1 10.249.133.226/32
sudo config interface ip add Loopback1 FC00:1::20/128
# sudo config interface ip add Loopback1 fdbd:51cd::0a45:ffff/128
sudo config interface ip add Loopback2 173.173.173.173/32
```

- 方法 2：在 config_db.json 中配置
```json
"LOOPBACK_INTERFACE": {
    "Loopback0": {},
    "Loopback1": {},
    "Loopback0|10.1.0.32/32": {},
    "Loopback0|FC00:1::32/128": {},
    "Loopback1|10.8.104.21/32": {}
},
```

## 10.2. 更改 Hostname
- 方法 1：命令行修改
```shell
config hostname sonic-DUT1
config save
# 检查
grep 'hostname' /etc/sonic/config_db.json
# 重启生效
```

- 方法 2：直接修改配置文件 /etc/sonic/config_db.json
```shell
"DEVICE_METADATA": {
        "localhost": {
            "bgp_asn": "65001",
            "cloudtype": null,
            "deployment_id": "1",
            "docker_routing_config_mode": "separated",
            "hostname": "sonic-DUT1",
            "hwsku": "mavericks",
            "platform": "x86_64-accton_xxx",
            "mac": "11:22:33:44:55:66",
            "region": null,
            "type": "ToRRouter",
            "default_bgp_status": "up",
            "default_pfcwd_status": "disable"
        }
    },
```

- 方法 3：linux 方式修改
```shell
# 切换至 root
su - root

TARGET_HOSTNAME='n11-119-079'

# 修改 hostname
sudo hostnamectl set-hostname $TARGET_HOSTNAME

# 修改 /etc/hosts
sudo vi /etc/hosts
sed -i "s/127.0.0.1 $HOSTNAME/127.0.0.1 $TARGET_HOSTNAME/g" /etc/hosts

# 修改 /etc/hostname
sudo vi /etc/hostname
sed -i "s/$HOSTNAME/$TARGET_HOSTNAME/g" /etc/hostname

tail /etc/hostname /etc/hosts

# 生效
/etc/init.d/hostname.sh start
# 或
invoke-rc.d hostname.sh start

# 备注：临时修改 HOSTNAME
hostname $TARGET_HOSTNAME
```

##  10.3. 通过 redis key 宣告/撤销路由
```shell
# 判断 redis 表项是否存在（已存在则无需添加）
redis-cli -h 127.0.0.1 -n 4 -p 6379 exists "BGP_NETWORK|192.168.0.90/32"
# 宣告路由
redis-cli -h 127.0.0.1 -n 4 -p 6379 hset "BGP_NETWORK|192.168.0.90/32" "NULL" "NULL"

# 撤销路由
redis-cli -h 127.0.0.1 -n 4 -p 6379 del "BGP_NETWORK|192.168.0.90/32"
```

## 10.4. 查看 config_db.json 中配置的 BGP_NETWORK
```shell
sonic-cfggen -d -v 'BGP_NETWORK' | grep -oP "u'[0-9a-f\.:]+/[0-9]+" |cut -d \' -f2
```

## 10.5. 安装 thrift 0.13.0 命令
```shell
# 安装依赖
sudo apt-get install libboost-dev libboost-test-dev libboost-program-options-dev libboost-filesystem-dev libboost-thread-dev libevent-dev automake make libtool git flex bison pkg-config g++ libssl-dev

wget http://archive.apache.org/dist/thrift/0.13.0/thrift-0.13.0.tar.gz
tar -xzvf thrift-0.13.0.tar.gz
cd thrift-0.13.0
./bootstrap.sh
./configure --with-cpp=yes --with-c_glib=no --with-java=no --with-ruby=no --with-erlang=no --with-go=no --with-nodejs=no
make -j2 && sudo make install
cd lib/py
sudo python setup.py install
cd ../../..
thrift --version
```

## 10.6. mgmt-topo 相关 brctl 指令
```shell
brctl show
```

## 10.7. mgmt-topo 相关 Open vSwitch 指令
```shell
# 创建 ovs Bridge
ovs-vsctl --may-exist add-br <bridge_name>

# 配置 mtu
ifconfig <bridge_name> mtu <mtu_val>

# 启动
ifconfig <bridge_name> up

# 删除 ovs Bridge
ovs-vsctl --if-exists del-br <bridge_name>

# 查看 bridge 的 VLAN
ovs-vsctl br-to-vlan <bridge_name>
ovs-vsctl br-to-vlan br-VM0501-0

# 查看 bridge 的 parent
ovs-vsctl br-to-parent <bridge_name>
ovs-vsctl br-to-parent br-VM0501-0

# 查看 bridge 端口列表（e.g. br-VM0501-0）
# ovs-vsctl list-ports <bridge_name>
ovs-vsctl list-ports br-VM0501-0

# 查看 port 所属的 bridge
# ovs-vsctl port-to-br <port_name>
ovs-vsctl port-to-br VM0501-t0

# 查看
ovs-vsctl show
# 添加 ovs 端口绑定
ovs-vsctl add-port <bridge_name> <port_name>
ovs-vsctl add-port br-VM0501-0 VM0501-t0
# 解除 ovs 端口绑定
ovs-vsctl del-port <bridge_name> <port_name>
ovs-vsctl del-port br-VM0501-0 VM0501-t0

ovs-vsctl del-port br-VM0502-0 VM0502-t0
ovs-vsctl add-port br-VM0501-0 VM0502-t0

# 查看 open flow 规则
ovs-ofctl dump-flows br-VM0501-0
ovs-ofctl dump-flows br-VM0502-0
# 添加 open flow 规则
ovs-ofctl add-flow <bridge_name> table=0,in_port=<vm_iface>,action=output:<out_iface>

# 删除 open flow 规则
ovs-ofctl del-flows <bridge_name>

ovs-vsctl show | grep -A 10 'Bridge "br-VM0501-0"'

```

## 10.8. mgmt 调大 fanout 侧对 lldp、lacp 协议的上报限速值
> fanout交换机是通过bpdu tunnel把lldp、lacp报文上送CPU做的软转发，上送报文默认限速是600pps，所以mgmt测试流量上不来。
```shell
# 创建流分类器
traffic classifier lldp operator and
  if-match control-plane protocol lldp
# 创建流行为
traffic behavior lldp
  car cir pps 2000 cbs 125440 ebs 0 green pass red discard yellow pass
# 创建流策略，并绑定流分类器和流行为
qos policy lldp
  classifier lldp behavior lldp
# 绑定流策略
control-plane slot 1
  qos apply policy lldp inbound
```

## 10.9. sonic-mgmt VM 互通 配置
```shell
# 为网卡增加 VLAN interface
ip link add link ma1 name x777 type vlan id 777
ip link set x777 up

# 配置 IP（vlan777）：设备 1
ip addr add 17.0.0.1/24 dev x777
## 配置 IP（vlan777）：设备 2
# ip addr add 17.0.0.2/24 dev x777

# 撤销 IP（vlan 777）：设备 1
ip addr del 17.0.0.1/24 dev x777
## 撤销 IP（vlan 777）：设备 2
# ip addr del 17.0.0.2/24 dev x777

# 删除 vlan interface
ip link set x777 down
ip link del x777
```