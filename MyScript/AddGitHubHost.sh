#!/bin/bash
# Test From ipaddress.com
# Test Time: 2020-11-30
# Fresh DNS
# Windows: ipconfig /flushdns
# Ubuntu: sudo systemctl restart nscd
# Mac: sudo killall -HUP mDNSResponder

HOSTS_FILE="/etc/hosts"
CHOWN="/usr/sbin/chown"

###############################################################
# 将 GitHub 的 Hosts 写入 /etc/hosts 文件
###############################################################
funcAddGitHubHosts() {
    # 判断是否添加过最新 GitHub Hosts
    local ret=$(cat ${HOSTS_FILE} | grep "GitHub Hosts Start 20201130")
    if [[ -z "$ret" ]]; then
        # 暂时将 hosts 文件的所属用户改为当前用户
        sudo $CHOWN $USER ${HOSTS_FILE}
        # 追加 GitHub Hosts 到 hosts文件
        echo '
# GitHub Hosts Start
# Query ip from www.ipaddress.com/ip-lookup on 20210604
199.232.69.194 github.global.ssl.fastly.net
140.82.112.3 github.com
140.82.114.4 www.github.com
140.82.114.4 gist.github.com
185.199.110.133 raw.github.com
185.199.108.153 assets-cdn.github.com
185.199.108.153 documentcloud.github.com
185.199.108.154 help.github.com
140.82.114.9 nodeload.github.com
140.82.113.17 status.github.com
185.199.109.153 training.github.com
185.199.110.133 camo.githubusercontent.com
185.199.108.133 cloud.githubusercontent.com
185.199.108.133 gist.githubusercontent.com
185.199.111.133 raw.githubusercontent.com
185.199.110.133/22 avatars0.githubusercontent.com
185.199.110.133/22 avatars1.githubusercontent.com
185.199.110.133/22 avatars2.githubusercontent.com
185.199.110.133/22 avatars3.githubusercontent.com
# GitHub Hosts End
' >> ${HOSTS_FILE}
        # 刷新 DNS (Mac OS X v10.10.4 or later)
        sudo killall -HUP mDNSResponder
        echo '\033[1;36m Successfully added GitHub Hosts:)
        \033[0m'
        # 恢复所属用户 root
        sudo $CHOWN root ${HOSTS_FILE}
        return 0
    fi
    echo '\033[1;36m You has added GitHub Hosts before, no need to add again.
        \033[0m'
    return 1
}


# 将 GitHub 的 Hosts 写入 /etc/hosts 文件
funcAddGitHubHosts

