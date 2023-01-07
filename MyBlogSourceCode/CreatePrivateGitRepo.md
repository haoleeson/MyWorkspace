搭建远程Git私库

<!-- 依赖项：
```shell
git --version
yum install curl-devel expat-devel gettext-devel openssl-devel zlib-devel perl-devel
yum install -y git
``` -->

# 1. 在Remote Host创建git私库

## 1.1. 调整防火墙

打开 HTTP（80）和 HTTPS（443）端口

```shell
iptables -A INPUT -p tcp --dport 80 -j ACCEPT
iptables -A INPUT -p tcp --dport 443 -j ACCEPT

# check
iptables -n -L

# 配置开机启动
iptables-save > /etc/iptables.up.rules

/etc/init.d/ssh restart
```

## 1.2. 安装 PHP7.4
```shell
# 添加 SURY PHP PPA 存储库
sudo apt -y install lsb-release apt-transport-https ca-certificates 
sudo wget -O /etc/apt/trusted.gpg.d/php.gpg https://packages.sury.org/php/apt.gpg
echo "deb https://packages.sury.org/php/$(lsb_release -sc) main" | sudo tee /etc/apt/sources.list.d/php.list
# 更新添加的存储库上的系统软件包列表
sudo apt update
# 安装 php7.4 和相关插件（Debian 11）
sudo apt install -y php7.4-cli php7.4-fpm php7.4-cgi php7.4-mysql php7.4-curl php7.4-json php7.4-mbstring php7.4-imagick php7.4-xml php7.4-zip php7.4-opcache
# 卸载
#sudo apt-get remove --purge -y php7.4-cli php7.4-fpm php7.4-cgi php7.4-mysql php7.4-curl php7.4-json php7.4-mbstring php7.4-imagick php7.4-xml php7.4-zip php7.4-opcache
```

## 1.3. 安装 Nginx
因为 Nginx 在 Debian 的默认存储库中可用，所以可以使用 apt 打包系统从这些存储库安装它。
```shell
sudo apt update
sudo apt install nginx

# 解决 systemd 在执行 ExecStart 启动过快导致 parse PID 失败
mkdir /etc/systemd/system/nginx.service.d
printf "[Service]\nExecStartPost=/bin/sleep 0.1\n" > /etc/systemd/system/nginx.service.d/override.conf
systemctl daemon-reload
service nginx restart

# check
service nginx status

# 创建 站点目录
mkdir -p /var/www/html/
echo 'Hello world!' > /var/www/html/index.html
chmod -R 777 /var/www/html/

# 修改 nginx 配置文件 (my_nginx_for_private_git_repo.config)
vi /etc/nginx/nginx.conf

# 检查 nginx 与 php-fpm 服务运行库状态
systemctl status nginx.service php7.4-fpm.service
systemctl restart nginx.service php7.4-fpm.service

# 浏览器测试
http://A.B.C.D/index.html
```

## 1.4. 创建 git 用户及属组
```shell
# 
groupadd git
useradd -m git -g git -s /bin/bash -d /home/git
passwd git

# 切换到git用户（这步很重要）
su git
```

## 1.5. 配置git仓库
```shell
# 创建git私库目录
mkdir -p $HOME/blog
mkdir -p $HOME/repos
cd $HOME/repos

# 初始化一个裸露的仓库
git init --bare blog.git

# 创建 hook 钩子函数，输入了内容如下
vi $HOME/repos/blog.git/hooks/post-receive

#!/bin/sh
git --work-tree=/home/git/blog --git-dir=/home/git/repos/blog.git checkout -f

# 增加执行权限
chmod +x $HOME/repos/blog.git/hooks/post-receive

# 退出到 root 账号
exit

# 更改仓库所属用户
sudo chown -R git:git /home/git/repos/blog.git
```

# 2. 测试
## 2.1. 建立ssh信任关系
```shell
server_ip='A.B.C.D'

# 上传本机公钥（需输入刚创建的远端 git 用户密码），以免密登录
ssh-copy-id -i ~/.ssh/id_rsa.pub git@$server_ip
```

## 2.2. 测试git仓库是否可用，如果能把空仓库拉下来，就说明 git 仓库搭建成功了
```shell
git clone git@$server_ip:/home/git/repos/blog.git

# check
cd blog; git remote -v
```


# 3. 取消Remote Host中git账户的Shell登录权限，仅支持git pull/push
```shell
# 若 /etc/shells 中无 git shell，则追加
grep git-shell /etc/shells; [ "$?" -eq "1" ] && echo "$(which git-shell)" >> /etc/shells

# 修改 /etc/passwd 中 git 账户权限
# 将原来的
git:x:1000:1000::/home/git:/bin/bash

# 修改为
git:x:1000:1000:,,,:/home/git:/usr/bin/git-shell
```

# 4. 修改 nginx 中 root 解析路径
vi /etc/nginx/nginx.conf

```shell
# 替换
root   /var/www/html;

# 换为 git 私库地址
root /home/git/blog;

# 重启 nginx
systemctl restart nginx.service
```

# 5. 在 Hexo/_config.yml 中 deploy 中添加私库 repo
```yml
deploy:
  # Website Pages
  - type: git
    repo: git@github.com:XXX.git
    branch: master
  # My Git
  - type: git
    repo: git@A.B.C.D:/home/git/repos/blog.git
    branch: master
```
