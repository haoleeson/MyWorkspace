layout: post
title: Etcd常用命令
date: 2023/3/10 16:12:45
updated: 2023/3/10 16:12:45
comments: true
tags: 
- Etcd
categories:
- 技术

---

Etcd是具备轻量级和高性能的分布式存储组件，尤其适合需要强一致性和高可用性的场景，本文记录一些常用命令。

<!-- more -->


# 1. 基础命令

```shell
etcdctlargs="--endpoints=http://127.0.0.1:2379"
etcdctlargs="--endpoints=127.0.0.1:2379 --cacert /root/etcd_certskeys/ca-cert.pem --cert /root/etcd_certskeys/client-cert.pem --key /root/etcd_certskeys/client-key.pem"
```

etcd help
```shell
ETCDCTL_API=3 etcdctl $etcdctlargs --help
NAME:
   etcdctl - A simple command line client for etcd.

WARNING:
   Environment variable ETCDCTL_API is not set; defaults to etcdctl v2.
   Set environment variable ETCDCTL_API=3 to use v3 API or ETCDCTL_API=2 to use v2 API.

USAGE:
   etcdctl [global options] command [command options] [arguments...]

VERSION:
   3.2.26

COMMANDS:
     backup          backup an etcd directory
     cluster-health  check the health of the etcd cluster
     mk              make a new key with a given value
     mkdir           make a new directory
     rm              remove a key or a directory
     rmdir           removes the key if it is an empty directory or a key-value pair
     get             retrieve the value of a key
     ls              retrieve a directory
     set             set the value of a key
     setdir          create a new directory or update an existing directory TTL
     update          update an existing key with a given value
     updatedir       update an existing directory
     watch           watch a key for changes
     exec-watch      watch a key for changes and exec an executable
     member          member add, remove and list subcommands
     user            user add, grant and revoke subcommands
     role            role add, grant and revoke subcommands
     auth            overall auth controls
     help, h         Shows a list of commands or help for one command

GLOBAL OPTIONS:
   --debug                          output cURL commands which can be used to reproduce the request
   --no-sync                        don't synchronize cluster information before sending request
   --output simple, -o simple       output response in the given format (simple, `extended` or `json`) (default: "simple")
   --discovery-srv value, -D value  domain name to query for SRV records describing cluster endpoints
   --insecure-discovery             accept insecure SRV records describing cluster endpoints
   --peers value, -C value          DEPRECATED - "--endpoints" should be used instead
   --endpoint value                 DEPRECATED - "--endpoints" should be used instead
   --endpoints value                a comma-delimited list of machine addresses in the cluster (default: "http://127.0.0.1:2379,http://127.0.0.1:4001")
   --cert-file value                identify HTTPS client using this SSL certificate file
   --key-file value                 identify HTTPS client using this SSL key file
   --ca-file value                  verify certificates of HTTPS-enabled servers using this CA bundle
   --username value, -u value       provide username[:password] and prompt if password is not supplied.
   --timeout value                  connection timeout per request (default: 2s)
   --total-timeout value            timeout for the command execution (except watch) (default: 5s)
   --help, -h                       show help
   --version, -v                    print the version
```

## 1.1. 查看 etcd 版本

```shell
ETCDCTL_API=3 etcdctl $etcdctlargs version
```

## 1.2. 查看 etcd 状态（含磁盘用量）
```shell
ETCDCTL_API=3 etcdctl $etcdctlargs --write-out=table endpoint status
```

## 1.3. 查看 etcd 磁盘使用量
```shell
ETCDCTL_API=3 etcdctl $etcdctlargs endpoint status --write-out table
```

## 1.4. 查看告警
```shell
etcdctlargs='--endpoints=127.0.0.1:2379 --cacert /root/etcd_certskeys/ca-cert.pem --cert /root/etcd_certskeys/client-cert.pem --key /root/etcd_certskeys/client-key.pem'
ETCDCTL_API=3 etcdctl $etcdctlargs alarm list
```

## 1.5. NOSPACE 处理方法
```shell
# 1. get REVISION
REVISION=$(ETCDCTL_API=3 etcdctl $etcdctlargs endpoint status --write-out="json" | egrep -o '"revision":[0-9]*' | egrep -o '[0-9].*'); echo "'$REVISION'"
# 2. 压缩数据版本
ETCDCTL_API=3 etcdctl $etcdctlargs compact ${REVISION}
# 3. 碎片整理
ETCDCTL_API=3 etcdctl $etcdctlargs defrag
ETCDCTL_API=3 etcdctl $etcdctlargs alarm disarm
# 查看磁盘占用
ETCDCTL_API=3 etcdctl $etcdctlargs --write-out=table endpoint status
```

