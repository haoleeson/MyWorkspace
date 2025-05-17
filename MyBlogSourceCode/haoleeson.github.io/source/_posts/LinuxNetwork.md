layout: post
title: Linux Network
date: 2025/3/10 16:33:45
updated: 2025/3/10 16:33:45
comments: true
tags:
- Network
- Linux
categories:
- 技术

---

本文记录一些工作中常用的Linux网络配置、排障、测试相关工具和指令。

<!-- more -->

# 1. 设置
## 1.1. 创建 veth 设备对
```shell
# 创建设备对 veth0 和 veth1
ip link add name veth0 type veth peer name veth1
# check
ip link show veth0
ip link show veth1

# set mtu
ip link set mtu 9000 veth0 up
ip link set mtu 9000 veth1 up

# 添加一个 veth 口到指定容器中
container_pid=$(sudo docker inspect --format='{{.State.Pid}}' manager_container1)
# ip link set netns ${container_pid} dev vethx && ip netns exec ${container_pid} ip link set name eth1 dev vethy
ip link set netns ${container_pid} dev veth${y} && docker exec -i $container_name ip link set name eth1 dev veth${y}

# 创建 veth 设备对，加入 container
/Users/admin/code/myShell/create_veth_into_container.sh
```

## 1.2. 创建 Vxlan Tunnel
从指定 eth 网口创建

```shell
# PS： 添加 IP
sudo ip addr add 10.1.1.1/31 dev eth4
sudo ip addr del 10.20.30.40/31 dev eth4

ip link add <vxlan_name> type vxlan id <vni> dstport 4789 remote <dst_vtep> local <src_vtep> dev <interface_name>
ip link add vxlan12345 type vxlan id 12345 dstport 4789 remote 10.20.30.40 local 192.168.1.2 dev eth4
ip link add vxlan3511 type vxlan id 3511 dstport 4789 remote 10.1.1.2 local 10.1.1.1 dev eth4

# ignore_checksum (vxlan 外层 udp checksum 为 0 时不会被 Linux 协议栈丢弃)
ip link add <vxlan_name> type vxlan id <vni> udp6zerocsumrx dstport 4789 remote <dst_vtep> local <src_vtep> dev <interface_name>
ip link add vxlan12345 type vxlan id 12345 udp6zerocsumrx dstport 4789 remote 10.20.30.40 local 192.168.1.2 dev eth4

# check
ip link | grep vxlan
ip -d link show <vxlan_name>
ip -d link show vxlan12345
ip -d link show vxlan700
ip -d link show vxlan701
ip -d link show vxlan3511
ip -d link show vxlan500

# PS: delete a vxlan
sudo ip link delete vxlan700
sudo ip link delete vxlan701
sudo ip link delete vxlan3511
```

## 1.3. 添加/删除 虚拟网卡
```shell
# 创建
sudo ifconfig eth0:0 192.168.1.63 up

# 删除
sudo ifconfig eth0:0 down
```

## 1.4. 添加删除网桥
```shell
# 添加网桥 br1
brctl addbr br1
ifconfig br1 10.250.0.1/24
ifconfig br1 inet6 add fec0::1/64
ifconfig br1 up
brctl show br1
ifconfig br1

# 删除网桥 br1
brctl show br1
ifconfig br1 down
brctl delbr br1
```

## 1.5. 修改网卡 MAC 地址
```shell
# ip a s eth1
# ping -I eth1 -c 10 172.16.1.1
ifconfig eth1 down
# ifconfig eth1 hw ether 00:04:00:04:04:04
ifconfig eth1 hw ether 00:03:00:03:03:03
# ifconfig eth1 hw ether 00:56:00:56:56:56
ifconfig eth1 up
ip a s eth1
```

## 1.6. 配置网卡 flow-hash 参数
```shell
ethtool -N eth5 rx-flow-hash udp4 sd
ethtool -N eth5 rx-flow-hash tcp4 sd
ethtool -N eth5 rx-flow-hash udp4 sdfn
ethtool -N eth5 rx-flow-hash tcp4 sdfn
```

## 1.7. 配置网卡 offload 参数
```shell
ethtool -K eth0 rx-checksum on|off
ethtool -K eth0 tx-checksum-ip-generic on|off
ethtool -K eth0 tso on|off
ethtool -K eth0 ufo on | off
ethtool -K eth0 gso on | off
ethtool -K eth0 ntuple on | off
```

## 1.8. 重启网卡
> 静态 IP 配置文件 /etc/network/interfaces
```shell
# a. 重启网络：
sudo /etc/init.d/networking restart
# 或
sudo service networking restart
# b. 重启网卡（eg. eth0）：
sudo ifdown eth0
# 或
sudo ifup eth0
```

## 1.9. 手动 DHCP 申请分配 IP
```shell
/sbin/dhclient eth0
```

## 1.10. 手动更新租约
```shell
/sbin/ifconfig /renew
/sbin/ifconfig /release
```

