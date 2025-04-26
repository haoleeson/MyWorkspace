layout: post
title: sonic各类告警日志梳理
date: 2022/2/14 22:30:45
updated: 2022/2/14 23:10:45
comments: true
tags: 
- SONiC
categories:
- 技术

---

本文记录一些SONiC硬件、端口、协议、系统类典型日志，便于快速定位问题。

<!-- more -->

# 1. 硬件类
> 本地日志：/var/log/syslog

## 1.1. 电源

- 插入
```shell
# 初始化时默认打印
2022-02-14 17:56:02.609340 HOSTNAME <local2.warning> WARNING pmon#hwmgrd: :pluggable_dev_log:- Psu2 is plugged in. vendor: ARTESYN, serial number: L214VZ006005P
```

- 拔出
```shell
# 暂无操作日志，日志代码如下：
logger.log_warning(device + ' is pulled out. ')
# 预估拔出电源日志
2022-02-14 17:56:02.609340 HOSTNAME <local2.warning> WARNING pmon#hwmgrd: :pluggable_dev_log:- Psu2 is pulled out.
```

- 异常
```shell
# 异常也可能为四种异常（'no power', 'thermal error', 'fan error', 'vol error'）的任意组合，共 15 种情况：
2022-02-14 17:56:02.614955 HOSTNAME <local2.warning> WARNING pmon#hwmgrd: :dev_alarm_log:- Psu2 is alarm: no power
2021-12-22 03:42:27.825952 HOSTNAME <local2.warning> WARNING pmon#hwmgrd: :dev_alarm_log:- Psu1 is alarm: from normal to no power, vol error
```

- 正常
```shell
# 初始化时也会打印
2022-02-14 17:56:02.596387 HOSTNAME <local2.warning> WARNING pmon#hwmgrd: :dev_alarm_log:- Psu1 is normal
```

## 1.2. 风扇
- 插入
```shell
# 初始化时默认打印
2022-02-14 10:25:37.481551 HOSTNAME <local2.warning> WARNING pmon#hwmgrd: :pluggable_dev_log:- Fan2 is plugged in. vendor: Inventec, serial number: 945301818370UZ
```

- 拔出
```shell
# 暂无操作日志，日志代码如下：
logger.log_warning(device + ' is pulled out. ')
# 预估拔出风扇日志
2022-02-14 10:25:37.481551 HOSTNAME <local2.warning> WARNING pmon#hwmgrd: :pluggable_dev_log:- Fan2 is pulled out.
```

- 异常
```shell
# 暂无操作日志，日志代码如下：
logger.log_warning('%s is alarm' % device)
# 预估风扇异常日志
2022-02-14 17:56:15.038878 HOSTNAME <local2.warning> WARNING pmon#hwmgrd: :dev_alarm_log:- Fan6 is alarm
```

- 正常
```shell
# 初始化时正常默认打印
2022-02-14 17:56:15.038878 HOSTNAME <local2.warning> WARNING pmon#hwmgrd: :dev_alarm_log:- Fan6 is normal
```

## 1.3. CPU
> 本地日志：/var/log/monit.log

- monit 检测到用户态 CPU 使用率过高告警
```shell
2022-02-17 16:05:47.705193 HOSTNAME <local2.err> ERR monit[652]: 'HOSTNAME.TEST' cpu user usage of 93.1% matches resource limit [cpu user usage>90.0%]
```

- monit 检测到内核态 CPU 使用率过高告警
```shell
2022-02-17 16:16:06.390901 HOSTNAME <local2.err> ERR monit[615]: 'HOSTNAME.TEST' cpu system usage of 99.8% matches resource limit [cpu system usage>90.0%]
```

## 1.4. 内存
> 本地日志：/var/log/monit.log

- monit 检测到内存使用率过高告警
```shell
2022-02-17 16:46:05.407053 HOSTNAME <local2.err> ERR monit[641]: 'HOSTNAME.TEST' mem usage of 85.9% matches resource limit [mem usage>80.0%]
```

## 1.5. 硬盘
> 本地日志：/var/log/monit.log

- monit 检测到总磁盘使用率过高告警
```shell
2022-02-17 16:52:06.521099 HOSTNAME <local2.err> ERR monit[641]: 'root-overlay' space usage 91.3% matches resource limit [space usage>90.0%]
```

<!-- 

磁盘不可写异常（ XorPlus 设备）
```shell
Jan 1 11:44:33 100.122.166.72 HOSTNAME : [RTRMGR xorp_rtrmgr]Failed to save file /pica/config/pica_startup.boot: File /pica/config/pica_startup.boot.tmp exists, and can not be overwritten.#012Read-only file system
```
-->

<!-- ## 2.5. 槽位号 slot【hwmgrd 未支持】 -->

## 1.6. 光模块

- 插入
```shell
# 初始化时默认打印
2022-02-14 17:56:26.450923 HOSTNAME <local2.warning> WARNING pmon#hwmgrd: :pluggable_dev_log:- Sff12 is plugged in. vendor: FINISAR, serial number: PZ611NQ
```

- 拔出
```shell
2021-12-14 16:10:18.780321 HOSTNAME <local2.warning> WARNING pmon#hwmgrd: :pluggable_dev_log:- Sff1 is pulled out.
```

## 1.7. 线卡

