

# 1. PVE
## 1.1. PVE 优化设置
### 1.1.1. 添加DNS
```shell
pve-系统-DNS-DNS服务器1-编辑：添加 223.5.5.5(阿里)、119.29.29.29(腾讯)
```

### 1.1.2. /etc/apt/sources.list
```shell
#origin
#deb http://ftp.debian.org/debian bookworm main contrib
#deb http://ftp.debian.org/debian bookworm-updates main contrib
#deb http://security.debian.org bookworm-security main contrib

#tsinghua
deb https://mirrors.tuna.tsinghua.edu.cn/debian/ bookworm main contrib non-free non-free-firmware
deb https://mirrors.tuna.tsinghua.edu.cn/debian/ bookworm-updates main contrib non-free non-free-firmware
deb https://mirrors.tuna.tsinghua.edu.cn/debian/ bookworm-backports main contrib non-free non-free-firmware
deb https://security.debian.org/debian-security bookworm-security main contrib non-free non-free-firmware

#ustc
deb https://mirrors.ustc.edu.cn/debian bookworm main contrib non-free non-free-firmware
deb https://mirrors.ustc.edu.cn/debian bookworm-updates main contrib non-free non-free-firmware
deb https://mirrors.ustc.edu.cn/debian bookworm-backports main contrib non-free non-free-firmware
deb https://mirrors.ustc.edu.cn/debian-security/ bookworm-security main contrib non-free non-free-firmware

```

## 1.2. /etc/apt/sources.list.d/pve-enterprise.list
屏蔽企业源
```shell
#deb https://enterprise.proxmox.com/debian/pve bookworm pve-enterprise
```

## 1.3. /etc/apt/sources.list.d/pve-no-subscription.list
更换中科大源
```shell
echo "deb https://mirrors.ustc.edu.cn/proxmox/debian/pve bookworm pve-no-subscription" > /etc/apt/sources.list.d/pve-no-subscription.list
```

## 1.4. /etc/apt/sources.list.d/ceph.list
更新CEPH分布式源
```shell
echo "deb https://mirrors.ustc.edu.cn/proxmox/debian/ceph-quincy bookworm no-subscription" > /etc/apt/sources.list.d/ceph.list
 
sed -i.bak "s#http://download.proxmox.com/debian#https://mirrors.ustc.edu.cn/proxmox/debian#g" /usr/share/perl5/PVE/CLI/pveceph.pm
```

## 1.5. 修复https证书并更新软件源
```shell
apt update && apt-get install -y apt-transport-https ca-certificates  --fix-missing
```

## 1.6. 更新LXC容器仓库员（CT）
```shell
sed -i.bak "s#http://download.proxmox.com/images#https://mirrors.ustc.edu.cn/proxmox/images#g" /usr/share/perl5/PVE/APLInfo.pm

# 重启PVE核心守护进程，稍等下手动刷新webui 页面
systemctl restart pvedaemon  
```

### 1.6.1. 开启CPU温度监控
```shell
apt-get install -y lm-sensors

# lm-sensors need configure, run below to configure your sensors, or refer to lm-sensors manual.
sensors-detect 
wget https://raw.githubusercontent.com/Meliox/PVE-mods/main/pve-mod-gui-sensors.sh
bash pve-mod-gui-sensors.sh install

# Then clear the browser cache to ensure all changes are visualized.
(curl -Lf -o /tmp/temp.sh https://raw.githubusercontent.com/a904055262/PVE-manager-status/main/showtempcpufreq.sh || curl -Lf -o /tmp/temp.sh https://mirror.ghproxy.com/https://raw.githubusercontent.com/a904055262/PVE-manager-status/main/showtempcpufreq.sh) && chmod +x /tmp/temp.sh && /tmp/temp.sh remod
```

# 2. 101 openwrt
## 2.1. 编译openwrt
备注
sed -i 's/ +libopenssl-legacy//g' package/feeds/helloworld/shadowsocksr-libev/Makefile

## 2.2. 安装 openwrt
/var/lib/vz/template/iso/openwrt-x86-64-generic-squashfs-combined-efi.img

qm importdisk 101 /var/lib/vz/template/iso/openwrt-x86-64-generic-squashfs-combined-efi.img local

# 3. 硬盘直通
```shell
ls -l /dev/disk/by-id

qm set 100 -scsi0 /dev/disk/by-id/nvme-KIOXIA-EXCERIA_G2_SSD_329FC1MIFM45
```

# 4. lxc

## 4.1. LXC容器添加cgroup参数
```shell
cd /etc/pve/lxc
cat 101.conf

# lxc add config
cat << EOF >> /etc/pve/lxc/101.conf 
lxc.cgroup.devices.allow: a
lxc.cap.drop:
lxc.cgroup2.devices.allow: c 10:200 rwm
EOF
```

## 4.2. 启动lxc容器
```shell
# 查看lxc容器列表
pct list

# 启动lxc容器
pct start 100

# 从pve的shell中进入lxc容器
pct enter 100
```

