layout: post
title: Syslog 模块的故障自检方法及常见已知问题
date: 2021/8/24 22:30:45
updated: 2021/8/23 23:10:45
comments: true
tags:
- syslog
categories:
- 技术

---

Rsyslog 版本：8.24.0

# 1. 故障自检方法

## 1.1. 无日志输出
**现象**：

目标进程的预期日志文件无日志写入， <code>tail -f</code> 未检测到日志写入流

<!-- more -->

```shell
sudo tail -f /var/log/syslog
```

### 1.1.1. 可能原因 1：目标进程未启动或异常
自检方法：排查目标进程运行状态，或结合进程自身特性判断

```shell
#  检查业务进程是否正常运行（eg. swss 容器中的 fdbmgrd 进程 ）
docker exec -it swss ps -ef | grep -v "grep" | grep "fdbmgrd"
```

### 1.1.2. 可能原因 2：Rsyslog 未启动

**可能原因 2-1**：

系统日志软件 Rsyslog 进程被 Kill

自检方法：检查 Rsyslog 是否运行

```shell
# 1. 检查交换机中 Rsyslog 是否运行
ps -ef | grep -v "grep" | grep "rsyslogd"

# 2. 检查对应容器（eg. swss）中 Rsyslog 是否运行
docker exec -it swss ps -ef | grep rsyslogd
```

**可能原因 2-2**：

Rsyslog 的自身配置文件 <code>/etc/rsyslog.conf</code> 或自定义配置文件夹下 <code>/etc/rsyslog.d/</code> 的配置有错，导致 Rsyslog 启动失败

自检方法：对照正常设备的配置

### 1.1.3. 可能原因 3：无程序打开目标日志文件
自检方法：查看是否有进程打开目标日志文件（eg. <code>/var/log/syslog</code>）

```shell
# 检查有无进程“打开了”目标日志文件
sudo lsof /var/log/syslog
```
一般情况如下：

```shell
COMMAND   PID USER   FD   TYPE DEVICE SIZE/OFF NODE NAME
rsyslogd 2181 root    8w   REG    8,3 57735831   56 /var/log/syslog
```

### 1.1.4. 可能原因 4： 日志输出限制级别设定过高
自检方法：通过 swssloglevel 或 logctl 命令检查日志输出限制级别是否过高

```shell
# 查看当前日志输出限制级别
swssloglevel -p | grep fdbmgrd
# 或
logctl -p -c swss#fdbmgrd
```

**应对方法**：

- 更改输出限制级别

```shell
# 降低目标进程（eg. fdbmgrd）日志输出限制级别
swssloglevel -l INFO -c fdbmgrd
# 或
logctl -l INFO -c swss#fdbmgrd
```
备注：查看更改日志输出限制级别用法

```shell
swssloglevel -h
# 或
logctl -h
```

## 1.2. 日志文件无法轮转，无限制增长
**现象**：

日志文件无限制增长，超过轮转阈值，却未被轮转压缩

### 1.2.1. 可能原因 1：logrotate 配置异常

自检方法：排查 logrotate 配置

```shell
# 1. 检查有无安装 logrotate
sudo which logrotate
# 或
ls -l /usr/sbin/logrotate

# 2. 检查 logrotate 自身配置（对照正常设备配置）
cat /etc/logrotate.conf

# 3. 检查有无对目标日志文件的轮转配置（eg. "daemon.log"）
grep -A 5 "daemon.log" /etc/logrotate.d/rsyslog
# 或
grep -A 5 -Rw "daemon.log" /etc/logrotate.d/

# 4. 模拟执行以验证目标文件的轮转配置的正确性（"-d", 不会真正执行日志轮转）
/usr/sbin/logrotate -d /etc/logrotate.d/rsyslog 2>&1 | grep -A 5 "daemon.log"
```

### 1.2.2. 可能原因 2：cron 配置异常

> logrotate 日志轮转依赖于被定时任务工具 cron 周期调起

自检方法：排查 cron 配置

```shell
# 1. 检查 cron 配置（对照正常设备配置）
cat /etc/crontab

# 2. 检查 cron 周期性调起 logrotate 的配置（对照正常设备配置）
cat /etc/cron.d/logrotate
# 或
cat /etc/cron.daily/logrotate

# 3. 检查定时任务 cron 是否启动
ps -ef | grep -v "grep" | grep "cron"

# 4. 检查有无 cron 成功调起 logrotate 的日志（当前调起周期为十分钟）
sudo grep "logrotate" /var/log/cron.log | tail -n 5
```

## 1.3. 轮转后新文件不记日志
**现象**：

日志文件大小为 0，已自检不是“1.1. 无输出日志”的问题
### 1.3.1. 可能原因：Rsyslog 未收到 HUP 信号