- 插入
```shell
# 初始化时默认打印
2017-02-05 05:25:10.419415 HOSTNAME <local2.warning> WARNING pmon#hwmgrd: :pluggable_dev_log:- Linecard4 is plugged in. vendor: H3C, serial number: 210231AF1D020600001B
```

- 拔出
```shell
# 暂无操作日志，日志代码如下：
logger.log_warning(device + ' is pulled out. ')
# 预估拔出板卡日志
2017-02-05 05:25:10.419415 HOSTNAME <local2.warning> WARNING pmon#hwmgrd: :pluggable_dev_log:- Linecard4 is pulled out.
```

## 1.8. 温度

- 高温告警
```shell
2022-02-02 23:48:48.859650 HOSTNAME <local2.warning> WARNING pmon#drv: :dev_alarm_log:- Thermal alarm: hotspot11 : 93.00 Centigrade
```

# 2. 端口类
> 本地日志：/var/log/syslog

## 2.1. 硬件端口

- 端口 UP
```shell
2022-02-14 10:32:54.573793 HOSTNAME <local2.warning> WARNING swss#orchagent: :- updatePortOperStatus: OperStatus of Port Ethernet38 (alias: he-1/1/38) changed from down to up
```

- 端口 DOWN
```shell
2022-02-14 12:40:34.319598 HOSTNAME <local2.warning> WARNING swss#orchagent: :- updatePortOperStatus: OperStatus of Port Ethernet37 (alias: he-1/1/37) changed from up to down
```

## 2.2. 三层接口
- 三层接口 UP
```shell
2022-02-14 10:32:54.583867 HOSTNAME <local2.warning> WARNING swss#orchagent: :- setHostVlanAdminState: OperStatus of L3Interface Vlan38 changed to up
```

- 三层接口 DOWN
```shell
2022-02-14 12:40:34.344832 HOSTNAME <local2.warning> WARNING swss#orchagent: :- setHostVlanAdminState: OperStatus of L3Interface Vlan40 changed to down
```

# 3. 协议类异常

## 3.1. BGP
> 模块代码： <code>src/HOSTNAME-frr/frr/bgpd/</code> 

- 异常
```shell
# 暂未找到异常日志，日志代码如下：
zlog_err("BGPd daemon failed: %s", strerror(errno));
zlog_err("getsockopt of SO_SNDBUF failed %s\n", safe_strerror(errno));
zlog_err("couldn't create af structure for peer %s", peer->host);
zlog_err ("bgp_connect_success peer's fd is negative value %d",
```

### 3.1.1. BGP 容器停启日志
> 本地日志：/var/log/daemon.log

- BGP 容器启动日志
```shell
2022-01-25 11:11:51.100344 HOSTNAME <daemon.info> INFO systemd[1]: Started BGP container.
```

- BGP 容器停止日志
```shell
2021-12-24 11:20:50.749969 HOSTNAME <daemon.info> INFO systemd[1]: Stopping BGP container...
```

### 3.1.2. BGP 容器中关键子进程退出日志
> 此 local0 日志为监控工具 supervisor 产生（ <code>/var/log/syslog</code> ），不会上传日志服务器

- zebra 退出
```shell
2022-02-14 15:53:36.202696 HOSTNAME <local0.info> INFO bgp#supervisord 2022-02-14 15:53:31,385 INFO exited: zebra (terminated by SIGKILL; not expected)
```

- staticd 退出
```shell
2022-02-14 15:58:56.443911 HOSTNAME <local0.info> INFO bgp#supervisord 2022-02-14 15:58:55,433 INFO exited: staticd (terminated by SIGKILL; not expected)
```

- bgpd 退出
```shell
2022-02-14 16:01:46.588714 HOSTNAME <local0.info> INFO bgp#supervisord 2022-02-14 16:01:44,320 INFO exited: bgpd (terminated by SIGKILL; not expected)
```

### 3.1.3. BGP 建立/断开邻居事件日志
> 本地日志：/var/log/quagga/bgpd.log

<img src="../../../../uploads/BGP_state.png" class="full-image" />

- 邻居建立
```shell
2022-02-11 15:43:20.630737 HOSTNAME <local2.notice> NOTICE bgp#bgpd[45]: 10.166.0.66 went from Idle to Connect
2022-02-11 15:43:20.631348 HOSTNAME <local2.notice> NOTICE bgp#bgpd[45]: 10.166.0.66 went from Connect to OpenSent
2022-02-11 15:43:20.631844 HOSTNAME <local2.notice> NOTICE bgp#bgpd[45]: 10.166.0.66 went from OpenSent to OpenConfirm
2022-02-11 15:43:20.633960 HOSTNAME <local2.notice> NOTICE bgp#bgpd[45]: 10.166.0.66 went from OpenConfirm to Established
```

- 邻居断开
```shell
2022-02-13 00:19:45.015599 HOSTNAME <local2.notice> NOTICE bgp#bgpd[45]: 10.166.0.66 went from Established to Clearing
2022-02-13 00:19:45.128939 HOSTNAME <local2.notice> NOTICE bgp#bgpd[45]: 10.166.0.66 went from Clearing to Idle
```

## 3.2. OSPF【未支持】
> 模块代码： <code>src/HOSTNAME-frr/frr/ospfd</code>、 <code>src/HOSTNAME-frr/frr/ospf6d</code> 

