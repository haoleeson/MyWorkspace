layout: post
title: 安装SONiC
date: 2021/9/28 22:30:45
updated: 2021/9/28 22:40:45
comments: true
tags: 
- SONiC
categories:
- 技术

---

# 1. 准备工作
## 1.1. 制作 SONiC 安装U盘
### 1.1.1. 依赖材料
1. 一台带 USB 接口的白盒交换机（已安装 SONiC 系统）
2. 一个空U盘 （容量高于2G）
3. 两个<font color="red" style="">安装文件</font>：sonic.bin 和 sonic-recovery.bin
  - sonic.bin，全量安装 SONiC 系统的二进制文件（六百多MB）
  - sonic-recovery.bin，构建/恢复 SONiC-OS 系统基础环境的二进制文件（约三百MB）

<!-- more -->

其中，sonic.bin 和 sonic-recovery.bin 的编译方式如下：
>备注：
>- 编译 SONiC 版本需确保当前登录用户已加入 <b><font color="#7E3D76" style="">docker</font></b> 组
>- 查询当前 <b><font color="#7E3D76" style="">docker</font></b> 组用户列表的命令为： <code>sudo cat /etc/group | grep docker</code> 
>- 若当前登录用户不在 <b><font color="#7E3D76" style="">docker</font></b> 组用户列表中，则需添加到 <b><font color="#7E3D76" style="">docker</font></b> 组用户列表，命令为：  <code>sudo usermod -aG docker ${当前用户名} </code> 


```shell
# 1. 进入 SONiC 源码目录
cd $SONIC_CODE_DIR
# 2. 设置芯片厂商（eg. broadcom）
make configure PLATFORM=broadcom
# 3. 执行 make 编译 sonic.bin （编译用时约 1小时）
make target/sonic.bin
# 4. 执行 make 编译 sonic-recovery.bin （编译用时约 10分钟）
make target/sonic-recovery.bin
```

### 1.1.2. 制作安装U盘
1. 上传两个<font color="red" style="">安装文件</font>到（用于制作安装U盘的）SONiC白盒交换机的 /host/ 目录

```shell
# 拷贝安装文件到交换机（eg. 通过 scp 命令传输）
scp sonic.bin admin@A.B.C.D:/home/admin
scp sonic-recovery.bin admin@A.B.C.D:/home/admin
# 拷贝安装文件到交换机的 /host/ 目录
cp /home/admin/sonic.bin /host/
cp /home/admin/sonic-recovery.bin /host/
# 同步
sync
```

2. 在（用于制作安装U盘的）白盒交换机上，安装 SONiC-OS recovery 基础镜像

```shell
# 进入 /host/ 目录
cd /host/
# 安装 SONiC-OS recovery 基础镜像
./sonic-recovery.bin -L SONiC-OS –g
```

3. 重启设备，进入上一步新安装的SONIC-OS recovery 基础镜像系统<br>（依据当前时间，在GRUB中选择进入上一步安装的系统版本）
4. 插入U盘，查看U盘盘符<br>（根据U盘容量判别，eg. 32G）

```shell
fdisk -l
# 示例U盘盘符名：/dev/sdb
Disk /dev/sdb: 28.8 GiB, 30943995904 bytes, 60437492 sectors
# 示例U盘分区名：/dev/sdb1~n
Device      Start       End         Sectors     Size        Type
/dev/sdb3   526370      60434458    59910000    28.6G       filesystem
```

5. 制作安装U盘<br>（上一步获知的U盘盘符名： <code>/dev/sdb</code> ）

```shell
./sonic-recovery.bin -u -n /dev/sdb
```

6. 同时将两个安装文件拷贝到U盘<br>（上一步获知的U盘分区名：/dev/sdb3）

```shell
# 挂载U盘
mount /dev/sdb3 /mnt/
# 拷贝安装文件到 U 盘
cp /host/sonic.bin /mnt/
cp /host/sonic-recovery.bin /mnt/
# 同步
sync
```

## 1.2. 安装/配置 minicom 串口工具