## 1.6. 数据满处理办法
### 1.6.1. 临时处理
```shell
# 获取当前版本
rev=$(ETCDCTL_API=3 etcdctl $etcdctlargs endpoint status --write-out="json" | egrep -o '"revision":[0-9]*' | egrep -o '[0-9].*')
# rev=$(etcdctl version)

# 压缩所有旧版本
ETCDCTL_API=3 etcdctl $etcdctlargs compact $rev

# 整理多余的空间
ETCDCTL_API=3 etcdctl $etcdctlargs defrag

# 取消告警信息
ETCDCTL_API=3 etcdctl $etcdctlargs alarm disarm

# 测试是否能成功写入
ETCDCTL_API=3 etcdctl $etcdctlargs put testkey 123

OK

# 再次查看ETCD存储使用情况
ETCDCTL_API=3 etcdctl $etcdctlargs --write-out=table endpoint status
```

### 1.6.2. 最终解决方案
在 etcd 启动参数中设置磁盘空间为 8 G
```shell
# 表示每隔一个小时自动压缩一次
# --auto-compaction-retention=1
# 磁盘空间调整为 8G，官方建议最大 8G（单位是字节）
# --quota-backend-bytes=8388608000

# e.g. 
etcd -advertise-client-urls http://0.0.0.0:2379 -listen-client-urls http://0.0.0.0:2379 --auto-compaction-retention=1 --quota-backend-bytes=8388608000
```

## 1.7. 启动 etcd 容器
```shell
# 实例启动命令： 更改容量参数为 8G
etcd_image=quay.io/coreos/etcd:v3.3.9 && \
docker run -tid --name etcd --net=host --restart=always --log-opt max-size=50m --log-opt max-file=8 \
   -v /etc/etcd:/etc/etcd \
   -v /etc/pki:/etc/pki \
   -v /var/lib/etcd:/var/lib/etcd \
   $etcd_image etcd -advertise-client-urls http://0.0.0.0:2379 -listen-client-urls http://0.0.0.0:2379 --auto-compaction-retention=1 --quota-backend-bytes=8388608000
```

## 1.8. 碎片整理
```shell
ETCDCTL_API=3 etcdctl $etcdctlargs defrag
```

## 1.9. 备份
```shell
ETCDCTL_API=3 etcdctl $etcdctlargs snapshot save backup.db
```

## 1.10. 节点健康检查
```shell
ETCDCTL_API=3 etcdctl $etcdctlargs endpoint health
```

## 1.11. set quota
```shell
# set a very small 16 MiB quota
$ etcd --quota-backend-bytes=$((16*1024*1024))
```
## 1.12. 获取etcd成员列表
```shell
ETCDCTL_API=3 etcdctl $etcdctlargs member list
# 回显示例
# 8e9e05c52164694d: name=n201-040-087 peerURLs=http://localhost:2380 clientURLs=http://10.201.40.87:2379,http://localhost:2379 isLeader=true
```

# 2. 增
## 2.1. 写数据

```shell
ETCDCTL_API=3 etcdctl $etcdctlargs put <key> <value>
```

# 3. 删
## 3.1. 删除指定 key
```shell
# 检查指定 key 数
ETCDCTL_API=3 etcdctl $etcdctlargs get --from-key "/app_data/vpc_remote_data/*" | wc
ETCDCTL_API=3 etcdctl $etcdctlargs get --from-key "/app_data/eni/*" | wc

# etcdctl del --from-key <key>
ETCDCTL_API=3 etcdctl $etcdctlargs del --from-key "/app_data/vpc_remote_data/*"

# 再次检查指定 key 数 （预期为 0）
ETCDCTL_API=3 etcdctl $etcdctlargs get --from-key "/app_data/vpc_remote_data/*" | wc
```

## 3.2. 删除key name12时并返回被删除的键值对
```shell
ETCDCTL_API=3 etcdctl $etcdctlargs del --prefix "/name12"
```

## 3.3. 删除所有数据
```shell
ETCDCTL_API=3 etcdctl $etcdctlargs del --prefix ""
ETCDCTL_API=3 etcdctl $etcdctlargs del --prefix "/controler/routetable/"
```

# 4. 改
## 4.1. 用 put 更新数据
```shell
# etcdctl put <key> <value>
ETCDCTL_API=3 etcdctl $etcdctlargs put avg_age 30
```

# 5. 查
## 5.1. 读指定 key 的值
```shell
ETCDCTL_API=3 etcdctl $etcdctlargs get <key>
ETCDCTL_API=3 etcdctl $etcdctlargs get /app_data/

ETCDCTL_API=3 etcdctl $etcdctlargs get --prefix "/app_data/leader/"

# 模糊查询匹配到前缀为web的数据
# 不支持 etcdctl get --prefix app_data

# 模糊查询匹配到前缀为web的key（不返回value）
# 不支持 etcdctl --prefix --keys-only=true get app_data 
ETCDCTL_API=3 etcdctl $etcdctlargs --prefix --keys-only=true get app_data 
```

## 5.2. 查看所有包含特定字段key
```shell
# 先预览包含指定字段的 key 的个数
ETCDCTL_API=3 etcdctl $etcdctlargs get --from-key "*app_data*" | wc
```

## 5.3. 查看所有 key
```shell
# 先预览 key 个数
ETCDCTL_API=3 etcdctl $etcdctlargs get --from-key "" | wc
```