- 异常
```shell
# 未启用，异常代码
printf("Connecting to OSPF daemon on %s failed!\n", args[1]);
vty_out (vty, "   OSPF not enabled on this interface%s", VNL);
flog_err(EC_OSPF_INIT_FAIL, "OSPF instance init failed: %s", strerror(errno));
flog_err(EC_LIB_SOCKET, "%s: ospf_sock_init is unable to open a socket", __func__);
```

## 3.3. ISIS【未支持】
> 模块代码： <code>src/HOSTNAME-frr/frr/isisd</code> 

- 异常
```shell
# 未启用，异常代码
flog_err(EC_ISIS_CONFIG, "Could not bring up %s because of invalid config.", circuit->interface->name);
flog_err(EC_ISIS_CONFIG, "Clearing config for %s. Please re-examine it.", circuit->interface->name);
```

# 4. MAC 类
> 这类异常发生在芯片层级，不会输出告警日志

但可通过监听 BCM 系列线程异常状态（<code>bcmL2X</code>、<code>bcmCNTR</code>、<code>bcmLINK</code>、<code>bcmDPC</code>、<code>bcmINTR</code>、<code>bcmTX</code>、<code>bcmXGS3AsyncTX</code>、<code>bcmRX</code>、<code>bcmL2age</code>），推测设备大概率发生了 MAC 类异常

各 BCM 线程异常退出/重启日志如下：

```shell
2022-02-16 01:27:59.712742 HOSTNAME <local2.err> ERR monit[661]: 'bcmCNTR' status failed (9) -- Thread bcmCNTR has exited abnormally. It is being restarted now.
2022-02-16 01:27:59.715515 HOSTNAME <local2.err> ERR monit[661]: 'bcmDPC' status failed (9) -- Thread bcmDPC has exited abnormally.
2022-02-16 01:27:59.716774 HOSTNAME <local2.err> ERR monit[661]: 'bcmINTR' status failed (9) -- Thread bcmINTR has exited abnormally.
2022-02-16 01:27:59.711377 HOSTNAME <local2.err> ERR monit[661]: 'bcmL2' status failed (9) -- Thread bcmL2X has exited abnormally. It is being restarted now.
2022-02-16 01:27:59.736919 HOSTNAME <local2.err> ERR monit[661]: 'bcmL2age' status failed (9) -- Thread bcmL2age has exited abnormally.
2022-02-16 01:27:59.714208 HOSTNAME <local2.err> ERR monit[661]: 'bcmLINK' status failed (9) -- Thread bcmLINK has exited abnormally. It is being restarted now.
2022-02-16 01:27:59.726623 HOSTNAME <local2.err> ERR monit[661]: 'bcmRX' status failed (9) -- Thread bcmRX has exited abnormally.
2022-02-16 01:27:59.722205 HOSTNAME <local2.err> ERR monit[661]: 'bcmTX' status failed (9) -- Thread bcmTX has exited abnormally.
2022-02-16 01:27:59.723675 HOSTNAME <local2.err> ERR monit[661]: 'bcmXGS3AsyncTX' status failed (9) -- Thread bcmXGS3AsyncTX has exited abnormally.
```

# 5. 系统类


## 5.1. 各容器启/停状态日志查询

<b><font color="red" style="">各容器启/停日志查看命令：</font></b><br>

```shell
sudo grep -i "${container_name} container" /var/log/daemon.log
```

### 5.1.1. snmp 容器

```shell
sudo grep -i "snmp container" /var/log/daemon.log | tail -n 20

## snmp 容器启动日志
2022-01-18 15:25:48.218932 sonic <daemon.info> INFO systemd[1]: Started SNMP container.

## snmp 容器停止日志
2022-01-18 15:25:19.641467 sonic <daemon.info> INFO systemd[1]: Stopped SNMP container.
```

### 5.1.2. lldp 容器

```shell
sudo grep -i "lldp container" /var/log/daemon.log | tail -n 20

## lldp 容器启动日志
2022-01-04 21:51:00.082042 sonic <daemon.info> INFO systemd[1]: Started LLDP container.

## lldp 容器停止日志
2022-01-04 21:50:29.080276 sonic <daemon.info> INFO systemd[1]: Stopped LLDP container.
```

### 5.1.3. teamd 容器

```shell
sudo grep -i "teamd container" /var/log/daemon.log | tail -n 20

## teamd 容器启动日志
2022-01-13 14:40:41.912032 sonic <daemon.info> INFO systemd[1]: Started TEAMD container.

## teamd 容器停止日志
2022-01-18 15:25:05.472610 sonic <daemon.info> INFO systemd[1]: Stopped TEAMD container.
```

### 5.1.4. bgp 容器

```shell
sudo grep -i "bgp container" /var/log/daemon.log | tail -n 20

## bgp 容器启动日志
2021-12-31 10:41:22.266584 sonic <daemon.info> INFO systemd[1]: Started BGP container.

## bgp 容器停止日志
2022-01-04 21:50:43.337088 sonic <daemon.info> INFO systemd[1]: Stopped BGP container.
```

### 5.1.5. database 容器

```shell
sudo grep -i "database container" /var/log/daemon.log | tail -n 20

## database 容器启动日志
2022-01-20 18:11:58.655729 sonic <daemon.info> INFO systemd[1]: Started Database container.

## database 容器停止日志
2021-12-23 18:07:52.612817 sonic <daemon.info> INFO systemd[1]: Stopped Database container.
```