## 1.11. 创建网络命名空间（network namespaces）
```shell
# 查看当前网络命名空间
sudo ip netns list

# 新建网络命名空间
sudo ip netns add defaultns
sudo ip netns add eth4ns
sudo ip netns add eth5ns

# 在网络命名空间中创建虚拟网络空间，并绑定实际网卡
# ip link add link <real_interface> <virtual_interface> netns <namespace> type ipvlan mode l2
sudo ip link add link eth4 eth4_vns netns eth4ns type ipvlan mode l2
sudo ip link add link eth5 eth5_vns netns eth5ns type ipvlan mode l2

# 配置虚拟网络空间
## 开启虚拟网络空间
sudo ip -n eth4ns link set lo up
sudo ip -n eth4ns link set eth4_vns up
sudo ip -n eth5ns link set lo up
sudo ip -n eth5ns link set eth5_vns up

## 配置 IP 和 Route
sudo ip -n eth4ns addr add 10.0.0.2/24 dev eth4_vns
sudo ip -n eth4ns route add default via 10.0.0.1 dev eth4_vns
sudo ip netns exec eth4ns ip route add 20.0.0.5 via 10.0.0.5
sudo ip -n eth5ns addr add 20.0.0.2/24 dev eth5_vns
sudo ip -n eth5ns route add default via 20.0.0.1 dev eth5_vns
sudo ip netns exec eth5ns ip route add 10.0.0.5 via 20.0.0.5

# 命名空间执行命令
sudo ip netns exec eth4ns ip route list
sudo ip netns exec eth5ns ip route list

sudo ip netns exec eth4ns ping 10.0.0.5
sudo ip netns exec eth4ns ping 20.0.0.5

sudo ip netns exec eth5ns ping 20.0.0.5
sudo ip netns exec eth5ns ping 10.0.0.5

# 删除网络命名空间
sudo ip netns delete eth4ns
sudo ip netns delete eth5ns
```

## 1.12. 防火墙配置
```shell
# 查看入方向规则
sudo iptables -nvL INPUT
# 查看出方向规则
sudo iptables -nvL OUTPUT
```
### 1.12.1. 删除指定规则
```shell
sudo iptables -L --line-numbers
# e.g. 删除 INPUT 表中的第 3 条规则
sudo iptables -D INPUT 3
```

### 1.12.2. 查看 POSTROUTING 规则
```shell
iptables -t nat -v -L POSTROUTING -n --line-number
iptables -t nat -D POSTROUTING num
```
### 1.12.3. 查看 PREROUTING 规则
```shell
iptables -t nat -v -L PREROUTING -n --line-number
iptables -t nat -D PREROUTING num
```

### 1.12.4. 添加 DNAT 规则
- IPv4
```shell
# 设置变量
TESTBED_SERVER_IP='10.201.40.80'
DUT_IP='10.32.124.119'

# SNAT 规则：更改发往 dut 报文的源地址
sudo iptables -t nat -A POSTROUTING -s 10.250.0.0/24 -o eth0 -j SNAT --to-source $TESTBED_SERVER_IP
# DNAT 规则：更改来自 dut 报文的目的地址 为 ptf container ip（10.250.0.100）
sudo iptables -t nat -A PREROUTING -s $DUT_IP -j DNAT --to-destination 10.250.0.100
```

- IPv6
```shell
# SNAT 规则：更改 BMC 发往 ntp 服务器的报文的源地址
sudo ip6tables -t nat -A POSTROUTING -s fe80::ff:fe00:1 -o eth0 -j SNAT --to-source fc00:2::fc41
# check
sudo ip6tables -t nat -v -L POSTROUTING -n --line-number

# ~~DNAT 规则：更改 ntp 服务器发往 BMC 报文的目的地址~~
sudo ip6tables -t nat -A PREROUTING -s fdbd:dc00::10:8:8:12 -j DNAT --to-destination fe80::ff:fe00:1
# check
sudo ip6tables -t nat -v -L PREROUTING -n --line-number
```

备注：删除规则
- IPv4
```shell
# 删除 SNAT 规则（查看规则编号，删除指定编号规则）
sudo iptables -t nat -v -L POSTROUTING -n --line-number
sudo iptables -t nat -D POSTROUTING <num>

# 删除 DNAT 规则（查看规则编号，删除指定编号规则）
sudo iptables -t nat -v -L PREROUTING -n --line-number
sudo iptables -t nat -D PREROUTING <num>
```
- IPv6
```shell
# 删除 SNAT 规则（查看规则编号，删除指定编号规则）
sudo ip6tables -t nat -v -L POSTROUTING -n --line-number
sudo ip6tables -t nat -D POSTROUTING <num>

# 删除 DNAT 规则（查看规则编号，删除指定编号规则）
sudo ip6tables -t nat -v -L PREROUTING -n --line-number
sudo ip6tables -t nat -D PREROUTING <num>
```

### 1.12.5. 防火墙丢弃指定目的 mac 的包
```shell
# 增加防火墙配置，丢弃发往目的 mac 的包（接收端执行，创造断链）
sudo iptables -t filter -I OUTPUT -d 10.167.204.111 -j DROP

# 撤销上一规则（撤销所有：iptables -F）
sudo iptables -t filter -D OUTPUT -d 10.167.204.111 -j DROP
```

