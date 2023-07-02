layout: post
title: Docker安装及简单应用
date: 2018/11/19 12:10:30
updated: 2019/2/18 10:03:45
comments: true
tags:

- Docker
categories:
- 技术

---
<img src="../../../../uploads/DockerSimpleUsing.png" class="full-image" />

# 1. 安装Docker

## 1.1. 一键安装Docker
Manjaro系统下pacman命令一键安装Docker

```unix
sudo pacman -S docker
```
<!-- more -->

## 1.2. 配置镜像加速器
国内从 Docker Hub 拉取镜像有时会遇到困难，此时可以配置镜像加速器。Docker 官方和国内很多云服务商都提供了国内加速器服务，例如:
- Docker 官方提供的中国 registry mirror https://registry.docker-cn.com
- 七牛云加速器 https://reg-mirror.qiniu.com/

### 1.2.1. 新建 /etc/docker/daemon.json 文件
```
sudo touch /etc/docker/daemon.json
sudo vim /etc/docker/daemon.json
```

### 1.2.2. 在文件中添加如下命令
```unix 文件位置：/etc/docker/daemon.json
{
    "registry-mirrors": [
        "https://registry.docker-cn.com"
    ]
}
```

### 1.2.3. 重新启动服务
```bash
sudo systemctl daemon-reload
sudo systemctl restart docker
```

### 1.2.4. 检查加速器是否生效
```bash
sudo docker info
```
若最后有如下信息，则国内镜像服务（加速器）已生效
```bash
Registry Mirrors:
 https://registry.docker-cn.com/
```

# 2. Docker简单应用

## 2.1. 运行hello-word小例子
```bash
sudo docker run hello-world
```
运行hello-world容器，尽管此时没有hello-world镜像，docker会自动拉取hello-world的镜像，然后运行hello-world容器。

