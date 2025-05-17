layout: post
title: p4i的安装与使用
date: 2023/1/16 10:30:45
updated: 2023/1/16 10:30:45
comments: true
tags:
- SDE
- Network
- Barefoot
- P4
categories:
- 技术

---

p4i 作为 Barefoot P4 开发工具链中的重要一部分，可用于SDE P4程序编译后的各资源分配情况查看，本文记录p4i的安装与简单使用方法。

<!-- more -->

> 架构：
> - BOE 容器：编译 SDE
> - BOE 中：启动 p4i
> - MAC 电脑：创建到 BOE 端口映射，本地访问映射端口

# 1. 安装 P4i
> $SDE/pkgsrc/p4i/ 包含 p4i for Linux/MacOS 安装包
```shell
# 检查 p4i 安装包 [sde9.3.2]
docker exec -it bf_sde_9_3_2_simulation ls -l /sde/bf-sde-9.3.2/pkgsrc/p4i/
# 检查 p4i 安装包 [sde9.9.0]
docker exec -it bf_sde_9_9_0_simulation ls -l /sde/bf-sde-9.9.0/pkgsrc/p4i/

# 从外部拷出容器中 p4i 安装包 [sde9.3.2]
docker cp bf_sde_9_3_2_simulation:/sde/bf-sde-9.3.2/pkgsrc/p4i/ /home/username/
# 从外部拷出容器中 p4i 安装包 [sde9.9.0]
docker cp bf_sde_9_9_0_simulation:/sde/bf-sde-9.9.0/pkgsrc/p4i/ /home/username/

#  安装 p4i
sudo dpkg -i /home/username/p4i/p4i.linux.deb
# check
sudo dpkg -l | grep p4i

# 修复安装依赖组件缺失问题 （e.g. libgbm-dev, libasound-dev, libasound2-dev, libnotify4, libxss1, xdg-utils, libappindicator3-1）
sudo apt --fix-broken install

# 再次尝试安装 p4i
sudo dpkg -i ~/p4i/p4i.linux.deb

# 安装 xvfb （解决P4i运行时会报错段错误，无图形化界面）
sudo apt install xvfb
sudo apt install libgbm1 libasound2

# check
which p4i
```

备注：如果Debian 9系统遇到spawn xdg-open ENOENT错误，可以sudo apt-get install xdg-utils解决

# 2. 启动 P4i
直接运行
```shell
xvfb-run p4i
# 默认 localhost:3000
```

从编译容器拷贝manifest.json等文件后运行
（start_p4i.sh）
```shell
#!/usr/bin/env bash

#
# Extra manifest.json and run p4i
#

# sde 9.3.2
SDE_CONTAINER_NAME='sde_9_3_2_build'
SRC_P4I_MANIFESTS_DIR='/sde/bf-sde-9.3.2/build/switch-p4-16/p4src/switch/'
# 确保容器中已经生成了 *.tar.bz
# /opt/bf-sde/install/bin/bf-p4c --std p4-16 --target tofino --arch tna -o ./switch --bf-rt-schema ./switch/bf-rt.json -g -Xp4c='--disable-power-check' -I /p4xgw/pkgsrc/switch-p4-16/p4src/shared/ /p4xgw/pkgsrc/switch-p4-16/p4src/switch-tofino/switch_tofino_xgw.p4

# rgw
/sde/bf-sde-9.3.2/install/bin/bf-p4c --std p4-16 --target tofino --arch tna -o ./switch --bf-rt-schema ./switch/bf-rt.json -g -Xp4c='--disable-power-check' -I /sde/bf-sde-9.3.2/pkgsrc/switch-p4-16/p4src/shared/ /sde/bf-sde-9.3.2/pkgsrc/switch-p4-16/p4src/switch-tofino/switch_tofino_p4gw.p4

# sde 9.9.0
# SDE_CONTAINER_NAME='bf_sde_9_9_0_simulation'
# SRC_P4I_MANIFESTS_DIR='/sde/bf-sde-9.9.0/build/pkgsrc/switch-p4-16/p4src/switch/'
# 确保容器中已经生成了 *.tar.bz2
/sde/bf-sde-9.9.0/install/bin/bf-p4c --std p4-16 --target tofino --arch tna -o ./switch --bf-rt-schema ./switch/bf-rt.json -g --archive -DXGW_PROFILE /sde/bf-sde-9.3.2/pkgsrc/switch-p4-16/p4src/switch-tofino/switch.p4

P4I_MANIFESTS_DIR='/data00/home/username/.p4i_manifests'

# Check if sde container is running
is_sde_container_running=$(docker ps | grep $SDE_CONTAINER_NAME > /dev/null; echo $?)
echo "is_sde_container_running=$is_sde_container_running"
if [ "$is_sde_container_running" == "0" ]; then
    is_comparing=$(docker exec -it $SDE_CONTAINER_NAME ps -ef | grep p4c-barefoot > /dev/null; echo $?)
    echo "is_comparing=$is_comparing"
    # check if sde container is comparing
    if [ "$is_comparing" == "0" ]; then
        echo "Container $SDE_CONTAINER_NAME is comparing now, start p4i failed !!!"
        exit 1
    else
        # stop sde container
        echo "Container $SDE_CONTAINER_NAME is not comparing, stop it to run p4i."
        docker stop $SDE_CONTAINER_NAME
        sleep 1
    fi
fi

# copy container manifest.json
if [ -d "$P4I_MANIFESTS_DIR/switch/" ]; then
    rm -rf $P4I_MANIFESTS_DIR/switch/ > /dev/null 2>&1
fi

docker cp $SDE_CONTAINER_NAME:$SRC_P4I_MANIFESTS_DIR $P4I_MANIFESTS_DIR/

sleep 1

# start p4i
xvfb-run p4i
```

# 3. MAC 本地创建ssh 通道到远端 3000 端口映射
```shell
ssh username@A.B.C.D -L 127.0.0.1:1234:127.0.0.1:3000
# MacOS 浏览器访问 127.0.0.1:1234
```

# 4. 上传 p4i license(仅首次)
> 无 license 10min 后 p4i 自动退出
```shell
scp ~/Downloads/d1aba014-e594-41dc-b871-81a665d3c701.info username@A.B.C.D:/home/username/.local/p4i/
```

# 5. faketime within the docker
```shell
// https://102no.com/2019/11/28/libfaketime-docker-change/
// in dev-box
git clone https://github.com/wolfcw/libfaketime.git
cd libfaketime  && make install
docker cp /usr/local/lib/faketime/libfaketime.so.1 gw-9.9-container:/usr/local/lib

// in docker
chmod +x /usr/local/lib/libfaketime.so.1
sudo su tiger
export LD_PRELOAD=/usr/local/lib/libfaketime.so.1 FAKETIME="-15d"
xvfb-run install/bin/p4i
```