### 1.12.6. 防火墙添加 TCP、UDP 514 端口
```shell
# 防火墙添加 TCP 514 端口
sudo iptables -A INPUT -p tcp --dport 514 -j ACCEPT
# del
sudo iptables -D INPUT -p tcp --dport 514 -j ACCEPT

# 防火墙添加 UDP 514 端口
sudo iptables -A INPUT -p udp --dport 514 -j ACCEPT
# del
sudo iptables -D INPUT -p udp --dport 514 -j ACCEPT

# 保存（重启后失效）
sudo iptables-save
```

### 1.12.7. 添加 支持接收 VxLAN udp 报文规则
```shell
# 重加
sudo iptables -D OUTPUT -p all --source 0.0.0.0/0 --destination 0.0.0.0/0 -j ELKEID_OUTPUT
sudo iptables -A OUTPUT -p all --source 0.0.0.0/0 --destination 0.0.0.0/0 -j ELKEID_OUTPUT

# 发送方
sudo iptables -A OUTPUT -p all --source 10.11.115.104 --destination 10.11.119.78 -j ACCEPT
sudo iptables -L -n --line-number | grep -A 10 'Chain OUTPUT'

# 接收方
sudo iptables -A INPUT -p all --source 10.11.115.104 --destination 10.11.119.78 -j ACCEPT
sudo iptables -A INPUT -p all --source 10.11.113.140 --destination 10.11.119.78 -j ACCEPT
sudo iptables -A INPUT -p all --source 10.11.113.28 --destination 10.11.114.34 -j ACCEPT
sudo iptables -L -n --line-number | grep -A 30  'Chain INPUT'
```

### 1.12.8. 防火墙 CentOs 开启端口
```shell
# 查看防火墙状态
sudo systemctl status firewalld

# 查看指定端口状态
sudo firewall-cmd --zone=public --query-port=30001/tcp

# 查看所有已开放端口
sudo firewall-cmd --list-all

# 查看已开放端口
netstat -tlpn

# 开放指定端口（永久生效）
sudo firewall-cmd --zone=public --add-port=30001/tcp --permanent

# 关闭指定端口（永久生效）
sudo firewall-cmd --zone=public --remove-port=30001/tcp --permanent

# 重载防火墙以生效
sudo firewall-cmd --reload
```

### 1.12.9. 备份防火墙配置到文件
```shell
sudo iptables-save > backup_file
```

## 1.13. 证书
### 1.13.1. 生成证书
```shell
# 1. 生成证书授权CA的证书和 key
## Generate a private key for the CA
openssl genrsa 2048 > ca-key.pem
## Generate the X509 certificate for the CA
openssl req -new -x509 -nodes -days 365000 -key ca-key.pem -out ca-cert.pem
### 填值 Country Name (2 letter code) [AU]:CN
### 填值 State or Province Name (full name) [Some-State]:.

# 2. 生成服务端证书和 key
## Generate the private key and certificate request
openssl req -newkey rsa:2048 -nodes -days 365000 -keyout server-key.pem -out server-req.pem
### 填值 Country Name (2 letter code) [AU]:CN
### 填值 State or Province Name (full name) [Some-State]:.
## Generate the X509 certificate for the server
openssl x509 -req -days 365000 -set_serial 01 -in server-req.pem -out server-cert.pem -CA ca-cert.pem -CAkey ca-key.pem

# 3. 生成客户端证书和 key
## Generate the private key and certificate request
openssl req -newkey rsa:2048 -nodes -days 365000 -keyout client-key.pem -out client-req.pem
### 填值 Country Name (2 letter code) [AU]:CN
### 填值 State or Province Name (full name) [Some-State]:.
## Generate the X509 certificate for the client
openssl x509 -req -days 365000 -set_serial 01 -in client-req.pem -out client-cert.pem -CA ca-cert.pem -CAkey ca-key.pem

# 4. 校验证书文件
## Verify the server certificate
openssl verify -CAfile ca-cert.pem ca-cert.pem server-cert.pem
openssl verify -CAfile ca-cert.pem commonserver-cert.pem commonserver-key.pem
openssl verify -CAfile /etc/routesyncd/routesyncd_test/certskeys/ca-cert.pem /etc/routesyncd/routesyncd_test/certskeys/server-cert.pem /etc/routesyncd/routesyncd_test/certskeys/server-key.pem
## Verify the client certificate
openssl verify -CAfile ca-cert.pem ca-cert.pem client-cert.pem
openssl verify -CAfile ca-cert.pem client-cert.pem client-key.pem
openssl verify -CAfile /etc/routesyncd/routesyncd_test/certskeys/ca-cert.pem /etc/routesyncd/routesyncd_test/certskeys/client-cert.pem /etc/routesyncd/routesyncd_test/certskeys/client-key.pem
```

