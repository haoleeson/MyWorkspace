layout: post
title: sonic 全量编译及指定容器编译简介
date: 2021/9/26 22:30:45
updated: 2021/9/26 22:40:45
comments: true
tags: 
- SONiC
- Network
categories:
- 技术

---

> sonic_version 201911
# 1. 全量编译/更换版本步骤回顾

## 1.1. 全量编译命令
> 编译环境：开发机

```shell
cd $SONIC_CODE_DIR
rm -rf target/
make configure PLATFORM=broadcom
make target/sonic.bin
```

<!-- more -->

## 1.2. 全量更换版本命令
> 安装环境：交换机
> 将全量安装包 sonic.bin 上传到交换机后执行

```shell
sudo sonic_installer install -f /home/admin/sonic.bin
sudo reboot
```

# 2. 编译及更新单个容器步骤

## 2.1. 以 bgp 为例
> bgp 容器镜像文件： <code>docker-fpm-frr.gz</code>

```shell
# 在编译机的代码库的 <code>$SONIC_CODE_DIR</code> 路径下，删除（待编译容器镜像）旧的镜像包
rm target/docker-fpm-frr.gz
rm target/debs/stretch/frr_7.2-sonic-0_amd64.deb

# 编译 bgp 容器镜像包（约 8 min）
make target/docker-fpm-frr.gz

# 上传到交换机
ls -l $SONIC_CODE_DIR/target/docker-fpm-frr.gz
scp $SONIC_CODE_DIR/target/docker-fpm-frr.gz admin@A.B.C.D:/home/admin/

# 登录交换机
ssh admin@A.B.C.D
# 确认容器镜像包信息
ls -l /home/admin/docker-fpm-frr.gz

# 单独更新 bgp 容器（无需 reboot 宿主机）
sudo sonic_installer upgrade_docker --cleanup_image bgp /home/admin/docker-fpm-frr.gz
```

## 2.2. 以 lldp 为例
> lldp 容器镜像文件： <code>docker-lldp-sv2.gz</code>

```shell
# 在编译机的代码库的 <code>$SONIC_CODE_DIR</code> 路径下，删除（待编译容器镜像）旧的镜像包
rm target/docker-lldp-sv2.gz
rm target/debs/lldpd_1.0.4-1_amd64.deb

# 编译 lldp 容器镜像包（约 8 min）
make  target/docker-lldp-sv2.gz

# 上传到交换机
ls -l $SONIC_CODE_DIR/target/docker-lldp-sv2.gz
scp $SONIC_CODE_DIR/target/docker-lldp-sv2.gz admin@A.B.C.D:/home/admin/

# 登录交换机
ssh admin@A.B.C.D
# 确认容器镜像包信息
ls -l /home/admin/docker-lldp-sv2.gz

# 单独更新 lldp 容器（无需 reboot 宿主机）
sudo sonic_installer upgrade_docker --cleanup_image lldp /home/admin/docker-lldp-sv2.gz
```

## 2.3. 以 pmon 为例
> pmon 容器镜像文件： <code>docker-platform-monitor.gz</code>

```shell
# 在编译机的代码库的 <code>$SONIC_CODE_DIR</code> 路径下，删除（待编译容器镜像）旧的镜像包
rm target/docker-platform-monitor.gz
rm target/python-debs/python-sonic-hwmgrd_1.0-1_all.deb
rm target/python-debs/python-sonic-syseepromd_1.0-1_all.deb
rm target/python-debs/python-sonic-psud_1.0-1_all.deb
rm target/python-debs/python-sonic-xcvrd_1.0-1_all.deb
rm target/python-debs/python-sonic-ledd_1.1-1_all.deb

# 编译 pmon 容器镜像包（约  min）
make target/docker-platform-monitor.gz

# 上传到交换机
ls -l $SONIC_CODE_DIR/target/docker-platform-monitor.gz
scp $SONIC_CODE_DIR/target/docker-platform-monitor.gz admin@A.B.C.D:/home/admin/

# 登录交换机
ssh admin@A.B.C.D
# 确认容器镜像包信息
ls -l /home/admin/docker-platform-monitor.gz

# 单独更新 pmon 容器（无需 reboot 宿主机）
sudo sonic_installer upgrade_docker --cleanup_image pmon /home/admin/docker-platform-monitor.gz
```