> 日志轮转工具 logrotate 在轮转 <code>xxx.log</code> 文件后，理应给 Rsyslog 发 HUP 挂起信号，以使 Rsyslog 进程能够重新加载 新的 <code>xxx.log</code> 文件的（文件 inode 号变更）进行记日志。

Rsyslog 未收到 HUP 信号，其仍根据旧 inode 向不存在的前 <code>xxx.log</code> 写日志。

自检方法：检查该日志文件对应的 lorotate 轮转配置文件（eg.  <code>/etc/logrotate.d/rsyslog</code> ），确保 postrotate 执行块内，存在向 Rsyslog 发送 HUP 信号的操作

```shell
postrotate
    /bin/kill -HUP $(cat /var/run/rsyslogd.pid) 2>/dev/null || true
endscript
```

# 2. 常见已知问题

## 2.1. 高速刷日志时突然停止输出
**现象**：

短时输出大量日志时突然无征兆中断输出，5 分钟后日志又恢复输出，循环往复，导致日志呈现周期性断续输出现象

**根因**：

日志吞吐量过高时，会触发容器中 Rsyslog 配置的“熔断”值（2 万条/每 5 分钟），此时容器中 Rsyslog 会停止转发日志消息到宿主机 Rsyslog，故宿主机端观检测不到日志输出。不过，进入下一 5 分钟周期计数清零后，日志又恢复输出。

注意：“熔断”期间的输出日志会丢失。

自检方法：查看目标容器（eg. bgp）中的 Rsyslog 配置文件 <code>/etc/rsyslog.conf</code>

```shell
docker exec -it bgp grep -C 2 "SystemLogRateLimitInterval" /etc/rsyslog.conf
```

默认配置如下：

```shell
# Set a rate limit on messages from the container
#
$SystemLogRateLimitInterval 300
$SystemLogRateLimitBurst 20000
```

**应对方法**：
- 更参考1.1.4改日志输出的级别，以降低日志输出速率
- 临时调高 Rsyslog 配置的“熔断”值

```shell
# 修改目标容器（eg. bgp）中 Rsyslog 的“熔断”配置值
docker exec -it bgp sed -i 's/SystemLogRateLimitBurst [0-9]\+/SystemLogRateLimitBurst 30000/g' /etc/rsyslog.conf

# 重启目标容器（eg. bgp）中的 Rsyslog 服务以生效配置
docker exec -it bgp service rsyslog restart
```

## 2.2. Rsyslog 收到 HUP 信号
**现象**：

Rsyslog 收到 HUP 信号并输出下方的 INFO 级别日志。

```shell
2021-10-16 03:50:01.212971 HOSTNAMR <local7.info> INFO liblogging-stdlog:  [origin software="rsyslogd" swVersion="8.24.0" x-pid="1732" x-info="http://www.rsyslog.com"] rsyslogd was HUPed
```

**根因**：

符合预期的正常情况。当日志文件发生轮转时，Rsyslog 会收到 logrotate 发送的 HUP 信号，重新加载文件，包括停止往已改名的“准轮转文件”写日志，而是写日志到新建的一个同名文件中。

## 2.3. Rsyslog 折叠重复日志
**现象**：

Rsyslog 输出下方的折叠日志

```shell
2021-10-27 15:57:44.222512 HOSTNAMR <local2.err> ERR swss#orchagent: message repeated 1636 times: [ :- doTask: op: SET, key: vlan23:8.1.1.2]
```

**根因**：

出现 <code>message repeated 1636 times</code> ，是由于容器中的 Rsyslog 开启了“减少重复日志” 开关（默认开启），以避免一千多行重复冗余日志转发的性能消耗，是符合预期的正常情况。

自检方法：查看目标容器（eg. bgp）中的 Rsyslog 配置文件 <code>/etc/rsyslog.conf</code>

```shell
docker exec -it bgp grep -B 2 "RepeatedMsgReduction" /etc/rsyslog.conf
```
默认配置如下：

```shell
# Suppress duplicate messages and report "message repeated n times"
#
$RepeatedMsgReduction on
```

## 2.4. Rsyslog 打印 2354 标识
**现象**：

Rsyslog 输出下方日志

```shell
2021-09-26 11:20:58.668466 HOSTNAMR <local7.err> ERR liblogging-stdlog: omfwd: error 11 sending via udp: Resource temporarily unavailable [v8.24.0 try http://www.rsyslog.com/e/2354 ]

2022-02-10 10:16:31.392826 HOSTNAMR <local7.err> ERR liblogging-stdlog: omfwd: error 101 sending via udp: Network is unreachable [v8.24.0 try http://www.rsyslog.com/e/2354 ]
```