### 1.13.2. 查看证书信息
```shell
# 查看 证书文件
# openssl x509 -text -noout -in /path/to/yourcertificate.pem
openssl x509 -text -noout -in /etc/routesyncd/routesyncd_test/certskeys/ca-cert.pem
openssl x509 -text -noout -in /etc/routesyncd/routesyncd_test/certskeys/server-cert.pem
openssl x509 -text -noout -in /etc/routesyncd/routesyncd_test/certskeys/client-cert.pem

openssl x509 -text -noout -in /etc/routesyncd/gobgpcert/ca-cert.pem
openssl x509 -text -noout -in /etc/routesyncd/gobgpcert/commonserver-cert.pem
openssl x509 -text -noout -in /etc/routesyncd/gobgpcert/client-cert.pem

# 查看 key 证书私钥信息
# openssl rsa -text -noout -in /path/to/your_private_key.pem

openssl rsa -text -noout -in /etc/routesyncd/routesyncd_test/certskeys/server-key.pem
openssl rsa -text -noout -in /etc/routesyncd/routesyncd_test/certskeys/client-key.pem

openssl rsa -text -noout -in /etc/routesyncd/gobgpcert/commonserver-key.pem
openssl rsa -text -noout -in /etc/routesyncd/gobgpcert/client-key.pem

# 校验证书
# openssl verify -CApath /path/to/the/CA_directory/ /path/to/your/certificate.pem
openssl verify -CApath /root/my_cert/ cert.pem key.pem
openssl verify -CAfile ca-cert.pem server-cert.pem client-cert.pem
openssl verify -CAfile ca-cert.pem commonserver-cert.pem client-cert.pem

# 生成证书 1
openssl req -newkey rsa:2048 -new -nodes -keyout key.pem -out csr.pem
# 生成证书 2
openssl req -newkey rsa:2048 -new -nodes -x509 -days 3650 -keyout key.pem -out cert.pem
```

### 1.13.3. 查看环境支持 openssl 证书
```shell
openssl ciphers -v 'ALL:COMPLEMENTOFALL'
openssl ciphers -v 'ALL:COMPLEMENTOFALL' | grep TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256
TLSv1.2 Record Layer: Alert (Level: Fatal, Description: Bad Certificate)
    Content Type: Alert (21)
    Version: TLS 1.2 (0x0303)
    Length: 2
    Alert Message

```

## 1.14. 设置服务器DNS
可设置主机dns为目标DNS （/etc/resolv.conf）
```shell
cat /etc/resolv.conf

domain google.com
options rotate
nameserver 8.8.8.8
nameserver 8.8.4.4
```

## 1.15. 添加 apt 源
```shell
# 添加阿里源，以Debian10为例
mv /etc/apt/sources.list /etc/apt/sources.list.bak && \
echo "deb https://mirrors.aliyun.com/debian/ buster main non-free contrib" > /etc/apt/sources.list && \
echo "deb-src https://mirrors.aliyun.com/debian/ buster main non-free contrib" >> /etc/apt/sources.list && \
echo "deb https://mirrors.aliyun.com/debian-security buster/updates main" >> /etc/apt/sources.list && \
echo "deb-src https://mirrors.aliyun.com/debian-security buster/updates main" >> /etc/apt/sources.list && \
echo "deb https://mirrors.aliyun.com/debian/ buster-updates main non-free contrib" >> /etc/apt/sources.list && \
echo "deb-src https://mirrors.aliyun.com/debian/ buster-updates main non-free contrib" >> /etc/apt/sources.list && \
echo "deb https://mirrors.aliyun.com/debian/ buster-backports main non-free contrib" >> /etc/apt/sources.list && \
echo "deb-src https://mirrors.aliyun.com/debian/ buster-backports main non-free contrib" >> /etc/apt/sources.list
```

## 1.16. 更新 apt-source-list
```shell
# 编辑
/etc/apt/source.list

# 或在下方目录添加 source list 文件
/etc/apt/sources.list.d/*

apt-get update -y
```

## 1.17. 添加静态DNS解析和静态路由
```shell
# （临时）加了两条 hosts 和路由
echo '10.20.30.40 ABC.org' >> /etc/hosts
sudo /etc/init.d/networking restart
sudo ip route add 10.20.30.40 via 10.0.0.1 dev eth0

sudo apt-get update
```

## 1.18. 安装 Apache2 网页
```shell
apt install apache2

# 创建站点文件夹
SITE_DIR='/data00/www'
mkdir -p $SITE_DIR
sudo chown -R root:root $SITE_DIR/html
sudo chmod -R $SITE_DIR/html 400
sudo find $SITE_DIR/html -type d -exec chmod 755 {} \;
sudo find $SITE_DIR/html -type f -exec chmod 644 {} \;

# （可选）配置站点目录（DocumentRoot /var/www/html ->  /data00/www/html ）
vi /etc/apache2/sites-available/000-default.conf
DocumentRoot /var/www/html
# DocumentRoot /data00/www/html

# (可选) 配置站点指定 URL 路径对应 站点路径（可不在 DocumentROOT 下）
vi /etc/apache2/sites-available/000-default.conf
	# Alias "/sonic" "/data00/fileserver/files/sonic"
	# <Directory "/data00/fileserver/files/sonic">
	#     Options Indexes MultiViews
	#     AllowOverride None
	#     Require all granted
	# </Directory>
	# Alias "/bfn" "/data00/fileserver/files/bfn"
	# <Directory "/data00/fileserver/files/bfn">
	#     Options Indexes MultiViews
	#     AllowOverride None
	#     Require all granted
	# </Directory>
	# Alias "/sonic_dep_pkgs" "/data00/fileserver/files/sonic_dep_pkgs"
	# <Directory "/data00/fileserver/files/sonic_dep_pkgs">
	#     Options Indexes MultiViews
	#     AllowOverride None
	#     Require all granted
	# </Directory>

# 配置文件 （修改默认站点 /var/www/ 为 /data00/www/ ）
vi /etc/apache2/apache2.conf

sudo systemctl restart apache2

# check
sudo systemctl status apache2
```