### 5.1.6. radv 容器

```shell
sudo grep -i "radv container" /var/log/daemon.log | tail -n 20

## syncd 容器启动日志
2022-01-11 17:14:24.665014 sonic <daemon.info> INFO radv.sh[2148]: Starting existing radv container with HWSKU BT2575

##（无容器退出日志，暂监听radv容器里的 supervisor-proc-exit-script 停止日志代替）
sudo grep -a "radv" /var/log/syslog | grep "supervisor-proc-exit-script" | grep stop | tail -n 20

## radv 容器停止日志
2022-01-11 11:54:36.009347 sonic <local0.info> INFO radv#supervisord 2022-01-11 11:53:52,755 INFO stopped: supervisor-proc-exit-script (terminated by SIGTERM)
```

### 5.1.7. dhcp_relay 容器

```shell
sudo grep -i "dhcp_relay container" /var/log/daemon.log | tail -n 20

## dhcp_relay 容器启动日志（或启动一个已有容器）
2022-01-20 18:12:07.952541 sonic <daemon.info> INFO dhcp_relay.sh[3429]: Starting existing dhcp_relay container with HWSKU BT2575

## （无容器退出日志，暂监听dhcp_relay容器里的 supervisor-proc-exit-listener 停止日志代替）
sudo grep -a "dhcp_relay" /var/log/syslog | grep "supervisor-proc-exit-listener" | grep stop | tail -n 20

## dhcp_relay 容器停止日志
2022-01-11 11:54:38.304276 sonic <local0.info> INFO dhcp_relay#supervisord 2022-01-11 11:53:54,128 INFO stopped: supervisor-proc-exit-listener (terminated by SIGTERM)
```

### 5.1.8. syncd 容器

```shell
sudo grep -i "syncd container" /var/log/daemon.log | tail -n 20

## syncd 容器启动日志（创建一个新容器）
2021-12-22 22:49:20.897248 sonic <daemon.info> INFO syncd.sh[25671]: Creating new syncd container with HWSKU BT2575

## syncd 容器启动日志（或启动一个已有容器）
2022-01-20 18:12:06.333407 sonic <daemon.info> INFO syncd.sh[2920]: Starting existing syncd container with HWSKU BT2575

## 无容器退出日志，暂监听syncd容器里的 supervisor-proc-exit-listener 停止日志代替）
sudo grep -a "syncd" /var/log/syslog | grep "supervisor-proc-exit-listener" | grep stop | tail -n 20

## syncd 容器停止日志
2022-01-11 11:54:32.373488 sonic <local0.info> INFO syncd#supervisord 2022-01-11 11:53:48,949 INFO stopped: supervisor-proc-exit-listener (terminated by SIGTERM)
```

### 5.1.9. swss 容器

```shell
sudo grep -i "swss container" /var/log/daemon.log | tail -n 20

## swss 容器启动日志（创建一个新容器）
2022-01-11 17:13:16.747983 sonic <daemon.info> INFO swss.sh[28958]: Creating new swss container with HWSKU BT2575

## swss 容器启动日志（或启动一个已有容器）
2022-01-20 18:12:03.332602 sonic <daemon.info> INFO swss.sh[1950]: Starting existing swss container with HWSKU BT2575

## （无容器退出日志，暂监听swss容器里的 supervisor-proc-exit-listener 停止日志代替）
sudo grep -a "swss" /var/log/syslog | grep "supervisor-proc-exit-listener" | grep stop | tail -n 20

## swss 容器停止日志
2022-01-11 11:54:30.919836 sonic <local0.info> INFO swss#supervisord 2022-01-11 11:53:36,769 INFO stopped: supervisor-proc-exit-listener (terminated by SIGTERM)
```

### 5.1.10. pmon 容器

```shell
sudo grep -i "pmon container" /var/log/daemon.log | tail -n 20

## pmon 容器启动日志（创建一个新容器）
2021-12-22 22:51:57.133310 sonic <daemon.info> INFO pmon.sh[2522]: Creating new pmon container with HWSKU BT2575

## pmon 容器启动日志（或启动一个已有容器）
2022-01-20 18:12:01.562897 sonic <daemon.info> INFO pmon.sh[1944]: Starting existing pmon container with HWSKU BT2575

## （无标志，暂监听pmon容器里的 hwmgrd 停止日志代替）
sudo grep -a "pmon" /var/log/syslog | grep "hwmgrd" | grep stop | tail -n 20

## pmon 容器停止日志
2021-08-18 13:57:35.807813 <local0.info> sonic INFO pmon#supervisord 2021-08-18 05:57:19,661 INFO stopped: hwmgrd (terminated by SIGKILL)
```

### 5.1.11. mgmt-framework 容器
（暂未开启）
```shell
sudo grep -i "mgmt-framework container" /var/log/daemon.log | tail -n 20

## mgmt-framework 容器启动日志（创建一个新容器）
2021-07-15 16:13:55.808772 sonic <daemon.info> INFO mgmt-framework.sh[2766]: Creating new mgmt-framework container with HWSKU BT2575

## mgmt-framework 容器启动日志（或启动一个已有容器）
2021-07-20 16:21:08.207138 sonic <daemon.info> INFO mgmt-framework.sh[2812]: Starting existing mgmt-framework container with HWSKU BT2575

## （无容器退出日志，暂监听mgmt-framework容器里的 rsyslogd 停止日志代替）
sudo grep -a "mgmt-framework" /var/log/syslog | grep "rsyslogd" | grep stop | tail -n 20

## mgmt-framework 容器停止日志
2021-08-11 20:04:12.517360 sonic <local0.info> INFO mgmt-framework#supervisord 2021-08-11 12:02:59,842 INFO stopped: rsyslogd (exit status 0)
```