## 2.4. 以 radv 为例
> radv 容器镜像文件： <code>docker-router-advertiser.gz</code>

```shell
# 在编译机的代码库的 <code>$SONIC_CODE_DIR</code> 路径下，删除（待编译容器镜像）旧的镜像包
rm target/docker-router-advertiser.gz
rm target/debs/stretch/radvd-dbgsym_2.17-2~bpo9+1_amd64.deb
rm target/debs/stretch/radvd_2.17-2~bpo9+1_amd64.deb

# 编译 radv 容器镜像包（约 10 min）
make target/docker-router-advertiser.gz

# 上传到交换机
ls -l $SONIC_CODE_DIR/target/docker-router-advertiser.gz
scp $SONIC_CODE_DIR/target/docker-router-advertiser.gz admin@A.B.C.D:/home/admin/

# 登录交换机
ssh admin@A.B.C.D
# 确认容器镜像包信息
ls -l /home/admin/docker-router-advertiser.gz

# 单独更新 radv 容器（无需 reboot 宿主机）
sudo sonic_installer upgrade_docker --cleanup_image radv /home/admin/docker-router-advertiser.gz
```

## 2.5. 以 swss 为例
> swss 容器镜像文件： <code>docker-orchagent.gz</code>

```shell
# 在编译机的代码库的 <code>$SONIC_CODE_DIR</code> 路径下，删除（待编译容器镜像）旧的镜像包
rm target/docker-orchagent.gz
rm target/debs/stretch/swss_1.0.0_amd64.deb
rm target/debs/stretch/libswsscommon_1.0.0_amd64.deb
rm target/debs/stretch/python-swsscommon_1.0.0_amd64.deb

# 编译 swss 容器镜像包（约 13 min）
make target/docker-orchagent.gz

# 上传到交换机
ls -l $SONIC_CODE_DIR/target/docker-orchagent.gz
scp $SONIC_CODE_DIR/target/docker-orchagent.gz admin@A.B.C.D:/home/admin/
$$
# 登录交换机
ssh admin@A.B.C.D
# 确认容器镜像包信息
ls -l /home/admin/docker-orchagent.gz

# 单独更新 swss 容器（无需 reboot 宿主机）
sudo sonic_installer upgrade_docker --cleanup_image swss /home/admin/docker-orchagent.gz
```

## 2.6. 以 snmp 为例
> snmp 容器镜像文件： <code>docker-snmp-sv2.gz</code>

```shell
# 在编译机的代码库的 <code>$SONIC_CODE_DIR</code> 路径下，删除（待编译容器镜像）旧的镜像包
rm target/docker-snmp-sv2.gz
rm target/debs/stretch/libsnmp30_5.7.3+dfsg-1.5_amd64.deb
rm target/debs/stretch/libsnmp-base_5.7.3+dfsg-1.5_all.deb
rm target/debs/stretch/libsnmp-dev_5.7.3+dfsg-1.5_amd64.deb

# 编译 snmp 容器镜像包
make target/docker-snmp-sv2.gz

# 上传到交换机
ls -l $SONIC_CODE_DIR/target/docker-snmp-sv2.gz
scp $SONIC_CODE_DIR/target/docker-snmp-sv2.gz admin@A.B.C.D:/home/admin/

# 登录交换机
ssh admin@A.B.C.D
# 确认容器镜像包信息
ls -l /home/admin/docker-snmp-sv2.gz

# 单独更新 snmp 容器（无需 reboot 宿主机）
sudo sonic_installer upgrade_docker --cleanup_image snmp /home/admin/docker-snmp-sv2.gz
```

