#!/bin/bash

#
# Update local ssl cert
#
# dependencies: acme.sh, nginx, php7


MY_DOMAIN_1='eisenhao.cn'
MY_DOMAIN_ROOT_1='/home/git/blog'
MY_DOMAIN_2='sea.eisenhao.cn'
MY_DOMAIN_ROOT_2='/usr/share/nginx/html/'
INSTALL_TO_EXT_PATH='true'


# FIXED ENV
NGINX_CONF_PATH='/etc/nginx/nginx.conf'
TMP_BACKUP_PATH='/tmp/nginx.conf'
ACME_CMD='/root/.acme.sh/acme.sh'
EXT_CERT_PATH='/root/cert'


function check_open_firewall_port() {
    local port=$1MY_DOMAIN_ROOT_1
    local ret=$()

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
        echo "src_file: $src_file is not existed!!!"
        exit 1
    fi

    echo -e "\nBackup file '$src_file' > '$dst_file'"
    cp $src_file $dst_file
}


function restore_file() {
    local src_file=$1
    local dst_file=$2
    
    if [ ! -f $src_file ]; then
        echo "src_file: $src_file is not existed!!!"
        exit 1
    fi

    echo -e "\nRestore file '$src_file' > '$dst_file'"
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
}


function restart_nginx() {
    echo -e "\nRestart nginx..."
    echo "systemctl restart nginx.service php7.4-fpm.service"
    # systemctl restart nginx.service php7.4-fpm.service
    systemctl status nginx.service php7.4-fpm.service | grep 'Active:'
}


function install_new_cert_to_external_path() {
    local my_domain=$1
    local external_cert_path=$2

    echo -e "\nInstall new cert to external path"
    $ACME_CMD --install-cert -d $my_domain --key-file $external_cert_path/key.pem --fullchain-file $external_cert_path/cert.pem --reloadcmd "service nginx force-reload"
}


function try_update_cert() {
    local my_domain=$1
    local my_domain_root=$2
    local ret='1'
    echo -e "\n================== Before update ===================="
    $ACME_CMD --list -d $my_domain | egrep 'Domain|TimeStr'
    echo "====================================================="

    # check and open port 80
    check_open_firewall_port '80'

    # backup old nginx config
    backup_file "$NGINX_CONF_PATH" "$TMP_BACKUP_PATH"

    # replace nginx config
    rewrite_nginx_config "$my_domain" "$my_domain_root" "$NGINX_CONF_PATH"

    restart_nginx

    sleep 2

    # update target domain cert
    echo -e "\nUpdate $my_domain domain cert ..."
    $ACME_CMD  --issue  -d $my_domain --webroot $my_domain_root  --standalone --httpport 80 -k ec-256 --server letsencrypt
    ret=$?

    # restore old nginx config
    restore_file "$TMP_BACKUP_PATH" "$NGINX_CONF_PATH"

    restart_nginx

    echo -e "\n================== After update ===================="
    $ACME_CMD --list -d $my_domain | egrep 'Domain|TimeStr'
    echo "===================================================="

    if [ "$ret" != "2" ]; then
        echo -e "\n\n domain $my_domain No need to update, skip refresh :D"
    elif [ "$ret" != "0" ]; then
        echo -e "\n\n update $my_domain domain cert FAILED !!!"
    else
        if [ "$INSTALL_TO_EXT_PATH" == 'true' ]; then
            install_new_cert_to_external_path "$my_domain" "$EXT_CERT_PATH"
        fi
        echo -e "\n\n update $my_domain domain cert SUCCESS ^_^"
        echo "Done."
    fi
}


function main() {
    try_update_cert "$MY_DOMAIN_1" "$MY_DOMAIN_ROOT_1"
    sleep 3
    try_update_cert "$MY_DOMAIN_2" "$MY_DOMAIN_ROOT_2"
}

main