### 5.1.12. sflow 容器
（暂未开启）

```shell
sudo grep -i "sflow container" /var/log/daemon.log | tail -n 20

## sflow 容器启动日志
2021-08-17 22:14:23.550052 sonic <daemon.info> INFO systemd[1]: Started sFlow container.

## sflow 容器停止日志
2021-08-17 22:14:22.418637 sonic <daemon.info> INFO systemd[1]: Stopped sFlow container.
```

### 5.1.13. telemetry 容器
（暂未开启）

```shell
sudo grep -i "telemetry container" /var/log/daemon.log | tail -n 20

## telemetry 容器启动日志
2021-08-18 19:57:56.832442 sonic <daemon.info> INFO systemd[1]: Started Telemetry container.

## telemetry 容器停止日志
2021-08-18 19:57:55.668585 sonic <daemon.info> INFO systemd[1]: Stopped Telemetry container.
```

## 5.2. 各容器内各进程对应日志文件路径

<br><b><font color="#7E3D76" style="">各容器进程对应日志文件路径表如下：</font></b>

<table border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th>容器</th>
        <th>日志文件</th>
        <th>写日志的进程</th>
    </tr>
    <tr>
        <td align="center"  rowspan="3" >snmp</td>
        <td>/var/log/daemon.log</td>
        <td>snmp#snmp-subagent 进程运行日志<font color="red" style="">&lt;daemon.err/info/warning&gt;</font><br>snmp#snmpd进程 进程运行日志<font color="red" style="">&lt;daemon.warning&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/user.log</td>
        <td>snmp#supervisord 守护进程日志<font color="red" style="">&lt;user.info&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/syslog</td>
        <td>snmp#supervisord 守护进程日志<font color="red" style="">&lt;local0.info&gt;</font></td>
    </tr>
    <tr>
        <td align="center"  rowspan="4" >telemetry</td>
        <td>/var/log/daemon.log</td>
        <td>守护进程日志<font color="red" style="">&lt;daemon.info&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/telemetry.log</td>
        <td>telemetry 运行日志<font color="red" style="">&lt;user.info&gt;</font>,<font color="red" style="">&lt;daemon.info&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/user.log</td>
        <td>telemetry#supervisord 进程运行日志<font color="red" style="">&lt;user.info&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/syslog</td>
        <td>sonic systemd 日志<font color="red" style="">&lt;local0.info&gt;</font>,<font color="red" style="">&lt;local7.info&gt;</font></td>
    </tr>
    <tr>
        <td align="center"  rowspan="5" >lldp</td>
        <td>/var/log/daemon.log</td>
        <td>lldp#lldpd 进程运行日志<font color="red" style="">&lt;daemon.warning/info&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/user.log</td>
        <td>lldp#lldpmgrd 进程运行日志<font color="red" style="">&lt;user.err/warning/info/debug&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/syslog</td>
        <td>lldp#supervisord 日志<font color="red" style="">&lt;local0.info&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/messages</td>
        <td>start_module lldp 日志<font color="red" style="">&lt;local0.info/warning&gt;</font>,<font color="red" style="">&lt;local2.warning&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/running.log</td>
        <td>AUTOPROVISION pica_autoprovision 日志<font color="red" style="">&lt;local0.info/warning&gt;</font>,<font color="red" style="">&lt;local2.warning&gt;</font></td>
    </tr>
    <tr>
        <td align="center"  rowspan="3" >sflow</td>
        <td>/var/log/daemon.log</td>
        <td>sflow 容器运行日志<font color="red" style="">&lt;daemon.info&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/user.log</td>
        <td>sflow#supervisord 进程运行日志<font color="red" style="">&lt;user.info&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/syslog</td>
        <td>sflow#sflowmgrd 进程运行日志<font color="red" style="">&lt;local2.notice&gt;</font><br>sflow#supervisord 进程运行日志<font color="red" style="">&lt;local0.info&gt;</font></td>
    </tr>
    <tr>
        <td align="center"  rowspan="3" >radv</td>
        <td>/var/log/daemon.log</td>
        <td>radv 容器运行日志<font color="red" style="">&lt;daemon.info&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/user.log</td>
        <td>radv#supervisord 进程运行日志<font color="red" style="">&lt;user.info&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/syslog</td>
        <td>radv#supervisord 进程运行日志<font color="red" style="">&lt;local0.info&gt;</font></td>
    </tr>
    <tr>
        <td align="center"  rowspan="3" >dhcp_relay</td>
        <td>/var/log/daemon.log</td>
        <td>dhcp_relay 容器运行日志<font color="red" style="">&lt;daemon.info&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/user.log</td>
        <td>dhcp_relay#supervisord 进程运行日志<font color="red" style="">&lt;user.info&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/syslog</td>
        <td>dhcp_relay#supervisord 进程运行日志<font color="red" style="">&lt;local0.info&gt;</font></td>
    </tr>
    <tr>
        <td align="center"  rowspan="3" >syncd</td>
        <td>/var/log/daemon.log</td>
        <td>syncd 容器运行日志<font color="red" style="">&lt;daemon.info&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/user.log</td>
        <td>syncd#syncd 进程运行日志<font color="red" style="">&lt;user.info/debug&gt;</font><br>syncd#supervisord 进程运行日志<font color="red" style="">&lt;user.info&gt;</font><br>syncd#dsserve 进程运行日志<font color="red" style="">&lt;user.notice&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/syslog</td>
        <td>syncd#syncd 进程运行日志<font color="red" style="">&lt;local2.err/warning/debug/notice&gt;</font><br>syncd#supervisord 进程运行日志<font color="red" style="">&lt;local0.info&gt;</font></td>
    </tr>
    <tr>
        <td align="center"  rowspan="4" >teamd</td>
        <td>/var/log/daemon.log</td>
        <td>teamd 容器运行日志<font color="red" style="">&lt;daemon.info&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/teamd.log</td>
        <td>teamd#teamd_PortChannel* 进程运行日志<font color="red" style="">&lt;daemon.debug&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/user.log</td>
        <td>teamd#supervisord 进程运行日志<font color="red" style="">&lt;user.info&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/syslog</td>
        <td>teamd#supervisord 进程运行日志<font color="red" style="">&lt;local0.info&gt;</font><br>teamd#teamsyncd/teammgrd 进程运行日志<font color="red" style="">&lt;local2.err/notice&gt;</font></td>
    </tr>
    <tr>
        <td align="center"  rowspan="3" >mgmt-framework</td>
        <td>/var/log/daemon.log</td>
        <td>mgmt-framework 容器运行日志<font color="red" style="">&lt;daemon.info&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/user.log</td>
        <td>mgmt-framework#supervisord 进程运行日志<font color="red" style="">&lt;user.info&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/syslog</td>
        <td>mgmt-framework#supervisord 进程运行日志<font color="red" style="">&lt;local0.info&gt;</font></td>
    </tr>
    <tr>
        <td align="center"  rowspan="3" >swss</td>
        <td>/var/log/daemon.log</td>
        <td>swss 容器运行日志<font color="red" style="">&lt;daemon.info&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/user.log</td>
        <td>swss#intmgrd/restore_neighbor/supervisor-proc-exit-listener 进程运行日志<font color="red" style="">&lt;user.err/info&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/syslog</td>
        <td>swss#orchagent/portsyncd/neighsyncd/vrfmgrd/vxlanmgrd/switchmgrd/<br>fdbmgrd/cfgmgrd/intmgrd/transmgrd 进程运行日志<font color="red" style="">&lt;local0/local2.err/warning/notice&gt;</font></td>
    </tr>
    <tr>
        <td align="center"  rowspan="3" >pmon</td>
        <td>/var/log/daemon.log</td>
        <td>pmon 容器运行日志<font color="red" style="">&lt;daemon.info&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/user.log</td>
        <td>pmon#supervisord 进程运行日志<font color="red" style="">&lt;user.info&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/syslog</td>
        <td>pmon#supervisord 进程运行日志<font color="red" style="">&lt;local0.info&gt;</font><br>pmon#hwmgrd 进程运行日志<font color="red" style="">&lt;local2.err/info&gt;</font></td>
    </tr>
    <tr>
        <td align="center"  rowspan="7" >bgp</td>
        <td>/var/log/daemon.log</td>
        <td>bgp 容器运行日志<font color="red" style="">&lt;daemon.info&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/quagga/bgpd.log</td>
        <td>bgp#bgpd 进程运行日志<font color="red" style="">&lt;local2.err/warning/info&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/quagga/zebra.log</td>
        <td>bgp#zebra 进程运行日志<font color="red" style="">&lt;local2.err/warning/notice&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/user.log</td>
        <td>bgp#bgpcfgd 进程运行日志<font color="red" style="">&lt;user.info&gt;</font><br>bgp#supervisord 进程运行日志<font color="red" style="">&lt;user.info&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/messages</td>
        <td>BGP xorp_bgp 运行日志<font color="red" style="">&lt;local2.err/warning&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/running.log</td>
        <td>RTRMGR xorp_rtrmgr 启动日志<font color="red" style="">&lt;local0.info&gt;</font><br>BGP xorp_bgp 运行日志<font color="red" style="">&lt;local2.err/info&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/syslog</td>
        <td>bgp#fpmsyncd/monitorlinkd/staticd 进程运行日志<font color="red" style="">&lt;local2.err/warning/notice&gt;</font>,<font color="red" style="">&lt;local7.info&gt;</font><br>bgp#supervisord 守护进程日志<font color="red" style="">&lt;local0.info&gt;</font> </td>
    </tr>
    <tr>
        <td align="center"  rowspan="5" >database</td>
        <td>/var/log/daemon.log</td>
        <td>database 容器运行日志<font color="red" style="">&lt;daemon.info&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/user.log</td>
        <td> database 容器运行日志<font color="red" style="">&lt;user.notice&gt;</font><br>database#supervisord 守护进程日志<font color="red" style="">&lt;user.info&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/syslog</td>
        <td>database#supervisord 进程运行日志<font color="red" style="">&lt;local0.info&gt;</font></td>
    </tr>
    <tr>
        <td>/var/log/messages</td>
        <td>WARMBOOT_FINALIZER 等待日志</td>
    </tr>
    <tr>
        <td>/var/log/running.log</td>
        <td>WARMBOOT_FINALIZER 等待日志</td>
    </tr>
