搭建远程Git私库

依赖项：
```shell
git --version
yum install curl-devel expat-devel gettext-devel openssl-devel zlib-devel perl-devel
yum install -y git
```

# 1. 在Remote Host创建git私库

## 1.1. 调整防火墙

打开 HTTP（80）和 HTTPS（443）端口

```shell
iptables -A INPUT -p tcp --dport 80 -j ACCEPT

iptables -A INPUT -p tcp --dport 443 -j ACCEPT

iptables-save > /etc/iptables.up.rules

/etc/init.d/ssh restart
```

## 1.2. 安装 Nginx
因为 Nginx 在 Debian 的默认存储库中可用，所以可以使用 apt 打包系统从这些存储库安装它。
```shell
sudo apt update
sudo apt install nginx

# 修改 nginx 配置文件
vi /etc/nginx/nginx.conf

# 检查 nginx 服务运行库状态
systemctl status nginx.service

# 创建 index.html
mkdir -p /var/www/html/
echo 'Hello world!' > /var/www/html/index.html
chmod -R 777 /var/www/html/

# 浏览器测试
http://A.B.C.D/index.html
```

## 1.3. 创建 git 用户及属组
```shell
# 
groupadd git
useradd -m git -g git -s /bin/bash -d /home/git
passwd git

# 切换到git用户（这步很重要）
su git
```

## 1.4. 配置git仓库
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