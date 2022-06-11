layout: post
title: logrotate日志轮转工具简介
date: 2021/8/23 22:30:45
updated: 2021/8/23 23:10:45
comments: true
tags: 
- syslog
categories:
- 技术

---

日志轮转 log rotation 解读：日志轮转是系统管理中使用的一个自动化过程，在此过程中，一旦日志文件太旧或太大，就会对其进行压缩、移动（存档）、重命名或删除。

<!-- more -->

# 1. logrotate 简介

- 管理系统所产生的日志文件。可自动对日志进行截断（或轮转）、压缩以及删除旧的日志文件。
- 可周期性（按天/周/月）或当所监控文本文件大小超过阈值时（eg. 100MB），对文件进行截断（轮转）、压缩或删除过于老旧备份文件等处理。
- Linux系统默认安装logrotate工具，判断有无安装logrotate方式：<code>which logrotate</code>
- logrotate自身为一个命令行工具，需要手动调用或基于计划任务cron调起logrotate工作<br>（默认情况已在<code>/etc/cron.daily/logrotate</code>配置了其每天定时执行）

## 1.1. logrotate 配置文件说明

logrotate 配置文件包括：
- <b><font color="#7E3D76" style="">logrotate 自身的配置文件: /etc/logrotate.conf</font></b>
- <b><font color="#7E3D76" style="">需要轮转管理的日志文件各自的配置文件: /etc/logrotate.d/*</font></b>（统一放置于/etc/logrotate.d/目录下）

## 1.2. logrotate 手动运行命令
在完成/修改 logrotate 配置后，需重启 logrotate 以使配置生效。

<b><font color="#7E3D76" style="">手动运行logrotate的命令：</font></b>
```shell
/usr/sbin/logrotate /etc/logrotate.conf
```

<b><font color="#7E3D76" style="">手动执行某个日志的轮转配置文件的命令：</font></b>
```shell
/usr/sbin/logrotate -vf /etc/logrotate.d/log-file
```

## 1.3. 添加 logrotate 工具的计划任务

/etc/cron.daily目录下，有个logrotate的脚本，系统每天会执行/etc/cron.daily内的脚本，这样只需我们按上述/etc/logrotate.d/example中的配置，即可保证每天日志的生成。

<b><font color="#7E3D76" style="">配置宿主机计划任务：以天为周期启动日志轮转工具logrotate工具（无守护进程），内容如下：</font></b>
```shell
admin@host:~$ cat /etc/cron.daily/logrotate
#!/bin/sh

test -x /usr/sbin/logrotate || exit 0
/usr/sbin/logrotate /etc/logrotate.conf
admin@host:~$
```

## 1.4. logrotate 命令格式
```shell
logrotate [OPTION...] <configfile>
```
OPTION参数说明：
<table border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th align="center">参数（简写）</th>
        <th align="center">参数（详细）</th>
        <th align="center">功能</th>
    </tr>
    <tr>
        <td align="center">-d</td>
        <td align="center">--debug</td>
        <td align="center">debug模式，测试配置文件是否有错误。</td>
    </tr>
    <tr>
        <td align="center">-f</td>
        <td align="center">--force</td>
        <td align="center">强制转储文件。</td>
    </tr>
    <tr>
        <td align="center">-m</td>
        <td align="center">--mail=command</td>
        <td align="center">压缩日志后，发送日志到指定邮箱。</td>
    </tr>
    <tr>
        <td align="center">-s</td>
        <td align="center">--state=statefile</td>
        <td align="center">使用指定的状态文件。</td>
    </tr>
    <tr>
        <td align="center">-v</td>
        <td align="center">--verbose</td>
        <td align="center">显示转储过程。</td>
    </tr>
</table>


# 2. logrotate 轮转参数配置示例

示例配置文件<code>（/etc/logrotate.d/log-file</code>）

```conf
/var/log/log-file {
    monthly
    rotate 5
    compress
    delaycompress
    missingok
    notifempty
    create 644 root root
    postrotate
        /usr/bin/killall -HUP rsyslogd
    endscript
}
```

<b><font color="red" style="">轮转参数解释如下：</font></b>


<table border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th align="center"><b>配置参数</b></th>
        <th align="center"><b>说明</b></th>
    </tr>
    <tr>
        <td>monthly</td>
        <td>日志文件将按月轮转。其它可用值为'daily'，'weekly'或者'yearly'。</td>
    </tr>
    <tr>
        <td>rotate 5</td>
        <td>一次将存储5个归档日志。对于第六个归档，时间最久的归档将被删除。</td>
    </tr>
    <tr>
        <td>compress</td>
        <td>在轮转任务完成后，已轮转的归档将使用gzip进行压缩。</td>
    </tr>
    <tr>
        <td>delaycompress</td>
        <td>总是与compress选项一起用，delaycompress选项指示logrotate不要将最近的归档压缩，<br>压缩将在下一次轮转周期进行。这在你或任何软件仍然需要读取最新归档时很有用。</td>
    </tr>
    <tr>
        <td>missingok</td>
        <td>在日志轮转期间，任何错误将被忽略，例如“文件无法找到”之类的错误。</td>
    </tr>
    <tr>
        <td>notifempty</td>
        <td>如果日志文件为空，轮转不会进行。</td>
    </tr>
    <tr>
        <td>create 644 root root</td>
        <td>以指定的权限创建全新的日志文件，同时logrotate也会重命名原始日志文件。</td>
    </tr>
    <tr>
        <td>postrotate/endscript</td>
        <td>在所有其它指令完成后，postrotate和endscript里面指定的命令将被执行。<br>在这种情况下，rsyslogd 进程将立即再次读取其配置并继续运行。</td>
    </tr>
</table>

<b><font color="red" style="">其他参数说明：</font></b>

<table border="1" cellspacing="1" style="border: 1ps dotted #666" >
    <tr>
        <th align="center"><b>配置参数</b></th>
        <th align="center"><b>说明</b></th>
    </tr>
    <tr>
        <td>nocompress</td>
        <td>不压缩</td>
    </tr>
    <tr>
        <td>copytruncate</td>
        <td>用于还在打开中的日志文件，把当前日志备份并截断</td>
    </tr>
    <tr>
        <td>nocopytruncate</td>
        <td>备份日志文件但是不截断</td>
    </tr>
    <tr>
        <td>create mode owner group</td>
        <td>转储文件，使用指定的文件模式创建新的日志文件</td>
    </tr>
    <tr>
        <td>nocreate</td>
        <td>不建立新的日志文件</td>
    </tr>
    <tr>
        <td>nodelaycompress</td>
        <td>覆盖 delaycompress 选项，转储同时压缩。</td>
    </tr>
    <tr>
        <td>nosharedscripts</td>
        <td>（默认项）对于每一个轮转的日志文件都执行prerotate和postrotate脚本。</td>
    </tr>
    <tr>
        <td>errors address</td>
        <td>专储时的错误信息发送到指定的Email 地址</td>
    </tr>
    <tr>
        <td>ifempty</td>
        <td>即使是空文件也转储，这个是 logrotate 的缺省选项。</td>
    </tr>
    <tr>
        <td>mail address</td>
        <td>把转储的日志文件发送到指定的E-mail 地址</td>
    </tr>
    <tr>
        <td>nomail</td>
        <td>转储时不发送日志文件</td>
    </tr>
    <tr>
        <td>olddir directory</td>
        <td>转储后的日志文件放入指定的目录，必须和当前日志文件在同一个文件系统</td>
    </tr>
    <tr>
        <td>noolddir</td>
        <td>转储后的日志文件和当前日志文件放在同一个目录下</td>
    <tr>
        <td>prerotate/endscript</td>
        <td>在转储以前需要执行的命令可以放入这个对，这两个关键字必须单独成行</td>
    </tr>
    <tr>
        <td>postrotate/endscript</td>
        <td>该对字段间的脚本将在日志轮转结束后执行</td>
    </tr>
    <tr>
        <td>firstaction/endscript</td>
        <td>区间内的脚本在轮转之前、prerotate之前，且至少有一个待轮转日志时，才执行（限制：需要轮转的日志数必须大于1才执行；若此区间出错，将不会执行下方的脚本）</td>
    </tr>
    <tr>
        <td>rotate count</td>
        <td>指定日志文件删除之前转储的次数，0指没有备份，5指保留5个备份</td>
    </tr>
    <tr>
        <td>tabooext [+] list</td>
        <td>让logrotate不转储指定扩展名的文件，缺省的扩展名是：.rpm-orig, .rpmsave, v, 和 ~</td>
    </tr>
    <tr>
        <td>size size</td>
        <td>当日志文件到达指定的大小时才转储，bytes(缺省)及KB(sizek)或MB(sizem)
    </tr>
</table>

# 3. 项目中 logrotate 配置

## 3.1. logrotate 工具自身配置（宿主机，容器内无）

<b><font color="red" style="">宿主机的 logrotate 工具自身配置文件/etc/logrotate.conf如下：</font></b>


```conf
# see "man logrotate" for details
# rotate log files weekly
weekly

# keep 4 weeks worth of backlogs
rotate 4

# create new (empty) log files after rotating old ones
create

# uncomment this if you want your log files compressed
#compress

# packages drop log rotation information into this directory
include /etc/logrotate.d

# no packages own wtmp, or btmp -- we'll rotate them here
/var/log/wtmp {
    missingok
    monthly
    create 0664 root utmp
    rotate 1
}

/var/log/btmp {
    missingok
    monthly
    create 0660 root utmp
    rotate 1
}

# system-specific logs may be configured here
```


## 3.2. 各需日志轮转文件的配置（宿主机中）

<b><font color="red" style="">各需日志轮转文件的配置文件 /etc/logrotate.d/rsyslog 内容如下：</font></b>

```conf
# These logs should no longer get created. However, in case they do get created,
# we should keep them to a small size and rotate them also.

/var/log/auth.log
/var/log/cli.log
/var/log/debug
/var/log/telemetry.log
{
    size 10M
    rotate 1
    missingok
    notifempty
    compress
    sharedscripts
    postrotate
        /bin/kill -HUP $(cat /var/run/rsyslogd.pid)
    endscript
}

/var/log/kern.log
/var/log/quagga/bgpd.log
/var/log/quagga/zebra.log
/var/log/syslog
/var/log/teamd.log
/var/log/user.log
{
    size 100M
    rotate 10
    missingok
    notifempty
    compress
    sharedscripts
    postrotate
        /bin/kill -HUP $(cat /var/run/rsyslogd.pid)
    endscript
}

/var/log/cron.log
/var/log/daemon.log
/var/log/messages
{
    size 200M
    rotate 10
    missingok
    notifempty
    compress
    sharedscripts
    firstaction
        # Adjust NUM_LOGS_TO_ROTATE to reflect number of log files that trigger this block specified above
        NUM_LOGS_TO_ROTATE=5

        # Adjust LOG_FILE_ROTATE_SIZE_KB to reflect the "size" parameter specified above, in kB
        LOG_FILE_ROTATE_SIZE_KB=204800

        # Reserve space for btmp, wtmp, dpkg.log, monit.log, etc., as well as logs that
        # should be disabled, just in case they get created and rotated
        RESERVED_SPACE_KB=4096

        VAR_LOG_SIZE_KB=$(df -k /var/log | sed -n 2p | awk '{ print $2 }')

        # Limit usable space to 90% of the partition minus the reserved space for other logs
        USABLE_SPACE_KB=$(( (VAR_LOG_SIZE_KB * 90 / 100) - RESERVED_SPACE_KB))

        # Set our threshold so as to maintain enough space to write all logs from empty to full
        # Most likely, some logs will have non-zero size when this is called, so this errs on the side
        # of caution, giving us a bit of a cushion if a log grows quickly and passes its rotation size
        THRESHOLD_KB=$((USABLE_SPACE_KB - (NUM_LOGS_TO_ROTATE * LOG_FILE_ROTATE_SIZE_KB * 2)))

        # First, delete any *.1 or *.11~20.gz files that might be left around from a prior incomplete
        find /var/log -type f | egrep '.+\.1?$|.+\.1[1-9]+\.gz?$|.+\.20+\.gz?$' | xargs rm -f

        # logrotate execution, otherwise logrotate will fail to do its job
        while true; do
            USED_KB=$(du -s /var/log | awk '{ print $1; }')

            if [ $USED_KB -lt $THRESHOLD_KB ]; then
                break
            else
                OLDEST_ARCHIVE_FILE=$(find /var/log -type f -printf '%T+ %p\n' | grep -E '.+\.[0-9]+(\.gz)?$' | sort | head -n 1 | awk '{ print $2; }')

                if [ -z "$OLDEST_ARCHIVE_FILE" ]; then
                    logger -p syslog.err -t "logrotate" "No archive file to delete -- potential for filling up /var/log partition!"
                    break
                fi

                logger -p syslog.info -t "logrotate" "Deleting archive file $OLDEST_ARCHIVE_FILE to free up space"
                rm -rf "$OLDEST_ARCHIVE_FILE"
            fi
        done
    endscript
    postrotate
        /bin/kill -HUP $(cat /var/run/rsyslogd.pid) 2>/dev/null || true
    endscript
}

/var/log/swss/swss.rec
/var/log/swss/sairedis.rec
{
    size 200M
    rotate 10
    missingok
    notifempty
    compress
    sharedscripts
    postrotate
        pgrep -x orchagent | xargs /bin/kill -HUP 2>/dev/null || true
    endscript
}
```

## 3.3. 各需日志轮转文件的配置（容器中）

<b><font color="red" style="">容器各需日志轮转文件的配置文件 /etc/logrotate.d/rsyslog 内容如下：</font></b>

```conf
/var/log/syslog
{
	rotate 7
	daily
	missingok
	notifempty
	delaycompress
	compress
	postrotate
		invoke-rc.d rsyslog rotate > /dev/null
	endscript
}

/var/log/mail.info
/var/log/mail.warn
/var/log/mail.err
/var/log/mail.log
/var/log/daemon.log
/var/log/kern.log
/var/log/auth.log
/var/log/user.log
/var/log/lpr.log
/var/log/cron.log
/var/log/debug
/var/log/messages
{
	rotate 4
	weekly
	missingok
	notifempty
	compress
	delaycompress
	sharedscripts
	postrotate
		invoke-rc.d rsyslog rotate > /dev/null
	endscript
}
```


# 4. 容器中 supervisor 守护进程的配置文件（容器中，宿主机无）

配置文件：/etc/supervisor/conf.d/supervisord.conf

<b><font color="red" style="">容器中，守护进程配置（各程序的kill重启策略）</font></b>

```conf
root@host:/var# cat /etc/supervisor/conf.d/supervisord.conf
[supervisord]
logfile_maxbytes=1MB
logfile_backups=2
nodaemon=true

[eventlistener:supervisor-proc-exit-listener]
command=/usr/bin/supervisor-proc-exit-listener
events=PROCESS_STATE_EXITED
autostart=true
autorestart=unexpected

[program:start.sh]
command=/usr/bin/start.sh
priority=1
autostart=true
autorestart=false
stdout_logfile=syslog
stderr_logfile=syslog

[program:rsyslogd]
command=/usr/sbin/rsyslogd -n
priority=2
autostart=false
autorestart=unexpected
stdout_logfile=syslog
stderr_logfile=syslog

[program:syncd]
command=/usr/bin/syncd_start.sh
priority=3
autostart=false
autorestart=false
stdout_logfile=syslog
stderr_logfile=syslog

[program:ledinit]
command=/usr/bin/bcmcmd -t 60 "rcload /usr/share/host/platform/led_proc_init.soc"
priority=4
autostart=false
autorestart=false
startsecs=0
stdout_logfile=syslog
stderr_logfile=syslog

[program:linecardd]
command=/usr/bin/linecardd
priority=5
autostart=false
autorestart=false
stdout_logfile=syslog
stderr_logfile=syslog

[program:averagerated]
command=/usr/bin/averated
priority=6
autostart=true
autorestart=false
stdout_logfile=syslog
stderr_logfile=syslog
```

# 参考文档
- [日志切割之Logrotate](https://www.cnblogs.com/clsn/p/8428257.html)