## 2.7. 以 teamd 为例
> teamd 容器镜像文件： <code>docker-teamd.gz</code>

```shell
cd $SONIC_CODE_DIR
# 在编译机的代码库的 <code>$SONIC_CODE_DIR</code> 路径下，删除（待编译容器镜像）旧的镜像包
rm target/docker-teamd.gz
rm target/debs/stretch/libteam5_1.28-1_amd64.deb

# 编译 teamd 容器镜像包（约 8 min）
make target/docker-teamd.gz

# 上传到交换机
ls -l $SONIC_CODE_DIR/target/docker-teamd.gz
scp $SONIC_CODE_DIR/target/docker-teamd.gz admin@A.B.C.D:/home/admin/

# 登录交换机
ssh admin@A.B.C.D
# 确认容器镜像包信息
ls -l /home/admin/docker-teamd.gz

# 单独更新 teamd 容器（无需 reboot 宿主机）
sudo sonic_installer upgrade_docker --cleanup_image teamd /home/admin/docker-teamd.gz
```

## 2.8. ~~以 syncd 为例~~（sonic_installer 不支持单独更换此容器）
> syncd 容器镜像文件： <code>docker-syncd-brcm.gz</code>

```shell
# 在编译机的代码库的 <code>$SONIC_CODE_DIR</code> 路径下，删除（待编译容器镜像）旧的镜像包
rm target/docker-syncd-brcm.gz
rm target/debs/stretch/syncd_1.0.0_amd64.deb

# 编译 syncd 容器镜像包（约  min）
make target/docker-syncd-brcm.gz

# 上传到交换机
ls -l $SONIC_CODE_DIR/target/docker-syncd-brcm.gz
scp $SONIC_CODE_DIR/target/docker-syncd-brcm.gz admin@A.B.C.D:/home/admin/

# 登录交换机
ssh admin@A.B.C.D
# 确认容器镜像包信息
ls -l /home/admin/docker-syncd-brcm.gz

# 单独更新 syncd 容器（无需 reboot 宿主机）
sudo sonic_installer upgrade_docker --cleanup_image syncd /home/admin/docker-syncd-brcm.gz
```

# 3. 强制替换同版本镜像方式
## 3.1. 以 syncd 为例

```shell
# 停止旧 syncd 容器
docker stop syncd
# 删除旧 syncd 容器
sudo docker rm -f syncd
# 删除旧 syncd 镜像
sudo docker rmi -f $(docker images | grep syncd  | awk '{ print $3 }')
# 加载新 syncd 镜像包
sudo docker load < /home/admin/docker-syncd-brcm.gz
# 通过服务的方式自动创建新 syncd 容器
sudo service syncd restart
```

## 3.2. 以 swss 为例

```shell
# 停止旧 swss 容器
docker stop swss
# 删除旧 swss 容器
sudo docker rm -f swss
# 删除旧 swss 镜像
sudo docker rmi -f $(docker images | grep docker-orchagent  | awk '{ print $3 }')
# 加载新 swss 镜像包
sudo docker load < /home/admin/docker-orchagent.gz
# 通过服务的方式自动创建新 swss 容器
sudo service swss restart
```

# 4. 备注

- 编译时若报 Telemetry 失败可修改 <code>rules/config</code> 中如下配置，以关闭使能Telemetry：

```shell
ENABLE_SYSTEM_TELEMETRY = n
```

- <code>sonic_installer upgrade_docker</code>的 OPTION参数说明如下：

```shell
sudo sonic_installer upgrade_docker --help
# 执行结果
Usage: sonic_installer upgrade_docker [OPTIONS] <container_name> URL

  Upgrade docker image from local binary or URL

Options:
  -y, --yes
  --cleanup_image  Clean up old docker image
  --skip_check     Skip task check for docker upgrade
  --tag TEXT       Tag for the new docker image
  --warm           Perform warm upgrade
  --help           Show this message and exit.
```