Rsyslog 打[2354 标识日志](https://www.rsyslog.com/rsyslog-error-2354/)表明很可能是**系统的 UDP 缓冲区空间不足**。

（注：旧版本（如 8.24）也无法发送接近或大于 64KiB 的日志消息）

**根因**：

系统的 UDP 缓冲区空间不足。还需监控系统的 UDP 缓存区占用情况来定位是哪些组件占用较大（可参考：[监控 UDP buffer 可用空间](https://stackoverflow.com/questions/2289830/how-to-monitor-linux-udp-buffer-available-space)）

## 2.5. Rsyslog 打印 2359 标识
**现象**：

Rsyslog 输出下方日志

```shell
2021-09-26 10:35:02.802106 HOSTNAMR <local7.info> INFO liblogging-stdlog: action 'action 0' resumed (module 'builtin:omfwd') [v8.24.0 try http://www.rsyslog.com/e/2359 ]
```
**根因**：

Rsyslog 恢复服务的提示日志，[2359 标识](http://www.rsyslog.com/e/2359) 表示 之前由于重连到服务器或资源不再紧缺时暂停的操作现已恢复执行，符合预期无需处理。

## 2.6. Rsyslog 打印 2007 标识
**现象：**
Rsyslog 输出下方日志

```shell
2022-05-06 15:30:34.575869 HOSTNAMR <local7.warning> WARNING liblogging-stdlog: action 'action 0' suspended, next retry is Fri May  6 15:31:04 2022 [v8.24.0 try http://www.rsyslog.com/e/2007 ]
```
**根因**：
[2007 标识](https://www.rsyslog.com/rsyslog-error-2007/)的常见原因为 Rsyslog 配置中包含向不可达组件写日志的错误配置，如配置了不可达的远程日志服务器，将导致输出大量2007标识的告警信息。

**解决方法**：
删除/注释错误的远程日志服务器配置后重启rsyslog服务。
## 2.7. 无 Redis 自身运行日志
**现象**：

未记录 Database 中 Redis 的相关运行日志

**根因**：

Database 容器里的 redis 配置中，默认未配置日志输出

自检方法：查看 Redis 配置文件 <code>/etc/redis/redis.conf</code>

```shell
docker exec -it database grep -B 2 "syslog-enable" /etc/redis/redis.conf
```
默认配置如下：

```shell
# To enable logging to the system logger, just set 'syslog-enabled' to yes,
# and optionally update the other syslog parameters to suit your needs.
syslog-enabled no
```

**应对方法**：
- 修改 Redis 配置文件，添加日志输出配置，并重启 Redis 以生效（不建议线上设备执行此操作）

```shell
# 1. 备份原配置
docker exec -it database cp /etc/redis/redis.conf /etc/redis/redis.conf_bak
# 查看备份文件
docker exec -it database ls -l /etc/redis/redis.conf_bak

# 2. 添加 Redis 输出日志路径配置
docker exec -it database sed -i 's;logfile \"\";logfile \"/var/log/redis/redis.log\";g' /etc/redis/redis.conf

# 3. 添加 Redis 输出日志 ident 配置
docker exec -it database sed -i 's;# syslog-ident redis;syslog-ident redis;g' /etc/redis/redis.conf

# 4. 添加 Redis 输出日志 facility 配置
docker exec -it database sed -i 's;# syslog-facility local0;syslog-facility local0;g' /etc/redis/redis.conf

# 5. 打开 Redis 输出日志开关配置
docker exec -it database sed -i 's;syslog-enabled no;syslog-enabled yes;g' /etc/redis/redis.conf

# 6. 停启 Database 容器以生效配置
docker stop database; docker start database
```

- redis-cli 虽然也支持热修改部分日志配置，但不支持热修改开启/关闭日志输出

```shell
# 1. 热修改 Redis 输出日志路径配置
redis-cli -h 127.0.0.1 -p 6379 CONFIG SET logfile "/var/log/redis/redis.log"
# 检查变更
redis-cli -h 127.0.0.1 -p 6379 CONFIG GET logfile

# 2. 热修改 Redis 输出日志 facility 配置（支持八种 facility 属性：user、local0 ~ local7）
redis-cli -h 127.0.0.1 -p 6379 CONFIG SET syslog-facility "local0"
# 检查变更
redis-cli -h 127.0.0.1 -p 6379 CONFIG GET syslog-facility

# 3. 热修改 Redis 输出日志 loglevel 配置（支持四种级别：debug、verbose、notice、warning）
redis-cli -h 127.0.0.1 -p 6379 CONFIG SET loglevel "warning"
# 检查变更
redis-cli -h 127.0.0.1 -p 6379 CONFIG GET loglevel
```

## 2.8. 修改 Rsyslog 配置文件后未生效？
修改 Rsyslog 配置文件后，需要重启服务以生效配置

```shell
sudo service rsyslog restart
```

## 2.9. 一条日志能够重定向到多个日志文件么？
可以，在 Rsyslog 配置中（<code>/etc/rsyslog.d/00-HOSTNAMR.conf</code>），若 syslog 消息匹配了多条自定义重定向（引流）规则（且规则执行块内无结束匹配关键字 stop），就能实现输出单条日志到多个文件

多条自定义重定向（引流）单日志到多个文件如下：
1. 在配置文件 <code>/etc/rsyslog.d/00-HOSTNAMR.conf</code> 中添加两条自定义重定向（引流）规则

```shell
## test rule1
if $msg contains "ABC" then {
    /var/log/abc.log
}

## test rule2
if $msg contains "DEF" then {
    /var/log/def.log
}
```

2. 模拟发送一个 syslog 消息

```shell
logger -p local5.info "ABC DEF TEST1"
```

3. 可发现两个重定向（引流）日志文件都记录了该日志

```shell
2021-12-29 15:14:18.698602 HOSTNAMR <local.info> INFO admin: ABC DEF TEST1
```

## 2.10. Rsyslog 支持修改日志的 facility 么？
问题补充描述：程序打 local0 的日志，能否让 Rsyslog 在写日志文件时改为 local2 ？

暂不支持，截止官网 8.2112.0 版本，Rsyslog 暂不支持修改日志 facility 的操作；网上也没有成功修改案例。

虽然 Rsyslog 支持的“读已有日志文件并按行转发”功能中支持指定日志 facility，理论上存在“引流 local0 日志 ==> 指定文件 ==> 读文件转成 syslog 消息（指定 local2）”这种可能，但这种方式**不具备可行性**：
- 首先是这种“二次转发”的日志会存在**冗余消息前缀**，如

```shell
# 原始日志
2021-12-29 17:20:51.653444 HOSTNAMR <local0.info> INFO admin: ABC DEF TEST5

# 二次转发日志：二次转发的日志前缀（时间戳 2 local2 级别 2 设备属性 2） + 原始日志前缀（时间戳 1 local0 级别 1 设备属性 1）+ 原始消息正文
2021-12-29 17:20:52.703466 HOSTNAMR <local2.notice> NOTICE testinput 2021-12-29 17:20:51.653444 HOSTNAMR <local0.info> INFO admin: ABC DEF TEST5
```
- 其次，这种打日志后再读文件二次转发方式，由于写入文件与读文件二次转发逻辑问题，一条日志很容易陷入被**无限打印循环**

## 2.11. 获知程序对应的日志路径？
由于 Rsyslog 主要基于程序打日志的 facility、或少量自定义的重定向（引流）规则明确记日志的文件 <code>/etc/rsyslog.d/00-HOSTNAMR.conf</code> ，故暂无进程与日志文件的明确对应关系。不过依然可以参考下方两种方式获知进程的日志文件路径：
- 方法 1：查看梳理的各容器启停日志及各进程输出日志
- 方法 2：手动检索 <code>/var/log/</code> 目录（检索字段：容器名#进程名）

```shell
sudo grep -Rw "swss#fdbmgrd" /var/log/ | awk '{ print $1 }' | uniq | sort | uniq

# 运行示例
/var/log/auth.log:2022-01-30
/var/log/syslog:2022-01-30
```

## 2.12. 日志服务器未收到上报日志？
咱们的日志上报是CS架构，下方任一原因都可能导致日志服务器无法收到日志：

**设备端：**
- Rsyslog 服务未运行？检查命令：

```shell
sudo systemctl status rsyslog | grep Active
```
- 设备上是否配置 远程日志服务器IP 检查命令：

```shell
grep -A 2 'remote syslog server' /etc/rsyslog.conf
```
- 日志服务器不可达？检查命令：

```shell
ping $(grep -A 1 'remote syslog server' /etc/rsyslog.conf  | tail -n +2)
```
- 防火墙 配置？514 端口未打开？检查命令：

```shell
sudo iptables -L -n
sudo lsof -i:514
```
- 设备无异常日志输出？ 检查命令：

```shell
sudo grep -E 'NOTICE|WARNING|ERROR' /var/log/syslog | grep local2 | tail -20
```

**日志服务器端：**
- Rsyslog 服务未运行？检查命令：

```shell
sudo systemctl status rsyslog | grep Active
```
- 防火墙 配置？514 端口未打开？检查命令：

```shell
sudo iptables -L -n
sudo lsof -i:514
```
- Rsyslog 配置中 $UDPServerAddress 127.0.0.1 被打开了？服务器端需注释，否则只能接收本地日志检查命令：

```shell
grep 'UDPServerAddress' /etc/rsyslog.conf
```
- 服务器端配置了日志全转发？ 检查命令：

```shell
grep -A 2 'remote syslog server' /etc/rsyslog.conf
```

