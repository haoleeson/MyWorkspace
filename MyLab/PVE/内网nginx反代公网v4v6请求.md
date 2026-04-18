# 为内网分配固定IPv6地址
为内网准备用作nginx反代服务器的设备分配固定IPv6地址

## 1. iKuai IPv6 外网配置（WAN）
- 外网接口：`wan1`
- **接入方式**：`DHCPv6客户端（动态获取）`
- **请求前缀长度**：`自动`
- 强行获取前缀：关闭
- 客户端DUID标识：随机生成
- 确保获取到公网 IPv6 地址（如 `240e::/64` 开头）

## 2. iKuai IPv6 内网配置（LAN）
| 配置项 | 值 |
|--------|-----|
| 内网接口 | `lan1` |
| 配置类型 | `自动获取` |
| 绑定外网线路 | `wan1` |
| 前缀分配长度 | `自动` |
| DHCPv6 | `开启` |
| **DHCPv6 模式** | **`无状态`** |
| **RA 通告绑定** | **`开启`**（白名单关键） |
| IPv6 DNS | 留空或不开启 |

## 3. 前缀静态分配（为指定设备分配公网 IPv6）
- 进入：`网络设置` → `IPv6设置` → `前缀静态分配`
- 点击添加：
  - **终端本地链接 IPv6 地址**：填写准备用作nginx反代服务器 eth0 接口的本地链接IPv6 `fe80::` 地址（如 `fe80::abcd:1234:5678:cdef`）
  - **内网接口**：`lan1`
  - **外网线路**：`wan1`
- 保存后该设备将获得固定后缀的公网 IPv6 地址

## 4. iKuai 防火墙 ACL 规则（放行外网访问）
- 进入：`安全功能` → `ACL规则` → 添加
  | 配置项 | 值 |
  |--------|-----|
  | 协议栈 | `IPv6` |
  | 协议 | `任意` |
  | 动作 | `允许` |
  | 方向 | `进` |
  |连接方向匹配|原始方向|
  | 源地址 | 留空 |
  | 目的地址 | 开启后缀匹配，匹配内容为获取到的公网IPv6后缀 eg ::abcd:1234:5678:cdef/::64 |
- 注意：规则顺序靠前，确保匹配
- 反方向出方向再复制修改添加一条规则，允许内网设备访问公网 IPv6

## 5. ddns-go 配置（同步到 Cloudflare）
- **DNS 服务商**：`Cloudflare`
- **API Token**：具有编辑区域 DNS 权限的 Token （从 Cloudflare 控制台获取 API 令牌）
- **IPv4 启用**：`关闭`（本例仅需 IPv6）
- **IPv6 启用**：`开启`
  - **获取方式**：`通过网卡获取` → 选择 Nginx 服务器对应的网卡
- **Domains**：`<YOUR_DOMAIN>`（如`mydomain.com` 或子域名 `sub.mydomain.com`）
- 保存后域名将解析到设备的公网 IPv6 地址

# 安裝 nginx

## 申请SSL证书(certbot + DNS验证域名)
```shell
mkdir -p /root/mynginx/ssl

apt update
# 安装 certbot 的 Cloudflare 插件
apt install certbot python3-certbot-dns-cloudflare -y

# 创建 Cloudflare API 令牌文件
mkdir -p /root/.secrets/
cat > /root/.secrets/cloudflare.ini << EOF
dns_cloudflare_api_token = <YOUR_CLOUDFLARE_API_TOKEN>
EOF
chmod 600 /root/.secrets/cloudflare.ini

# 申请证书（替换域名和邮箱）
certbot certonly \
  --dns-cloudflare \
  --dns-cloudflare-credentials /root/.secrets/cloudflare.ini \
  -d <YOUR_DOMAIN> \
  --cert-name mydomaincert \
  --email <YOUR_EMAIL> \
  --agree-tos \
  --non-interactive


# 验证证书
certbot certificates

ls -l /etc/letsencrypt/live/mydomaincert/
# /etc/letsencrypt/live/mydomaincert/fullchain.pem
# /etc/letsencrypt/live/mydomaincert/privkey.pem


# 6. 重载 Nginx
systemctl reload nginx

# 7. 测试自动续期
certbot renew --dry-run
```




## nginx.conf
- 配置ssl证书路径为Certbot生成证书路径，Certbot 自动续期后，Nginx 重载即可使用新证书