## 1.19. 解决 SSH 自动断连问题
step 1. 修改 /etc/profile中改MOUT的值
```shell
# 检查（未设置/缺省值为 0，表示不超时）
echo $TMOUT

# 若超过 0，则可在 /etc/profile 之类文件中设置它为 0
sudo vi /etc/profile
```

step 2. 修改 /etc/ssh/sshd_config 文件
```shell
# 1. 注释掉下面的 (允许账户密码登录)
#PasswordAuthentication no

# 2. 将允许添加了 authorized_keys 的客户端免密登录设置为 yes
PubkeyAuthentication yes

# (opt). 设置 ClientAliveInterval，表示服务器端向客户端请求消息的时间间隔（默认值 0，不发送），应改为 60 每分钟发送一次，从而保持长连接
ClientAliveInterval 60

# (opt). 设置 ClientAliveCountMax，表示允许探活失败并断链的最大次数，改为 3 即可
ClientAliveCountMax 3
```

step3. 重启 sshd 服务，以生效配置
```shell
sudo systemctl reload sshd
# sudo /etc/init.d/ssh restart
```

## 1.20. 删除已知 HOST
```shell
ssh-keygen -f ~/.ssh/known_hosts -R '192.168.3.58'
```

# 2. 排障
## 2.1. 查看网口信息（speed）
```shell
sudo ethtool eth1
sudo ethtool eth0 | grep -i speed
sudo ethtool eth1 | grep -i speed
```

## 2.2. 查看网卡型号
```shell
lspci | egrep -i --color 'network|ethernet'
lspci | egrep -i --color 'network|ethernet|wireless|wi-fi'

# 查看 eth0/1 各接口 网卡型号
sudo lshw -class network -short | fgrep -v 'Ethernet interface'

# 查看具体 接口硬件信息
sudo ethtool -i eth0
```

## 2.3. 查看端口占用
```shell
# (UDP类型的端口)
netstat -nupl

# (TCP类型的端口)
netstat -ntpl
```

## 2.4. 查看指定端口的建链数
```shell
sudo netstat -nat | grep :8089
```

## 2.5. 查看 ssh 登录在线人数
```shell
# 统计 ssh 在线人数
w | grep pts | wc -l
```

## 2.6. 手动获取 DHCP ip
```shell
sudo dhclient -v eth0
```

## 2.7. 查看网络服务状态
```shell
sudo systemctl status networking

# 重启网络
sudo systemctl restart networking

# 重启特定网卡
ifdown eth2; ifup eth2
ifdown eth3; ifup eth3
```

## 2.8. 查看网卡数据
```shell
MY_ETH='eth4'
MY_ETH='eth5'

# 查看系统硬件信息及网卡驱动
sudo lshw -C network | grep -C 7 $MY_ETH

# 查看网口基本信息
ethtool $MY_ETH

# 点亮网卡灯（亮 10 秒）
ethtool -p $MY_ETH 10
ethtool -p eth1 100

# 查看网卡队列数量（多队列提升性能）
ethtool -l $MY_ETH
## 修改网卡队列数
ethtool -L $MY_ETH combined 4

# 查询网口驱动相关信息
ethtool -i $MY_ETH

# 显示网卡 「环形队列」RingBuffer 大小 （最大值，当前实际分配至）
ethtool -g $MY_ETH
# 修改「环形队列」RingBuffer 大小
ethtool -G $MY_ETH rx 4096 tx 4096

# 查看网口所有统计相关信息
ethtool -S $MY_ETH
## 查看网卡各个队列收包数据
ethtool -S $MY_ETH | grep rx_queue | grep packets
ethtool -S $MY_ETH | grep packets
## 查看网卡因 「环形队列」RingBuffer满丢包数
ethtool -S $MY_ETH | fifo_errors

# 显示网卡 offload 参数的状态
ethtool -k $MY_ETH

# 查看网卡 ntuple 配置规则
ethtool -n $MY_ETH

# 查看现有 flow-hash 配置
ethtool -n $MY_ETH rx-flow-hash tcp4

# 同时设置 速率/全双工/关自协商
sudo ethtool -s $MY_ETH speed 100000 duplex full autoneg off

# 设置网口速率 Mbps (10/100/1000/10000/100000)，自协商需关闭
ethtool -s $MY_ETH speed 100000

# 设置网口半/全双工 (half|full)，自协商需关闭
ethtool -s $MY_ETH duplex full

# 设置网口是否自协商 (on|off)
ethtool -s $MY_ETH autoneg on

# 设置网口类型 (tp|aui|bnc|mii)
ethtool -s $MY_ETH port tp|aui|bnc|mii

# 查看队列对应硬件中断号
cat /proc/interrupts
```

## 2.9. 查看网卡 MAC 地址
```shell
/sbin/ifconfig eth0 | grep 'ether'  | awk '{ print $2 }'
# 或
cat /sys/class/net/eth0/address
```

