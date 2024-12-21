#!/bin/bash

##################################################
#
# Update local ssl cert
#
# dependencies: acme.sh, nginx, php7
# create date: 2023-12-23 11:46
# update date: 2024-12-21 10:35
#
##################################################


DOMAIN_1='your.domain1'
DOMAIN_1_ROOT_DIR='/home/git/blog'
DOMAIN_2='your.domain2'
DOMAIN_2_ROOT_DIR='/usr/share/nginx/html/'


# FIXED ENV
NGINX_CONF_PATH='/etc/nginx/nginx.conf'
TMP_BACKUP_PATH='/tmp/nginx.conf'
ACME_CMD='/root/.acme.sh/acme.sh'
EXT_CERT_PATH='/root/cert'
EXT_CERT_PATH2='/etc/v2ray-agent/tls'
ACME_CERT_DIR='/root/.acme.sh'


function check_open_a_firewall_port() {
    local port=$1

    iptables -n -L | egrep ":$port$" > /dev/null
    # open this port when not opened
    if [ "$?" == "1" ]; then
        iptables -A INPUT -p tcp --dport $port -j ACCEPT
        iptables-save > /etc/iptables.up.rules
    fi
}


function backup_file() {
    local src_file=$1
    local dst_file=$2

    if [ ! -f $src_file ]; then
        echo -e "\033[31mErr src_file '$src_file' is not existed!!!\033[0m"
        exit 1
    fi

    echo -e "\033[32m\nBackup file '$src_file' > '$dst_file' ...\033[0m"
    cp $src_file $dst_file
}


function restore_file() {
    local src_file=$1
    local dst_file=$2

    if [ ! -f $src_file ]; then
        echo -e "\033[31mErr src_file '$src_file' is not existed!!!\033[0m"
        exit 1
    fi

    echo -e "\033[32m\nRestore file '$src_file' > '$dst_file' ...\033[0m"
    cp $src_file $dst_file
}