## 4.3. 修改 apt 源
```shell
cat /etc/apt/sources.list
cp /etc/apt/sources.list /etc/apt/sources.list.bak

# replace source
cat << EOF > /etc/apt/sources.list 
deb https://mirrors.ustc.edu.cn/debian bookworm main contrib
deb https://mirrors.ustc.edu.cn/debian bookworm-updates main contrib
deb https://mirrors.ustc.edu.cn/debian-security bookworm-security main contrib
EOF

# check
cat /etc/apt/sources.list

# update
apt-get update && apt-get upgrade

# install
apt install -y vim
```

## 4.4. 配置ssh可用密码登录
```shell
# backup conf
cp /etc/ssh/sshd_config /etc/ssh/sshd_config.bak

# change ssh conf
sed -i 's;#PubkeyAuthentication yes;PubkeyAuthentication yes;g' /etc/ssh/sshd_config
sed -i 's;#PasswordAuthentication yes;PasswordAuthentication yes;g' /etc/ssh/sshd_config
sed -i 's;#PermitRootLogin prohibit-password;PermitRootLogin yes;g' /etc/ssh/sshd_config
sed -i 's;#AuthorizedKeysFile;AuthorizedKeysFile;g' /etc/ssh/sshd_config

# restart ssh service
systemctl restart sshd
```

## 4.5. 生成ssh私钥
```shell
ls -al ~/.ssh

# gen ssh keys
ssh-keygen -t rsa -b 4096 -C "ei13911468370@gmail.com"

# check
ls -al ~/.ssh

git config --global user.name "ei13911468370"
git config --global user.email "ei13911468370@gmail.com"
```

## 4.6. 安装docker环境
```shell
apt install -y curl git tmux wget

# 开科学，安装 docker
curl -sSL https://get.docker.com/ | sh

# 安装docker-compose
curl -L https://github.com/docker/compose/releases/latest/download/docker-compose-Linux-x86_64 >  /usr/local/bin/docker-compose

chmod +x /usr/local/bin/docker-compose
# 如下两条命令是避免docker-compose重启lxc容器后失效
echo "export PATH=\$PATH:/usr/local/bin" >>  /etc/profile
echo "source /etc/profile" >>  ~/.bashrc && source ~/.bashrc
```

# 5. 安装Go环境
```shell
cd $HOME
wget https://go.dev/dl/go1.24.5.linux-amd64.tar.gz
# 解压到 /usr/local
tar -C /usr/local -xzf go1.24.5.linux-amd64.tar.gz

# 添加 go 环境变量
cat << EOF >> $HOME/.bashrc 
# Go Env
export GOROOT=/usr/local/go
export GOPATH=\$HOME/go
export PATH=\$PATH:\$GOROOT/bin:\$GOPATH/bin
export GO111MODULE=on

EOF

tail  $HOME/.bashrc

# check
source $HOME/.bashrc
go version
go env
```

# 6. 修改 hosts
```shell
cat << EOF >> /etc/hosts 

# GitHub Hosts Start
# Test1：Query ip by ipaddress.com (20211204):
#                     - https://websites.ipaddress.com/github.com
#                     - https://websites.ipaddress.com/github.global.ssl.fastly.net
#                     - https://websites.ipaddress.com/assets-cdn.github.com
140.82.114.4 	github.com
151.101.1.194 	github.global.ssl.fastly.net
185.199.108.153	assets-cdn.github.com

EOF

cat /etc/hosts
```

# 7. 安装 VS Code Server 服务
下载并安装最新版 VS Code Server
```shell
# 下载并安装最新版 VS Code Server
curl -Lk 'https://code.visualstudio.com/sha/download?build=stable&os=cli-alpine-x64' --output vscode_cli.tar.gz
tar -xf vscode_cli.tar.gz
mv code /usr/local/bin/
rm vscode_cli.tar.gz

# 启动 VS Code Server（默认端口 8000）
# code tunnel --accept-server-license-terms
```

```shell
# 允许 VS Code Tunnel 端口
ufw allow 8000
ufw allow 22

```

创建 systemd 服务文件
```shell
vi /etc/systemd/system/vscode-server.service
```
文件内容
```shell
[Unit]
Description=VS Code Server
After=network.target

[Service]
Type=simple
User=root
ExecStart=/usr/local/bin/code tunnel --accept-server-license-terms
Restart=always
RestartSec=3

# 日志管理（可选）
StandardOutput=file:/var/log/vscode-server.log
StandardError=file:/var/log/vscode-server-error.log

[Install]
WantedBy=multi-user.target
```

设置权限并启用服务
```shell
# 修改服务文件权限
chmod 644 /etc/systemd/system/vscode-server.service

# 重载 systemd
systemctl daemon-reload

# 启用开机自启
systemctl enable vscode-server.service

# 立即启动服务
systemctl start vscode-server.service
```

验证服务状态
```shell
# 检查服务状态
systemctl status vscode-server.service

# 查看日志（如果配置了日志文件）
tail -f /var/log/vscode-server.log
```