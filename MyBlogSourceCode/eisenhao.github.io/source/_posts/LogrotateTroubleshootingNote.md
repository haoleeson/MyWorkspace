layout: post
title: logrotate 日志轮转未生效排障思路总结
date: 2021/9/3 22:30:45
updated: 2021/9/3 23:10:45
comments: true
tags: 
- syslog
categories:
- 技术

---


> logrotate 工具不会自启动，依赖 cron 定时任务工具调起或其他程序调用执行

# 1. 检查 logrotate 运行记录

## 1.1. 查看待切分日志是否被切分

```shell
ls -l -A /var/log/yourLogName.log
```

<!-- more -->

## 1.2. 检查环境有无安装 logrotate

```shell
which logrotate
# 或
ls -l /usr/sbin/logrotate
```
## 1.3. 检查 logrotate 自身配置

```shell
cat /etc/logrotate.conf
```
## 1.4. 检查有无对待切分日志文件的切分规则配置
检查有无 logrotate 对应文件的日志切分规则配置

```shell
ls -l -A /etc/logrotate.d/
cat /etc/logrotate.d/yourLogName
```
## 1.5. 测试该文件对应的日志切分配置是否正确
手动（加载配置）执行日志切分：
- 先用 debug 参数测试（不会真正执行日志切分）

```shell
# 调试执行 /etc/logrotate.d/frr 配置，为满足条件日志不会被轮转
/usr/sbin/logrotate -d /etc/logrotate.d/frr
# -f 参数强制转储日志文件
/usr/sbin/logrotate -d -f /etc/logrotate.d/frr
```
- 手动调 logrotate 执行对应日志文件的切分（强制执行）

```shell
/usr/sbin/logrotate -vf /etc/logrotate.d/frr
```

## 1.6. 查看 logrotate 的切分状态记录
logrotate 自身的日志：<code>/var/lib/logrotate/status</code>

```shell
cat /var/lib/logrotate/status
```



# 2. cron 是否正常工作？

## 2.1. 检查有无安装 cron

```shell
ls -l /usr/sbin/cron
```

## 2.2. 检测 cron 运行状态

### 2.2.1. 检查 cron 计划任务工具是否正在运行

```shell
ps -ef | grep cron | grep -v grep
```

### 2.2.2. 检查 cron 有无定时调起logrotate的日志

```shell
sudo grep -i "logrotate" /var/log/cron.log  | tail -n 10
```

## 2.3. 检测 cron 中 logrotate 的定时配置文件？

### 2.3.1. 查看 cron 的定时调起配置
配置文件：<code>/etc/anacrontab</code>（老版本为：<code>/etc/crontab</code>）


```shell
cat /etc/crontab
```

### 2.3.2. 手动执行 cron 配置中 logrotate 的每日计划任务配置

- 查看每日任务对应 logrotate 的每日计划任务配置


```shell
ls -l -A /etc/cron.daily/
cat /etc/cron.daily/logrotate
```

- 手动执行 cron 配置中 logrotate 的每日计划任务，检查能否成功调 logrotate 执行日志切分


```shell
sudo /etc/cron.daily/logrotate
```

- 查看自定义对应 logrotate 计划任务配置


```shell
ls -l /etc/cron.d/
cat /etc/cron.d/your_logrotate_cfg
```

## 2.4. 检测 cron 能否准时自行调起 logrotate 计划任务

> 通过上文查看 cron 的定时调起配置可知，cron 每天的定时任务会在 6:25 执行

- 在 <code>/etc/cron.daily/logrotate</code> logrotate 计划任务配置文件末追加打日志代码：

```shell
echo "$(date) logrotate runing" >>/tmp/logrotate.out
```

- 更改系统时间到 6:24:30，测试 cron 能否自动调起logrotate


```shell
date -s "2021-08-26 10:06:30"   # 设置系统时间
hwclock --systohc               # 将系统时间同步到硬件
```

## 2.5. 重启 cron 服务

```shell
# 重启 cron 服务方式1
service crond start     # 启动服务
service crond stop      # 关闭服务
service crond restart   # 重启服务

# 重启 cron 服务方式2
/etc/init.d/cron stop       # 关闭服务
/etc/init.d/cron start      # 启动服务
/etc/init.d/cron restart    # 重启服务
```

# 3. 参考文档
- [logrotate won't rotate my logs automatically](https://serverfault.com/questions/302020/logrotate-wont-rotate-my-logs-automatically)