</table>

### 5.2.1. snmp 容器

日志文件：
- /var/log/daemon.log     （snmp\#snmp-subagent 进程运行日志<daemon.err/info/warning>；snmp#snmpd进程 进程运行日志<daemon.warning>）
- /var/log/user.log       （snmp\#supervisord守护进程日志<user.info>）
- /var/log/syslog         （snmp\#supervisord守护进程日志<local0.info>）

<b><font color="#7E3D76" style="">【1】snmp#snmpd进程</font></b>

- /var/log/daemon.log

<b><font color="#7E3D76" style="">【2】snmp\#snmp-subagent 进程</font></b>

- /var/log/daemon.log

<b><font color="#7E3D76" style="">【3】snmp\#supervisord 进程</font></b>

- /var/log/user.log
- /var/log/syslog

### 5.2.2. telemetry 容器

日志文件：
- /var/log/daemon.log     （守护进程日志<daemon.info>）
- /var/log/telemetry.log  （telemetry 运行日志<user.info>,<daemon.info>）
- /var/log/user.log       （telemetry\#supervisord 进程运行日志<user.info>）
- /var/log/syslog         （sonic systemd日志<local0.info>,<local7.info>）

<b><font color="#7E3D76" style="">【1】telemetry\#supervisord 进程</font></b>

