WordPress 建站
参考：
- [Debian 安装 WordPress 全过程](https://blog.csdn.net/u010900996/article/details/119935233)
- [【Debian 10】树莓派上极速搭建 WordPress](https://blog.csdn.net/weixin_42200613/article/details/124126598)
# 1. 调整防火墙
打开 HTTP（80）和 HTTPS（443）端口
```shell
iptables -A INPUT -p tcp --dport 80 -j ACCEPT
iptables -A INPUT -p tcp --dport 443 -j ACCEPT
iptables -A INPUT -p tcp --dport 8443 -j ACCEPT
iptables -A INPUT -p tcp --dport 9098 -j ACCEPT
# check
iptables -n -L
iptables-save > /etc/iptables.up.rules
/etc/init.d/ssh restart
```
# 2. 安装 Nginx
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
```
# 3. 安装 MariaDB
```shell
sudo apt install mariadb-server
# 卸载
#sudo apt-get remove --purge -y mariadb-server
输入如下命令配置 root 密码
mysql_secure_installation
配置 WordPress 数据库
mysql -uroot
创建一个数据库用户
create user 'wordpress'@'localhost' identified by 'wordpress';
创建一个数据库
create database wordpress default charset utf8 collate utf8_general_ci;
授予权限
grant all privileges on wordpress.* to 'wordpress'@'localhost';
刷新权限并退出
flush privileges;
exit
```
# 4. 安装 PHP7.4
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
# 5. 安装证书（支持https）
利用开源 acme 工具生成证书（[acme 操作说明](https://github.com/acmesh-official/acme.sh/wiki/%E8%AF%B4%E6%98%8E)）
- 下载 [acme.sh](https://github.com/acmesh-official/acme.sh)
```shell
curl https://get.acme.sh | sh -s email=ei13911468370@gmail.com
```

## 5.1. 【推荐，可自动更新】Option1: 通过 http 方式自动生成证书
```shell
MY_DOMAIN='eisenhao.cn'
# 方式 1.a: http 方式验证
acme.sh --issue -d $MY_DOMAIN --nginx
# 方式 1.b: http 方式之 Webroot 模式验证
acme.sh --issue -d $MY_DOMAIN --webroot /home/git/blog/

# 方式 1.c:【亲测可行】 http 方式之 standalone 模式验证（需将 nginx 中服务的 port 设置为 80，并关闭对应的 ssl 的服务 ）
#acme.sh  --issue  -d $MY_DOMAIN  --standalone --httpport 8443
acme.sh  --issue  -d $MY_DOMAIN --webroot /home/git/blog/  --standalone --httpport 80 -k ec-256 --server "letsencrypt"

# 方式 1.d: http 方式之 standalone tls alpn 模式验证（用 443 端口）
acme.sh  --issue  -d $MY_DOMAIN  --alpn
acme.sh  --issue  -d $MY_DOMAIN  --alpn --tlsport 8443
```

## 5.2. Option2: 通过手动在域名上添加一条 txt 解析记录, 验证域名所有权（坏处，无法自动更新证书）
```shell
MY_DOMAIN='eisenhao.cn'
# 方式1：手动添加一条TXT解析记录
# 方式1：setp1. 生成相应的解析记录显示出来（ Domain: 'XXXX'; TXT value: 'YYYY'）
acme.sh --issue --dns -d $MY_DOMAIN --yes-I-know-dns-manual-mode-enough-go-ahead-please
# 方式1：setp2. 登录云解析厂商，在域名云解析控制台添加 TXT 解析记录
 Domain: 'XXXXXX.eisenhao.cn'
 TXT value: 'YYYYY'
# 方式1：step3. 等待解析后，重新生成证书（--renew）
## 生成证书位置：~/.acme.sh/<your_domain>/
acme.sh --renew -d $MY_DOMAIN --yes-I-know-dns-manual-mode-enough-go-ahead-please
# 方式2：配置解析商的自动集成
# 方式2： setp1. 登录云解析厂商，查看 api id 和 api key （e.g. DnsPod 中 APPID 和 SecretKey）
export DP_Id="1234"
export DP_Key="ABCDE"
acme.sh --issue --dns dns_dp -d $MY_DOMAIN
```

## 5.3. copy/安装 证书
```shell
# 创建存放证书路径（注意 nginx 配置中 ssl 会用到）
CERT_PATH='/root/cert'
mkdir -p $CERT_PATH
# 安装证书到指定路径
acme.sh --install-cert -d $MY_DOMAIN \
    --key-file       $CERT_PATH/key.pem  \
    --fullchain-file $CERT_PATH/cert.pem \
    --reloadcmd     "service nginx force-reload"

# 查看已安装证书信息
acme.sh --list -d $MY_DOMAIN
```

## 手动更新指定域名的证书
```shell
MY_DOMAIN='eisenhao.cn'

# check domain period of validity
acme.sh --list -d $MY_DOMAIN

# update acme.sh manually
acme.sh --upgrade
# or set auto update acme.sh
acme.sh --upgrade --auto-upgrade

# edit nginx conf (comment(stop) ssl server)
vi /etc/nginx/nginx.conf
systemctl restart nginx.service php7.4-fpm.service
systemctl status nginx.service php7.4-fpm.service

# try1: renew all certs
acme.sh --renew-all --force

# try2: update target domain cert manually ( acme only support 80 and 443 ports)
acme.sh  --issue  -d $MY_DOMAIN --webroot /home/git/blog/  --standalone --httpport 80 -k ec-256 --server "letsencrypt"

# update cert
acme.sh --renew -d $MY_DOMAIN -d $MY_DOMAIN2 --force

# install new cert to external path
acme.sh --install-cert -d $MY_DOMAIN \
    --key-file       $CERT_PATH/key.pem  \
    --fullchain-file $CERT_PATH/cert.pem \
    --reloadcmd     "service nginx force-reload"

# edit nginx conf (uncomment(start) ssl server)
vi /etc/nginx/nginx.conf
systemctl restart nginx.service php7.4-fpm.service
systemctl status nginx.service php7.4-fpm.service

# 配置 crontab 定时任务
#* 1 1 *  *  acme.sh --renew-all --force
# crontab -l
```

# 6. 修改 nginx 配置文件
vi /etc/nginx/nginx.conf

# 7. 拷贝配置模板，并替换以下内容
cp /var/www/html/wp-config-sample.php /var/www/html/wp-config.php
```shell
/** The name of the database for WordPress */
define( 'DB_NAME', 'wordpress' );
/** Database username */
define( 'DB_USER', 'wordpress' );
/** Database password */
define( 'DB_PASSWORD', 'wordpress' );
/** Database hostname */
define( 'DB_HOST', 'localhost' );
/** Database charset to use in creating database tables. */
define( 'DB_CHARSET', 'utf8' );
/** The database collate type. Don't change this if in doubt. */
define( 'DB_COLLATE', '' );
define("FS_METHOD","direct");
define("FS_CHMOD_DIR", 0777);
define("FS_CHMOD_FILE", 0777);
```
注：后三行为解决 WordPress 安装主题/插件提示输入 FTP 帐号的问题

# 8. 创建 index.html
```shell
echo 'Hello world!' > /var/www/html/index.html
```
# 9. 检查 nginx 与 php-fpm 服务运行库状态
```shell
systemctl status nginx.service php7.4-fpm.service
systemctl restart nginx.service php7.4-fpm.service
```
# 10. 浏览器配置
http://A.B.C.D/
http://A.B.C.D/readme.html
http://A.B.C.D/index.php
http://A.B.C.D/index.html
http://A.B.C.D/wp-admin/install.php
http://A.B.C.D/wp-admin/setup-config.php