function rewrite_nginx_config() {
    local tmp_domain=$1
    local tmp_domain_root=$2
    local tmp_nginx_conf_path=$3

    if [ ! -f $tmp_nginx_conf_path ]; then
        touch $tmp_nginx_conf_path
    fi

cat <<EOF > $tmp_nginx_conf_path
user www-data;
worker_processes auto;
pid /run/nginx.pid;
include /etc/nginx/modules-enabled/*.conf;
events {
    worker_connections 768;
}
http {
    sendfile on;
    tcp_nopush on;
    types_hash_max_size 2048;
    include /etc/nginx/mime.types;
    default_type application/octet-stream;
    ssl_protocols TLSv1 TLSv1.1 TLSv1.2 TLSv1.3;
    ssl_prefer_server_ciphers on;
    access_log /var/log/nginx/access.log;
    error_log /var/log/nginx/error.log;
    gzip on;
    gzip_vary on;
    gzip_proxied any;
    gzip_comp_level 6;
    gzip_buffers 16 8k;
    gzip_http_version 1.1;
    gzip_types text/plain text/css application/json application/javascript text/xml application/xml application/xml+rss text/javascript;
    include /etc/nginx/conf.d/*.conf;
    include /etc/nginx/sites-enabled/*;
    # Config only for update cert
    server {
        listen 80;
        listen [::]:80;
        charset utf-8;
        server_name ${tmp_domain};
        root   ${tmp_domain_root};
        index index.html index.php index.htm;
    }
}
EOF

    # Option
    # echo -e "\033[32m\n================== Debug rewrite_nginx_config '$tmp_nginx_conf_path' ====================\033[0m"
    # cat $tmp_nginx_conf_path
    # echo "===================================================="
}


function restart_nginx() {
    echo -e "\033[32m\nRestart nginx...\033[0m\n     ----------------------------\n"
    systemctl status nginx.service php7.4-fpm.service | grep 'Active:'
    echo -e "\n     ----------------------------\n"
    echo "     systemctl restart nginx.service php7.4-fpm.service"
    systemctl restart nginx.service php7.4-fpm.service
    systemctl status nginx.service php7.4-fpm.service | grep 'Active:'
    echo -e "\n     ----------------------------\n"
}


function install_new_cert_to_external_path() {
    local my_domain=$1
    local external_cert_path=$2

    if [ -z "$my_domain" ]; then
        echo -e "\033[31mNotice func install_new_cert_to_external_path() with an empty my_domain param, skip it\033[0m"
        return 1
    fi
    if [ -z "$external_cert_path" ]; then
        echo -e "\033[31mNotice func install_new_cert_to_external_path() with an empty external_cert_path param, skip it\033[0m"
        return 1
    fi

    echo -e "\033[32m\nInstall new cert to external path '$external_cert_path' ...\033[0m"
    $ACME_CMD --install-cert -d $my_domain --key-file "$external_cert_path/$my_domain.key" --fullchain-file "$external_cert_path/$my_domain.crt" --reloadcmd "service nginx force-reload"
}


function try_update_cert() {
    local my_domain=$1
    local my_domain_root=$2
    local install_to_ext_path=$3
    local ret='1'

    echo -e "\n================== Before update ===================="
    $ACME_CMD --list -d $my_domain | egrep 'Domain|TimeStr'
    echo "====================================================="

    # check and open port 80
    check_open_a_firewall_port '80'

    # backup old nginx config
    backup_file "$NGINX_CONF_PATH" "$TMP_BACKUP_PATH"

    # replace nginx config
    rewrite_nginx_config "$my_domain" "$my_domain_root" "$NGINX_CONF_PATH"

    restart_nginx

    sleep 2

    # (option) remove cron job
    # $ACME_CMD --uninstall-cronjob

    # remove old cert
    echo -e "\033[32m\nRemove old $my_domain domain cert ...\n\033[0m"
    $ACME_CMD --remove -d $my_domain
    echo -e "\033[32m\nDelete old $my_domain domain cert files '$ACME_CERT_DIR/${my_domain}*' ...\nrm -rf $ACME_CERT_DIR/${my_domain}*\n\033[0m"
    rm -rf $ACME_CERT_DIR/${my_domain}*

    # Create target domain cert
    echo -e "\033[32m\nCreate $my_domain domain cert ...\033[0m\nExec:\n=================================\n$ACME_CMD  --issue  -d $my_domain --webroot $my_domain_root  --standalone --httpport 80 -k ec-256 --server letsencrypt\n=================================\n"
    $ACME_CMD  --issue  -d $my_domain --webroot $my_domain_root  --standalone --httpport 80 -k ec-256 --server letsencrypt
    ret=$?

    # check
    if [ "$ret" == "2" ]; then
        echo -e "\033[32m\n\nNotice domain $my_domain No need to update, skip refresh :D\033[0m"
    elif [ "$ret" != "0" ]; then
        echo -e "\033[31m\n\nUpdate $my_domain domain cert FAILED !!!\033[0m"
    elif [ "$ret" == "0" ]; then
        if [ ! -z "$install_to_ext_path" ]; then
            install_new_cert_to_external_path "$my_domain" "$install_to_ext_path"
        fi
        echo -e "\033[32m\n\nUpdate $my_domain domain cert SUCCESS ^_^\033[0m"
    fi

    echo -e "\n================== After update ===================="
    $ACME_CMD --list -d $my_domain | egrep 'Domain|TimeStr'
    echo "===================================================="

    # restore old nginx config
    echo -e "\033[32m\n\nRestore old nginx config, and restart nginx \033[0m"
    restore_file "$TMP_BACKUP_PATH" "$NGINX_CONF_PATH"

    restart_nginx
}


function main() {
    try_update_cert "$DOMAIN_1" "$DOMAIN_1_ROOT_DIR" "$EXT_CERT_PATH"
    sleep 3
    try_update_cert "$DOMAIN_2" "$DOMAIN_2_ROOT_DIR" "$EXT_CERT_PATH2"
}

main