## 2.10. 网卡不能正常 UP 定位
定位 eth4 不能 up
```shell
# 罗列 pci 查看网卡型号 (e.g. 得知网卡为脉络思 Mellanox 网卡)
sudo lspci -v | grep -A 10 'Ethernet controller'

# 查看网卡驱动名 （e.g. mlx5_core ）
sudo lspci -v | grep -A 10 'Ethernet controller' | grep driver | cut -d : -f 2

# 查看系统异常告警信息 (得知 eth4 PCIE 地址 0000:86:00.0 )
sudo dmesg | grep -E 'mlx5_core|eth4'

# 查看 eth4
sudo udevadm test-builtin net_id /sys/class/net/eth4

sudo udevadm info /sys/class/net/eth4

# 开 eth4 电源
ETH_PCIE_ADDR='0000:86:00.0'
sudo bash -c "echo on > /sys/bus/pci/devices/$ETH_PCIE_ADDR/power/control"

# 还不行，考虑是否光模块没接好
sudo ethtool eth4 | grep 'Link detected'
```

## 2.11. 抓包
```shell
tcpdump -i eth0 | grep "192.168.3.238"
sudo tcpdump -i eth0 -vv -xx -w mgmt.pcap

# 抓包指定端口（采集器端执行）
sudo tcpdump -i Bridge port 8088 -n

# 抓取指定目的 IP 的包
sudo tcpdump -i Bridge dst net 10.167.204.111
sudo tcpdump -i Bridge -vnn dst net 10.32.124.119

# 抓取目的 IP 为 10.167.204.111 且源 port 为 8088 的包
sudo tcpdump -i Bridge -vnn dst host 10.167.204.111 and src port 8088

# 1、抓取包含 10.10.10.122 的数据包
sudo tcpdump -i eth0 -vnn host 10.10.10.122
# 2、抓取包含 10.10.10.0/24 网段的数据包
sudo tcpdump -i eth0 -vnn net 10.10.10.0/24
# 3、抓取包含端口 22 的数据包
sudo tcpdump -i eth0 -vnn port 22
# 4、抓取 udp 协议的数据包
sudo tcpdump -i any -nn -vv proto UDP
# 4、抓取 udp 协议 且 源目 IP 包含指定 IP 的数据包
sudo tcpdump -i any -nn -vv proto UDP and host 10.134.22.222
# 5、抓取 icmp 协议的数据包
sudo tcpdump -i eth0 -vnn icmp
# 6、抓取 arp 协议的数据包
sudo tcpdump -i eth0 -vnn arp
# 7、抓取 ip 协议的数据包
sudo tcpdump -i eth0 -vnn ip
# 8、抓取源 ip 是 10.10.10.122 数据包。
sudo tcpdump -i eth0 -vnn src host 10.10.10.122
# 9、抓取目的 ip 是 10.10.10.122 数据包
sudo tcpdump -i eth0 -vnn dst host 10.10.10.122
sudo tcpdump -i eth0 -vnn dst host 10.32.124.119
# 10、抓取源端口是 22 的数据包
sudo tcpdump -i eth0 -vnn src port 22
# 11、抓取源 ip 是 10.10.10.253 且目的 ip 是 22 的数据包
sudo tcpdump -i eth0 -vnn src host 10.10.10.253 and dst port 22
# 12、抓取源 ip 是 10.10.10.122 或者包含端口是 22 的数据包
sudo tcpdump -i eth0 -vnn src host 10.10.10.122 or port 22
# 13、抓取源 ip 是 10.10.10.122 且端口不是 22 的数据包
sudo tcpdump -i eth0 -vnn src host 10.10.10.122 and not port 22
# 14、抓取源 ip 是 10.10.10.2 且目的端口是 22，或源 ip 是 10.10.10.65 且目的端口是 80 的数据包。
sudo tcpdump -i eth0 -vnn ( src host 10.10.10.2 and dst port 22 ) or ( src host 10.10.10.65 and dst port 80 )
# 15、抓取源 ip 是 10.10.10.59 且目的端口是 22，或源 ip 是 10.10.10.68 且目的端口是 80 的数据包。
sudo tcpdump -i eth0 -vnn ‘src host 10.10.10.59 and dst port 22’ or ’ src host 10.10.10.68 and dst port 80 ’
# 16、把抓取的数据包记录存到/tmp/fill 文件中，当抓取 100 个数据包后就退出程序。
sudo tcpdump –i eth0 -vnn -w /tmp/fil1 -c 100
# 17、从/tmp/fill 记录中读取 tcp 协议的数据包
sudo tcpdump –i eth0 -vnn -r /tmp/fil1 tcp
# 18、从/tmp/fill 记录中读取包含 10.10.10.58 的数据包
sudo tcpdump –i eth0 -vnn -r /tmp/fil1 host 10.10.10.58
```

## 2.12. TFTP传输
```shell
# 从 netadmin 服务器 /tftpboot/ 下拉文件（注：需提前拷到 /tftpboot/， 且目标文件不能为文件夹）
tftp 10.20.30.40 -c get extract_error_log.sh /home/haoleeson/extract_error_log.sh

# 上传文件到 netadmin 服务器的 /tftpboot/ 目录 （注：发送文件指定当前文件夹中的文件即可）
tftp 10.20.30.40 -c put /home/haoleeson/test12390.txt
```