minicom 对比 screen 优势：
- screen 方式连接串口设备： <code>screen /dev/tty.usbserial-110 115200</code>
  - 优势：系统自带，随用随取。
  - 短板：用完要关闭需要先按Ctrl+A，再按Ctrl+K来杀掉进程；可能遇到在关闭后/dev路径没有Serial文件而无法使用的情况。
- minicom 串口工具连接串口设备： <code>minicom -c on</code> 
  - 优势：使用便捷，仅需一次配置，后续自动调用连接配置；稳定性好；支持热插拔；功能丰富。

### 1.2.1. 安装 minicom 串口工具
- 执行 <code>brew install minicom</code> 命令安装 minicom （依赖工具 [HomeBrew](https://brew.sh/)）

### 1.2.2. 配置 minicom 串口工具
1. <b><font color="#7E3D76" style="">查询串口设备ID</font></b><br>（需在串口线连接 **交换机** 与 **Mac笔记本**后执行下方命令才能看到）

```shell
ls -l /dev/tty.usb*
# 执行结果示例
/dev/tty.usbserial-110
```

2. <b><font color="#7E3D76" style="">进入 minicom 配置界面</font></b>

```shell
minicom -s
```

3. <b><font color="#7E3D76" style="">进入串口配置项</font></b><br>上下方向键移动光标，选择“Serial port setup”，Enter 确认
4. <b><font color="#7E3D76" style="">更改串口设备 ID</font></b><br>按 A 进入“Serial Device”配置，删除默认值 /dev/modem，更改为第 1 步查询得到的设备 ID（eg. <code>/dev/tty.usbserial-110</code> ），Enter 确认更改
5. <b><font color="#7E3D76" style="">更改波特率</font></b><br>按 E 进入“Bps/Par/Bits”配置，选择适当波特率（如，按 E 切换波特率为 115200），Enter 确认更改
6. <b><font color="#7E3D76" style="">关闭硬件流控</font></b><br>按 F 切换“Hardware Flow Control”开关值，切换为“NO”<br>示例配置如下：

```shell
    +-----------------------------------------------------------------------+
    | A -    Serial Device      : /dev/tty.usbserial-110                    |
    | B - Lockfile Location     : /opt/homebrew/Cellar/minicom/2.8/var      |
    | C -   Callin Program      :                                           |
    | D -  Callout Program      :                                           |
    | E -    Bps/Par/Bits       : 115200 8N1                                |
    | F - Hardware Flow Control : No                                        |
    | G - Software Flow Control : No                                        |
    | H -     RS485 Enable      : No                                        |
    | I -   RS485 Rts On Send   : No                                        |
    | J -  RS485 Rts After Send : No                                        |
    | K -  RS485 Rx During Tx   : No                                        |
    | L -  RS485 Terminate Bus  : No                                        |
    | M - RS485 Delay Rts Before: 0                                         |
    | N - RS485 Delay Rts After : 0                                         |
    |                                                                       |
    |    Change which setting?                                              |
    +-----------------------------------------------------------------------+
```

7. <b><font color="#7E3D76" style="">保存配置</font></b><br>按 Enter 或 Esc 退回到“configuration”主界面，选择“Save setup as dfl”保存为默认配置，最后选择“Exit from Minicom”退出

### 1.2.3. 通过 minicom 串口工具登录交换机
1. 用串口线连接 **交换机** 与 **Mac笔记本**
2. 通过串口工具访问**交换机**（终端执行命令为： <code>minicom -c on</code> ）

备注： ESC + Z 可调出 minicom 工具的命令菜单

# 2. 安装 SONiC
## 2.1. 通过 U 盘安装 SONiC 系统

<b><font color="#7E3D76" style="">1. 从U盘启动</font></b><br>
  - 交换机插入安装U盘
  - 重启（BIOS 默认优先从U盘启动）
  - 输入U盘中 SONiC 系统的用户/密码: admin/admin
  - 进入 /host/ 目录，确认存在两个<font color="red" style="">安装文件</font> ：sonic.bin 和 sonic-recovery.bin

<b><font color="#7E3D76" style="">2. （交换机）硬盘分区并准备SONiC-OS基础环境</font></b><br>

> 通过 sonic-recovery.bin 对（交换机）硬盘进行分区并准备 SONiC-OS 基础环境

  - (1). 通过 <code>blkid</code> 命令查看交换机分区信息及了解硬盘类型（sda 或 nvme）
  - (2a). 若执行blkid命令显示的信息中，硬盘类型为 <b><font color="red" style="">sda</font></b> ，则执行以下命令：

```shell
./sonic-recovery.bin -n /dev/sda
```
  - (2b). 若执行blkid命令显示的信息中，硬盘类型为 <b><font color="red" style="">nvme</font></b> ，则执行以下命令：

```shell
./sonic-recovery.bin -n /dev/nvme0n1
```
  - (3). 再次通过 <code>blkid</code> 命令查看硬盘分区信息，确认硬盘分区信息囊括下方所有 **LABEL** <br>（GRUB、SONiC-OS、Recovery、Diag、Reserved、Log）

<b><font color="#7E3D76" style="">3. 安装 SONiC 系统</font></b>

执行下方命令安装 SONiC 系统

```shell
./sonic.bin
```

<b><font color="#7E3D76" style="">4. 拔掉U盘，重启</font></b>

## 2.2. 通过 ONIE 重装 SONiC
<b><font color="#7E3D76" style="">1. 卸载旧 SONiC</font></b><br>
- 串口访问设备（切COM-E），手动重启；
- 在 GRUB 菜单选择 ONIE: Uninstall OS，等待其卸载旧 SONiC 系统后自动重启；
- 在重启后的 GRUB 菜单选择 ONIE: Rescue；
- 在提示 "please press enter to activate this console" 后，按回车进入 ONIE 系统

<b><font color="#7E3D76" style="">2. 手动配置 ONIE 系统的管理 IP</font></b><br>
> 配置同网段IP

```shell
ifconfig eth0 1.2.3.4 netmask 255.255.255.0
```

<b><font color="#7E3D76" style="">3. 拷贝 SONiC 安装镜像到 ONIE 系统的 /tmp 路径</font></b><br>
```shell
scp admin@4.5.6.7:/home/admin/sonic.bin /tmp/
```


<b><font color="#7E3D76" style="">4. 通过 onie-nos-install 安装 SONiC 镜像</font></b><br>

```shell
onie-nos-install /tmp/sonic.bin
```

## 2.3. 通过 sonic_installer 更新 SONiC
若设备已安装旧版 SONiC，可直接通过 sonic_installer 指令更新版本

```shell
sudo sonic_installer install -f /home/admin/new-sonic.bin
```

# 3. 配置交换机IP及管理网路由
> 备注：
> - 建议串口访问下执行下述操作，ssh 访问可能会因重新分配 IP 导致断连
> - <b><font color="red" style="">重启后 IP 配置丢失根因</font></b>：ZTP 服务启动后若发现同时缺失配置文件 <code>/etc/sonic/config_db.json</code> 和 旧配置文件夹 <code>/etc/sonic/old_config/</code> ，将自动获取IP，强制覆盖已配置的静态 IP。<br>故在新设备配置IP，需先开启 ZTP 服务并执行 config save 生成配置文件，然后配置静态管理 IP，以防止重启后 ZTP 检测到无配置文件而去自动获取IP导致IP配置丢失。
> - 若发现设备缺失配置文件 <code>/etc/sonic/config_db.json</code> ，执行下方 3(a) 步即可配置IP并生成配置文件。
> - 若发现设备管理 IP 丢失（ <code>/etc/network/interfaces</code>文件被删 ），执行下方 3(b) 步即可配置静态 IP（此文件为生成文件，不推荐手动配置）。

（SONiC 支持通过 cli 配置，可作为接线后临时测试的配置参考）

1. <b><font color="#7E3D76" style="">查看设备状态信息</font></b>

```shell
# 查看此设备有无“用户配置”文件
ls -l /etc/sonic/config_db.json
# 查看当前设备 IP
ip addr | grep 'scope global eth0' | awk '{ print $2 }'
# 查询 ZTP 服务启/停状态
systemctl list-units --all --type=service | grep ztp
# 查看 ZTP 服务详细状态信息
sudo service ztp status
# 查看生成的配置文件中是否包含管理IP字段
sed -n "$(grep -n 'MGMT_INTERFACE' /etc/sonic/config_db.json | tail -1 | cut -d : -f 1), +5p" /etc/sonic/config_db.json
```

2. <b><font color="#7E3D76" style="">打开“零配置部署”功能（Zero Touch Provisioning，ZTP）</font></b>

```shell
# 若 ztp 服务未开启，需执行下方命令开启 ZTP 服务
sudo systemctl start ztp
# 备注：
sudo update-rc.d -f ztp remove      # 禁止 ZTP 服务开启自启  
sudo update-rc.d ztp enable 2 3 4 5 # 开启 ZTP 服务开机自启
```
  - 若设备缺失配置文件<code>/etc/sonic/config_db.json</code>且启动时 ztp 服务已开启，执行 <code>ip addr | grep eth0</code> 将能看到已自动获取的 IP（eg.10.0.0.2）
  - 若此时无 IP，执行下方 3(a) 步即可配置IP并生成配置文件。

3. <b><font color="#7E3D76" style="">配置IP</font></b><br>（如配置交换机的 静态IP为：10.0.0.2/24、网关为：10.0.0.0）
<br><font color="black" style="">a. 方式一：通过调用cli命令配置IP（推荐）</font>

```shell
cli
sonic> configure terminal
sonic(config)# interface-config
sonic(interface config)# management
sonic(interface mgmt)# ipv4-family
sonic(interface mgmt v4)# address 10.0.0.2/24
```
或调 cli 命令行

```shell
# 调命令配置静态IP和网关（静态IP为：10.0.0.2/24、网关为：10.0.0.0）
sudo config interface eth0 ip add 10.0.0.2/24
# 添加到管理网路由（目的IP为：10.0.0.0/8、下一跳为网关：10.0.0.0）
sudo config route mgmt add 10.0.0.0/8 10.0.0.0 eth0
```
生成配置文件

```shell
sudo config save
```
查看生成的配置文件中是否包含管理IP字段

```shell
sed -n "$(grep -n 'MGMT_INTERFACE' /etc/sonic/config_db.json | tail -1 | cut -d : -f 1), +5p" /etc/sonic/config_db.json
```
<br><font color="black" style="">b. 方式二：通过直接修改网卡配置文件（临时，重启后失效）</font><br>通过 <code>sudo vi /etc/network/interfaces</code> 修改网卡配置文件，示例配置内容如下：

```shell
auto lo
iface lo inet loopback
# The management network interface
auto eth0
iface eth0 inet static
    address 10.0.0.2
    netmask 255.255.255.0
    # management network policy routing rules
    # management port up rules
    up ip -4 route add 10.0.0.0/24 dev eth0 table default
    up ip -4 rule add from 10.0.0.2/32 table default
    # management port down rules
    down ip -4 route delete 10.0.0.0/24 dev eth0 table default
    down ip -4 rule delete from 10.0.0.2/32 table default
source /etc/network/interfaces.d/*
```
生效配置<br>（以下方式均可）
  - a.重启网络：<code>sudo /etc/init.d/networking restart</code> 或 <code>sudo service networking restart</code><br><font color="black" style="">
  - b.重启网卡（eg. eth0）： <code>sudo ifdown eth0</code> 或 <code>sudo ifup eth0</code>


# 4. 参考文档
- [Mac笔记本 Pro 工具之 minicom安装与串口配置](https://blog.csdn.net/dirksmaller/article/details/105063379)
- [linux route命令详解](https://www.cnblogs.com/xig112635/p/14838651.html)