- /var/log/user.log
- /var/log/telemetry.log

### 5.2.3. lldp 容器

日志文件：
- /var/log/daemon.log         （lldp\#lldpd 进程运行日志<daemon.warning/info>）
- /var/log/user.log           （lldp\#lldpmgrd 进程运行日志<user.err/warning/info/debug>）
- /var/log/syslog             （lldp\#supervisord 日志<local0.info>）
- /var/log/messages           （start_module lldp日志<local0.info/warning>,<local2.warning>）
- /var/log/running.log        （AUTOPROVISION pica_autoprovision日志<local0.info/warning>,<local2.warning>）

<b><font color="#7E3D76" style="">【1】lldp\#lldpmgrd 进程</font></b>

- /var/log/user.log

<b><font color="#7E3D76" style="">【2】lldp\#lldpd 进程</font></b>

- /var/log/daemon.log

<b><font color="#7E3D76" style="">【3】lldp\#supervisord 进程</font></b>

- /var/log/syslog

### 5.2.4. sflow 容器

日志文件：
- /var/log/daemon.log         （sflow容器运行日志<daemon.info>）
- /var/log/user.log           （sflow\#supervisord 进程运行日志<user.info>）
- /var/log/syslog             （sflow\#sflowmgrd 进程运行日志<local2.notice>；sflow\#supervisord 进程运行日志<local0.info>）

<b><font color="#7E3D76" style="">【1】sflow\#sflowmgrd 进程</font></b>

- /var/log/syslog

<b><font color="#7E3D76" style="">【2】sflow\#supervisord 进程</font></b>

- /var/log/user.log
- /var/log/syslog

### 5.2.5. radv 容器

日志文件：
- /var/log/user.log       （radv\#supervisord运行日志<user.info>）
- /var/log/syslog         （radv\#supervisord运行日志<local0.info>）
- /var/log/daemon.log     （radv容器运行日志<daemon.info>）

<b><font color="#7E3D76" style="">【1】radv\#supervisord 进程</font></b>

- /var/log/user.log
- /var/log/syslog

### 5.2.6. dhcp_relay 容器

日志文件：
- /var/log/user.log       （dhcp_relay\#supervisord 进程运行日志<user.info>）
- /var/log/daemon.log     （dhcp_relay容器运行日志<daemon.info>）
- /var/log/syslog         （dhcp_relay\#supervisord 进程运行日志<local0.info>）

<b><font color="#7E3D76" style="">【1】dhcp_relay\#supervisord 进程</font></b>

- /var/log/user.log
- /var/log/syslog

### 5.2.7. syncd 容器

日志文件：
- /var/log/user.log       （syncd\#syncd 进程运行日志<user.info/debug>；syncd\#supervisord 进程运行日志<user.info>；syncd\#dsserve 进程运行日志<user.notice>）
- /var/log/daemon.log     （syncd容器运行日志<daemon.info>）
- /var/log/syslog         （syncd\#syncd 进程运行日志<local2.*>；syncd\#supervisord 进程运行日志<local0.info>）

<b><font color="#7E3D76" style="">【1】syncd\#syncd 进程</font></b>

- /var/log/user.log
- /var/log/syslog

<b><font color="#7E3D76" style="">【2】syncd\#dsserve 进程</font></b>

- /var/log/user.log

<b><font color="#7E3D76" style="">【3】syncd\#supervisord 进程</font></b>

- /var/log/user.log
- /var/log/syslog

### 5.2.8. teamd 容器

日志文件：
- /var/log/teamd.log      （teamd\#teamd_PortChannel\* 进程运行日志<daemon.debug>）
- /var/log/user.log       （teamd\#supervisord 进程运行日志<user.info>）
- /var/log/daemon.log     （teamd 容器运行日志<daemon.info>）
- /var/log/syslog         （teamd\#supervisord 进程运行日志<local0.info>；teamd\#teamsyncd/teammgrd进程运行日志<local2.err/notice>）