## 2.13. SFTP传输
```shell
# 上传文件到指定远程服务器目录（类似 scp，需输入密码）
sftp haoleeson@10.20.30.40:/home/haoleeson/inspect_error_log <<< $'put /home/haoleeson/test12390.txt'

# 下载文件到本地
sftp haoleeson@10.20.30.40:/home/haoleeson/pexpect-2.3.tar.gz ./
```

## 2.14. SCP传输
```shell
# 通过跳板机上传文档至生产设备
scp -o ProxyCommand="ssh -qW %h:%p jump-proxy.org" -r <src-dir> root@10.20.30.40:/root/

## 下载服务器日志（在 mac 终端执行）
scp -J netjump haoleeson@10.20.30.40:logfile/logfile10.log ~/Downloads/

## 下载 testbed 服务器文件到本地（在 mac 终端执行）
scp -J netjump haoleeson@10.20.30.40:/data00/home/haoleeson/test.log  ~/Downloads/

# scp 拉取/发送多个文件，用引号包含多个文件
# 拉取指定多个文件
scp haoleeson@10.20.30.40:"path_to_file_a  path_to_file_b" ~/

# 发送多个文件到远程
scp "path_to_file_a  path_to_file_b" haoleeson@10.20.30.40:/home/haoleeson/
```

## 2.15. curl
```shell
# 模拟 POST 请求
curl -header "Content-Type: application/json"
	-X POST
	-d --data '{"args": }'
	"http://192.168.0.1:8001/test"

# 模拟 POST 请求
curl  -d -H "Content-Type: application/json" --data '{"args": []}' \
        http://10.32.124.40:8000/platform/chassis/get_system_eeprom_info

# 模拟 POST 请求，调 HPA xgw-test-agent api 宣告路由
curl -d '{"v4_ips":["192.168.138.10/32"],"v6_ips":["10:254:254::254/128"]}' -H "Content-Type: application/json" -X POST http://127.0.0.1:11001/config_bgp_network
curl -d '{"v4_ips":["192.168.138.10/32"],"v6_ips":[]}' -H "Content-Type: application/json" -X POST http://127.0.0.1:11001/config_bgp_network

curl -d '{}' -H "Content-Type: application/json" -X POST http://10.11.112.137:11001/is_lambda
curl -d '{"name":"xgw_controller"}' -H "Content-Type: application/json" -X POST http://10.11.112.137:11001/restart_docker
```

## 2.16. 查看 Linux TCP keepalive 配置
```shell
sudo sysctl -a | grep keepalive
```

# 3. 测试

## 3.1. 网络测速工具 iperf
### 3.1.1. 开启防火墙 5001 端口(iperf2 默认 5001, iperf3 默认 5201)
```shell
iptables -A INPUT -p tcp --dport 5001 -j ACCEPT
iptables -A INPUT -p udp --dport 5001 -j ACCEPT
# check
iptables -n -L | grep 5001
```
### 3.1.2. TCP 测试
**-B 10.0.0.45**: 绑定自身 IP
**-s**: 服务端端
```shell
# 一台运行服务端 (10.0.0.45)
# iperf -B <my_interface_ip> -s
## -p 服务端 端口号
iperf -B 10.0.0.45 -p 5001 -s
iperf -B 10.201.40.80 -p 5001 -s
iperf -B 172.16.1.1 -p 5001 -s

# 一台运行服务端 (10.0.0.47)
# iperf -B <my_interface_ip> -c <server_ip>
## -p 服务端 端口号
## -t 测试秒数
iperf -B 10.0.0.47 -c 10.0.0.45
iperf -B 10.32.124.41 -c 10.201.40.80
iperf -B 192.168.1.1 -c 172.16.1.1
```

### 3.1.3. UDP测试
**-b 100M** : 带宽限制 100Mbps
```shell
# 服务器执行
iperf -B 20.0.0.51 -p 5001 -u -s

# 客户端执行 （打流带宽限制 300K bps）
iperf -B 20.0.0.52 -c 20.0.0.51 -u -b 300K -t 60
# iperf -u -c 10.0.0.45 -b 900M  -i 1  -w 1M  -t 60
```

