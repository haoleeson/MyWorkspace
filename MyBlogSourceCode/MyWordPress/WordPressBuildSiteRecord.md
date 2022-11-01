WordPress 建站

参考：
- [Debian 安装 WordPress 全过程](https://blog.csdn.net/u010900996/article/details/119935233)
- [【Debian 10】树莓派上极速搭建 WordPress](https://blog.csdn.net/weixin_42200613/article/details/124126598)

# 1. 调整防火墙

打开 HTTP（80）和 HTTPS（443）端口

```shell
iptables -A INPUT -p tcp --dport 80 -j ACCEPT

iptables -A INPUT -p tcp --dport 443 -j ACCEPT

iptables-save > /etc/iptables.up.rules

/etc/init.d/ssh restart
```

# 2. 安装 Nginx
因为 Nginx 在 Debian 的默认存储库中可用，所以可以使用 apt 打包系统从这些存储库安装它。
```shell
sudo apt update
sudo apt install nginx
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

<!-- 
# 安装 acme.sh
curl https://get.acme.sh | sh -s email=ei13911468370@gmail.com -->

# 5. 修改 nginx 配置文件
vi /etc/nginx/nginx.conf

# 6. 拷贝配置模板，并替换以下内容
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

# 7. 创建 index.html
```shell
echo 'Hello world!' > /var/www/html/index.html
```

# 8. 检查 nginx 与 php-fpm 服务运行库状态
```shell
systemctl status nginx.service php7.4-fpm.service
```

# 9. 浏览器配置
http://A.B.C.D/
http://A.B.C.D/readme.html
http://A.B.C.D/index.php
http://A.B.C.D/index.html
http://A.B.C.D/wp-admin/install.php
http://A.B.C.D/wp-admin/setup-config.php