## 2.2. 获取镜像
在 [Docker Store](https://store.docker.com/) 上有非常多的高质量的官方镜像

### 2.2.1. 拉取Python镜像
```bash
sudo docker pull python:3.5
```

### 2.2.2. 拉取Ubuntu16.04镜像
```bash
sudo docker pull ubuntu:16.04
```

### 2.2.3. 列出已经下载下来的镜像
```bash
sudo docker image ls
```

### 2.2.4. 删除镜像
```bash
sudo docker image rm [镜像名/镜像ID]
```

# 3. 使用python镜像

## 3.1. 准备工作
在宿主操作系统～目录下新建文件夹
```bash
mkdir -p DockerTest/Pythonapp #新建Pythonapp文件夹
touch helloworld.py #创建 python程序文件
```
helloworld.py 文件，代码如下：
```[] 文件位置：~/DockerTest/Pythonapp/helloworld.py

#!/usr/bin/python

for i in range(5):
    print(i， ' hello world!')
```

## 3.2. 运行容器
跳转到上一目录~/DockerTest，并执行以下命令运行容器

```bash
sudo docker run -v $PWD/Pythonapp:/usr/src/Pythonapp -w /usr/src/Pythonapp python:3.5 python helloworld.py

#命令说明：

-v $PWD/Pythonapp:/usr/src/Pythonapp #将主机中当前目录下的Pythonapp挂载到容器的/usr/src/Pythonapp
-w /usr/src/Pythonapp #指定容器的/usr/src/Pythonapp目录为工作目录
python helloworld.py #使用容器的python命令来执行工作目录中的helloworld.py文件
```
执行结果如下：
```python
0 hello world!
1 hello world!
2 hello world!
3 hello world!
4 hello world!
```

# 4. 使用Ubuntu16.04镜像

## 4.1. 容器与宿主机对比
```bash
#创建一个Ubuntu16.04容器并在内运行bash
sudo docker run -t -i ubuntu:16.04 /bin/bash
# 显示当前目录
pwd
# 显示正在使用的内核版本
uname -r
# 显示Docker的进程
ps a | grep docker
```
![Docker容器&宿主机对比](../../../../uploads/DockerContainerAndHostComparison.png)

**左图**为Docker运行的Ubuntu16.04容器； **右图**为宿主操作系统

**分析**：执行**pwd** (#显示当前目录)**命令**时可看到容器的当前目录为<code>/</code>，而非运行容器的宿主目录<code>~</code>；均跳转到根目录<code>/</code>后运行<code>ls</code>命令可看到容器与宿主操作系统有两套不同的文件系统。正如前面介绍的那样，Docker会虚拟一整套文件系统。

**分析**：两边执行<code>**uname -r**</code>>            # 显示正在使用的内核版本**命令**，两边内核版本一致，正如前面介绍的那样，Docker无模拟硬件，无内核。

## 4.2. 创建一个Ubuntu16.04容器并在内运行bash小程序
小程序功能：每隔一秒输出一次hello world
```bash
sudo docker run ubuntu:16.04 /bin/sh -c "while true; do echo hello world; sleep 1; done"
```
{% note warning %}按 Ctrl + C 可退出小程序循环{% endnote %}

## 4.3. 显示当前容器
```bash
docker container ls #显示当前正在运行的容器
sudo docker container ls -a #显示所有容器，包括终止状态的容器
```

## 4.4. 清理所有处于终止状态的容器
```bash
sudo docker container prune
```

# 5. Docker镜像、容器常用命令

## 5.1. 每次启动docker 重新启动服务
```bash
sudo systemctl daemon-reload
sudo systemctl restart docker
```

##（容器对比）linux命令：
显示当前目录:                 pwd
显示正在使用的内核版本:        uname -r
显示Docker的进程：            ps a | grep docker

## 5.2. 从 Docker 镜像仓库获取镜像：
```bash
sudo docker pull ubuntu:16.04
```

## 5.3. 列出本地镜像：
```bash
sudo docker image ls
```

## 5.4. 删除本地镜像：
```bash
sudo docker image rm [选项] <镜像1> [<镜像2> ...]
```

# 6. 容器 常用命令

## 6.1. 显示当前容器：
```bash
sudo docker container ls #显示当前正在运行的容器
sudo docker container ls -a #显示所有状态的容器（包括终止状态的容器）
```

## 6.2. 新建并启动:
```bash
sudo docker run -t -i ubuntu:16.04 /bin/bash # 创建一个Ubuntu16.04容器并在内运行bash
```

## 6.3. 后台运行容器 -d 参数：
```bash
sudo docker run -d ubuntu:16.04 /bin/sh -c "while true; do echo hello world; sleep 1; done"    #容器会在后台运行并不会把输出的结果 (STDOUT) 打印到宿主机上面

# 对比缺少 -d 参数的运行容器
sudo docker run ubuntu:16.04 /bin/sh -c "while true; do echo hello world; sleep 1; done"    #容器会把输出的结果 (STDOUT) 打印到宿主机上面
```

## 6.4. 终止容器：
```bash
sudo docker container stop [容器名/容器ID]
```
例如对于上面中只启动了一个ubuntu:16.04终端的容器，用户通过 exit 命令或Ctrl+d 来退出终端时，所创建的容器立刻终止。

## 6.5. 删除容器
```bash
sudo docker container rm [容器名/容器ID] #删除一个处于终止状态的容器
sudo docker container rm -f [容器名/容器ID] #删除一个运行中的容器
sudo docker container prune #清理所有处于终止状态的容器
```

## 6.6. 进入容器
在使用 -d 参数时，容器启动后会进入后台。
某些时候需要进入容器进行操作，包括使用 docker attach 命令或 docker exec 命令，推荐大家使用 docker exec 命令
```bash
sudo docker attach [容器名/容器ID]
sudo docker exec -it [容器名/容器ID] bash

#eg.
sudo docker run -d ubuntu:16.04 #后台运行ubuntu:16.04容器
sudo docker container ls -a #显示所有状态的容器（包括终止状态的容器）
sudo docker exec -it [容器名/容器ID] bash #进入ubuntu:16.04容器，并执行bash
```

## 6.7. 导出和导入容器

### 6.7.1. 导出容器
如果要导出本地某个容器，可以使用 docker export 命令，将导出容器快照到本地文件。
```bash
sudo docker container ls -a #显示所有状态的容器（包括终止状态的容器）
sudo docker export [容器名/容器ID] > FileName.tar
```

### 6.7.2. 导入容器快照
可以使用 docker import 从容器快照文件中再导入为镜像，例如
```bash
sudo cat FileName.tar | docker import - test/FileName:v1.0
sudo docker image ls
```