## 3.2. 安装qume虚拟机
> 镜像资源：
> - [Debian 9.13 (stretch)](https://cdimage.debian.org/cdimage/archive/9.13.0/amd64/iso-cd/debian-9.13.0-amd64-netinst.iso)

```shell
apt-get install qemu-kvm qemu-utils virt-manager libvirt-daemon gir1.2-spiceclientgtk-3.0
# 安装
sudo apt install qemu-kvm libvirt-clients libvirt-daemon-system bridge-utils virtinst libvirt-daemon virt-manager -y
# 检查
sudo systemctl status libvirtd.service
# 查看可供 kvm 使用的网络
sudo virsh net-list --all
# 配置 kvm 网络
sudo virsh net-start default
sudo virsh net-autostart default

# 新增用户组
sudo newgrp libvirt
sudo newgrp libvirt-qemu

# 配置普通用户也可使用 virsh
sudo adduser pkumar libvirt
sudo adduser pkumar libvirt-qemu

#
sudo apt-get install qemu qemu-kvm

# 创建虚拟机
sudo virt-install --name ubuntu-vm --os-type linux --os-variant ubuntu18.04 --ram 1024 --vcpu 1 --disk path=/var/lib/libvirt/images/ubuntu-vm.qcow2,size=10 --graphics vnc,listen=0.0.0.0 --noautoconsole --hvm --cdrom /home/pkumar/ubuntu-18.04-live-server-amd64.iso --boot cdrom,hd

# 查看运行中 虚拟机
sudo virsh list --all
```

## 3.3. 解析设备 IP
```shell
# 通过读配置文件获取 IP（可能与实际不一致）
grep -A 1 'MGMT_INTERFACE' /etc/sonic/libra_user.json | tail -n +2 | cut -d '|' -f 2 | cut -d / -f 1

# 通过命令查当前设备 IP
ip addr show eth0 | grep -oP \(\\d+\\.\){3}\\d+
ip addr show eth0 | grep -oE \([0-9]+\\.\){3}[0-9]+
ip addr show eth0 | grep -oE '([0-9]+\.){3}[0-9]+'
ip addr show eth0 | grep -oE "([0-9]{1,3}[\.]){3}[0-9]{1,3}"
ip addr show eth0 | grep global | awk '{ print $2 }' | cut -d / -f 1
ip addr show eth0 | grep inet | head -1 | tr / \ | cut -d \  -f 6
ip addr show eth0 | awk '$1 == "inet" {gsub(/\/.*$/, "", $2); print $2}'
```

## 3.4. Scapy
```shell
# 克隆
git clone https://github.com/secdev/scapy

# 安装
cd scapy
sudo python setup.py install

# check
scapy
```

### 3.4.1. 查看设备网络接口
```shell
# 运行
sudo ./run_scapy -H

# 查看所有网络接口
get_if_list()
# 或
conf.ifaces
```

### 3.4.2. 查看路由
```shell
# 查看路由
conf.route
conf.route6
```

### 3.4.3. 查看某接口 IP/MAC
```shell
# 获取接口 IP
get_if_addr("eth0")
get_if_addr("Ethernet32")

# 获取接口 MAC
get_if_hwaddr("eth0")
get_if_hwaddr("Ethernet32")
getmacbyip("10.0.0.1")
```

### 3.4.4. 简单 demo

```shell
# 运行
sudo ./run_scapy -H

# 构造报文
p = IP(dst="github.com")/ICMP()
p2 = Ether(src='00:00:00:00:00:01',dst='00:00:00:00:00:02')/IP(dst="10.32.124.40")/ICMP()
p3 = Ether()/IP(dst='192.168.1.2',ttl=10)/TCP(dport=80)
p4 = ARP(op=1, hwdst="ff:ff:ff:ff:ff:ff", pdst=ip_address)
```

### 3.4.5. 构造报文（计算校验和方式 1）
```shell
p = IP(src='192.168.1.1',dst='192.168.1.2')/TCP()/'abcdefg'
p = IP(raw(p))
```

### 3.4.6. 构造报文（计算校验和方式 2）
```shell
p = IP(src='192.168.1.1',dst='192.168.1.2')/TCP(chksum=0)/'abcdefg'
chk_str = raw(p)[20:]
p[TCP].chksum = in4_chksum(socket.IPPROTO_TCP,p[IP],chk_str)
```

### 3.4.7. 发包/收包
#### 3.4.7.1. 二层发包，指定出接口
```shell
# 发二层包（指定出接口），无效
sendp("I'm travelling on Ethernet", iface='Ethernet2', loop=1, inter=0.1)
```

#### 3.4.7.2. 普通收发包
通过 default 路由发包
```shell
# 仅发
send(pkt, inter=0, loop=0, count=1, iface=N)

# 发包且收包
# sr(): 接收多个回包
sr(IP(dst="www.baidu.com",ttl=(1,4))/TCP(dport=[21,23,80],flags="S"))
# sr1()：仅接收第一个回包
sr1(IP(dst="www.baidu.com",ttl=(1,4))/ICMP())
# srloop()： 循环发包/收包 （可配发包间隔、次数）
srloop(IP(dst="www.baidu.com",ttl=1)/ICMP(),inter=3,count=2) #每隔3秒ping一次，一共执行两次

```

### 3.4.8. 嗅探
```python
from scapy.all import *
pkt = sniff(iface = "Realtek PCIe GBE Family Controller",count = 3 ,filter='tcp',prn = lambda x: x.sprintf('{IP:%IP.src%->%IP.dst%\n}{Raw:%Raw.load%\n}'))

# filter:过滤条件
# iface：网卡接口名称
# count：数据包数量
# prn:回调函数，通常与lambda搭配使用
# sprintf()函数控制输入信息

# 抓取源地址为192.168.3.3的端口为80的tcp报文：
sniff(filter="ip src 192.168.3.3 and tcp and tcp port 80", prn=lambda x:x.summary())
# 抓取目的地址网段为192.168.3.3/24的报文：
sniff(filter="dst net 192.168", prn=lambda x:x.summary())
# 抓取非ICMP的报文：
sniff(filter="not icmp", prn=lambda x:x.summary())
# 将抓取到的报文的summary打印出来：
sniff(filter="icmp", prn=lambda x:x.summary(), count=10)
# 将所有IP报文的源地址打印出来：
sniff(filter="icmp", prn=lambda x:x[IP].src, count=10)
```
