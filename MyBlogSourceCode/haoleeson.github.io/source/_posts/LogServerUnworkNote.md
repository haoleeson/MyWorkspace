layout: post
title: 日志服务器未收到日志可能原因小记
date: 2021/8/27 22:30:45
updated: 2021/8/27 23:10:45
comments: true
tags:
- syslog
categories:
- 技术

---

咱们的日志上报是CS架构，下方任一原因都可能导致日志服务器无法收到日志：

**设备端：**
- Rsyslog 服务未运行？（检查指令）
```shell
sudo systemctl status rsyslog | grep Active
```

<!-- more -->

- 设备上是否配置 远程日志服务器IP （检查指令）
```shell
grep -A 2 'remote syslog server' /etc/rsyslog.conf
```
- 日志服务器不可达？（检查指令）
```shell
ping $(grep -A 1 'remote syslog server' /etc/rsyslog.conf  | tail -n +2)
```
- 防火墙 配置？514 端口未打开？（检查指令）
```shell
sudo iptables -L -n
sudo lsof -i:514
```
- 设备无异常日志输出？ （检查指令）
```shell
sudo grep -E 'NOTICE|WARNING|ERROR' /var/log/syslog | grep local2 | tail -20
```

**日志服务器端：**
- Rsyslog 服务未运行？（检查指令）
```shell
sudo systemctl status rsyslog | grep Active
```
- 防火墙 配置？514 端口未打开？（检查指令）
```shell
sudo iptables -L -n
sudo lsof -i:514
```
- Rsyslog 配置中 $UDPServerAddress 127.0.0.1 被打开了？服务器端需注释，否则只能接收本地日志（检查指令）
```shell
grep 'UDPServerAddress' /etc/rsyslog.conf
```
- 服务器端配置了日志全转发？ （检查指令）
```shell
grep -A 2 'remote syslog server' /etc/rsyslog.conf
```