```shell
events {
    worker_connections 1024;
}

http {
    # 强制使用IPv4解析，避免可能出现的连接问题
    resolver 223.5.5.5 119.29.29.29 ipv6=off;

    # HTTPS 融合服务
    server {
        # 同时监听 IPv4 <PORT1> 和 IPv6 的 <PORT2> 端口 (SSL)
        listen <PORT1> ssl;
        listen [::]:<PORT2> ssl;
        http2 on;
        server_name <YOUR_DOMAIN>;

        # SSL 证书路径
        ssl_certificate     /etc/letsencrypt/live/mydomaincert/fullchain.pem;
        ssl_certificate_key /etc/letsencrypt/live/mydomaincert/privkey.pem;

        # 可选：强化 SSL 安全配置
        ssl_protocols TLSv1.2 TLSv1.3;
        ssl_ciphers HIGH:!aNULL:!MD5;

        # 通用代理头
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto $scheme;

        # ===== 路径分发 (前置优先解析) =====
        # 爱快路由器
        location /ikuai/ {
            proxy_pass http://192.168.1.2/;
            # 爱快可能不认子路径，需要重写
            #rewrite ^/ikuai(/.*)$ $1 break;
            #proxy_set_header Host $host;
        }

        # RSSHub
        location /rss/ {
            proxy_pass http://192.168.1.3:1200/;
            # 如果 RSSHub 不认识 /rss 前缀，去掉前缀再转发：
            # rewrite ^/rss(/.*)$ $1 break;
        }
    }

     # HTTPS 飞牛服务
    server {
        # 仅监听 IPv4 和 IPv6 的 <PORT3> 端口 (SSL)
        listen [::]:<PORT3> ssl;
        http2 on;
        server_name <YOUR_DOMAIN>;

        ssl_certificate     /etc/letsencrypt/live/mydomaincert/fullchain.pem;
        ssl_certificate_key /etc/letsencrypt/live/mydomaincert/privkey.pem;

        ssl_protocols TLSv1.2 TLSv1.3;
        ssl_ciphers HIGH:!aNULL:!MD5;

        location / {
            proxy_pass https://192.168.1.3:5667/;
            proxy_set_header Host $host;
            proxy_set_header X-Real-IP $remote_addr;
            proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
            proxy_set_header X-Forwarded-Proto $scheme;

            # WebSocket 支持（飞牛可能用到）
            proxy_http_version 1.1;
            proxy_set_header Upgrade $http_upgrade;
            proxy_set_header Connection "upgrade";
        }
    }
}
```


## create容器
```bash
docker stop nginx-proxy; docker rm nginx-proxy

docker run -d \
  --name nginx-proxy \
  --restart always \
  --network host \
  -v /root/mynginx/nginx.conf:/etc/nginx/nginx.conf:ro \
  -v /etc/letsencrypt/:/etc/letsencrypt/:ro \
  nginx:latest

# check
docker logs --tail 50 -f nginx-proxy
```


# check
## IPv4
- 访问 https://<YOUR_DOMAIN>:<PORT1>/rss/weibo/user/1727858283 应该能看到微博博主宝玉xp文章的RSS输出
- 访问 https://<YOUR_DOMAIN>:<PORT1>/ikuai/ [未开启外链访问]应该能看到爱快路由器的登录界面
## IPv6
- 访问 https://<YOUR_DOMAIN>:<PORT2>/rss/weibo/user/1727858283 应该能看到微博博主宝玉xp文章的RSS输出
- 访问 https://<YOUR_DOMAIN>:<PORT2>/ikuai/ [未开启外链访问]应该能看到爱快路由器的登录界面
- 访问 https://<YOUR_DOMAIN>:<PORT3> 应该能看到飞牛NAS的登录界面

# iPhone 安装阿里公共DNS描述文件
> 解决手机4G流量DNS无法解析cloudflare域名问题
1. 步骤一：获取并安装描述文件
重要提示：代码中的 <string>YOUR-UNIQUE-UUID-HERE</string> 和 <string>YOUR-PROFILE-UNIQUE-UUID-HERE</string> 两处UUID需要替换为唯一值。你可以在这个UUID生成网站为它们各生成一个新的UUID，以确保配置文件能正常识别。
```xml
<?xml version=“1.0” encoding=“UTF-8”?>
<!DOCTYPE plist PUBLIC “-//Apple//DTD PLIST 1.0//EN” “http://www.apple.com/DTDs/PropertyList-1.0.dtd”>
<plist version=“1.0”>
<dict>
    <key>PayloadContent</key>
    <array>
        <dict>
            <key>DNSSettings</key>
            <dict>
                <key>DNSProtocol</key>
                <string>HTTPS</string>
                <key>ServerURL</key>
                <string>https://dns.alidns.com/dns-query</string>
                <key>ServerAddresses</key>
                <array>
                    <string>223.5.5.5</string>
                    <string>223.6.6.6</string>
                    <string>2400:3200::1</string>
                    <string>2400:3200:baba::1</string>
                </array>
            </dict>
            <key>PayloadDescription</key>
            <string>Configures DNS settings to use Alibaba Public DNS over HTTPS</string>
            <key>PayloadDisplayName</key>
            <string>AliDNS (DoH)</string>
            <key>PayloadIdentifier</key>
            <string>com.example.alidns.doh</string>
            <key>PayloadType</key>
            <string>com.apple.dnsSettings.managed</string>
            <key>PayloadUUID</key>
            <string>YOUR-UNIQUE-UUID-HERE</string>
            <key>PayloadVersion</key>
            <integer>1</integer>
        </dict>
    </array>
    <key>PayloadDescription</key>
    <string>Use Alibaba Public DNS over HTTPS</string>
    <key>PayloadDisplayName</key>
    <string>AliDNS (DoH)</string>
    <key>PayloadIdentifier</key>
    <string>com.example.alidns.doh.profile</string>
    <key>PayloadRemovalDisallowed</key>
    <false/>
    <key>PayloadType</key>
    <string>Configuration</string>
    <key>PayloadUUID</key>
    <string>YOUR-PROFILE-UNIQUE-UUID-HERE</string>
    <key>PayloadVersion</key>
    <integer>1</integer>
</dict>
</plist>
```
- 将文件保存为 .mobileconfig 扩展名，例如 AliDNS.mobileconfig。注意，扩展名一定要正确。
- 文件通过邮件附件发送给自己，或使用 AirDrop 传到手机上。
- 在手机上点击该文件，即可触发系统安装程序。
- 安装后在设置-通用-VPN&DNS&设备管理中可以看到已安装的配置文件，启用后即可使用阿里公共DNS的DoH服务。
- 安装完成后，建议重启一下iPhone，确保新的DNS设置在所有应用和网络环境下都能生效。