<b><font color="#7E3D76" style="">【1】teamd\#teamd_PortChannel\* 进程</font></b>

- /var/log/teamd.log

<b><font color="#7E3D76" style="">【2】teamd\#teamsyncd/teammgrd 进程</font></b>

- /var/log/syslog

<b><font color="#7E3D76" style="">【3】teamd\#supervisord 进程</font></b>

- /var/log/user.log
- /var/log/syslog

### 5.2.9. mgmt-framework 容器

日志文件：
- /var/log/user.log       （mgmt-framework\#supervisord 进程运行日志<user.info>）
- /var/log/daemon.log     （mgmt-framework 容器运行日志，<daemon.info>）
- /var/log/syslog         （mgmt-framework\#supervisord 进程运行日志<local0.info>）

<b><font color="#7E3D76" style="">【1】mgmt-framework\#supervisord 进程</font></b>

- /var/log/user.log
- /var/log/syslog

### 5.2.10. swss 容器

日志文件：
- /var/log/user.log           （swss\#intmgrd/restore_neighbor/supervisor-proc-exit-listener 进程运行日志<user.*>）
- /var/log/daemon.log         （swss 容器运行日志<daemon.info>）
- /var/log/syslog             （swss\#orchagent/portsyncd/neighsyncd/vrfmgrd/vxlanmgrd/switchmgrd/fdbmgrd/cfgmgrd/intmgrd/transmgrd 进程运行日志<local0/local2.err/warning/notice>）

<b><font color="#7E3D76" style="">【1】swss\#intmgrd/restore_neighbor/supervisor-proc-exit-listener 进程</font></b>

- /var/log/user.log

<b><font color="#7E3D76" style="">【2】swss\#orchagent/portsyncd/neighsyncd/vrfmgrd/vxlanmgrd/switchmgrd/fdbmgrd/cfgmgrd/intmgrd/transmgrd 进程</font></b>

- /var/log/syslog

<b><font color="#7E3D76" style="">【3】swss\#supervisord 进程</font></b>

- /var/log/user.log
- /var/log/syslog

### 5.2.11. pmon 容器

日志文件：
- /var/log/user.log       （pmon\#supervisord 进程运行日志，<user.info>）
- /var/log/daemon.log     （pmon容器运行日志，<daemon.info>）
- /var/log/syslog         （pmon\#supervisord 进程运行日志，<local0.info>；pmon\#hwmgrd 进程运行日志<local2.info/err>）

<b><font color="#7E3D76" style="">【1】pmon\#hwmgrd 进程</font></b>

- /var/log/syslog

<b><font color="#7E3D76" style="">【2】pmon\#supervisord 进程</font></b>

- /var/log/syslog
- /var/log/user.log

### 5.2.12. bgp 容器

日志文件：
- /var/log/quagga/bgpd.log        （bgp\#bgpd 进程运行日志<local2.err/info/warning>）
- /var/log/quagga/zebra.log       （bgp\#zebra 进程运行日志<local2.err/warning/notice>）
- /var/log/user.log               （bgp\#bgpcfgd 进程运行日志<user.info>；bgp\#supervisord 进程运行日志<user.info>）
- /var/log/daemon.log             （bgp 容器运行日志<daemon.info>）
- /var/log/messages               （BGP xorp_bgp 运行日志<local2.err/warning>）
- /var/log/running.log            （RTRMGR xorp_rtrmgr 启动日志<local0.info>；BGP xorp_bgp 运行日志<local2.err/info>）
- /var/log/syslog                 （bgp\#fpmsyncd/liblogging-stdlog/monitorlinkd/staticd 进程运行日志<local2.err/warning/notice>,<local7.info>；bgp\#supervisord守护进程日志<local0.info> ）

<b><font color="#7E3D76" style="">【1】bgp\#bgpd 进程</font></b>

- /var/log/quagga/bgpd.log

<b><font color="#7E3D76" style="">【2】bgp\#zebra 进程</font></b>

- /var/log/quagga/zebra.log

<b><font color="#7E3D76" style="">【3】bgp\#bgpcfgd 进程</font></b>

- /var/log/user.log

<b><font color="#7E3D76" style="">【4】bgp\#fpmsyncd/liblogging-stdlog/monitorlinkd/staticd 进程</font></b>

- /var/log/syslog

<b><font color="#7E3D76" style="">【5】bgp\#supervisord 进程</font></b>

- /var/log/user.log
- /var/log/syslog

### 5.2.13. database 容器

日志文件：
- /var/log/user.log       （ database 容器运行日志<user.notice>；database\#supervisord守护进程日志<user.info>）
- /var/log/daemon.log     （database容器运行日志，<daemon.info>）
- /var/log/messages       （WARMBOOT_FINALIZER 等待日志）
- /var/log/running.log    （WARMBOOT_FINALIZER 等待日志）
- /var/log/syslog         （database\#supervisord 进程运行日志，<local0.info>）

<b><font color="#7E3D76" style="">【1】database\#supervisord 进程</font></b>

- /var/log/user.log
- /var/log/syslog


## 5.3. 系统 Crash

思考点：譬如内核异常，不会直接输出日志


