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
dns_cloudflare_api_token = <your_cloudflare_api_token_here>
EOF
chmod 600 /root/.secrets/cloudflare.ini

# 申请证书（替换域名和邮箱）
certbot certonly \
  --dns-cloudflare \
  --dns-cloudflare-credentials /root/.secrets/cloudflare.ini \
  -d <your_domain> \
  --cert-name mydomaincert \
  --email <your_email> \
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
    # 强制 HTTP → HTTPS（可选）
    # server {
    #     listen 80;
    #     server_name <your_domain>;
    #     return 301 https://$server_name$request_uri;
    # }

    # 强制使用IPv4解析，避免可能出现的连接问题
    resolver 223.5.5.5 119.29.29.29 ipv6=off;

    # HTTPS 主服务
    server {
        # 同时监听 IPv4 65431 和 IPv6 的 65432 端口 (SSL)
        listen 65431 ssl;
        listen [::]:65432 ssl;
        http2 on;
        server_name <your_domain>;

        # SSL 证书路径
        ssl_certificate     /etc/letsencrypt/live/mydomaincert/fullchain.pem;
        ssl_certificate_key /etc/letsencrypt/live/mydomaincert/privkey.pem;

        # 通用代理头
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto $scheme;

        # ===== 路径分发 =====

        # RSSHub
        location /rss/ {
            proxy_pass http://<your_inner_svr_ip>:1200/;
            # 如果 RSSHub 不认识 /rss 前缀，去掉前缀再转发：
            # rewrite ^/rss(/.*)$ $1 break;
            # proxy_pass http://127.0.0.1:1200;
        }

        # 飞牛 NAS 管理页
        location /fnos/ {
            proxy_pass https://<your_inner_svr_ip>:5667/;
            # 支持 WebSocket（飞牛可能需要）
            #proxy_http_version 1.1;
            #proxy_set_header Upgrade $http_upgrade;
            #proxy_set_header Connection "upgrade";
        }

        # 爱快路由器
        location /ikuai/ {
            proxy_pass http://<your_inner_svr_ip>/;
            # 爱快可能不认子路径，需要重写
            #rewrite ^/ikuai(/.*)$ $1 break;
            #proxy_set_header Host $host;
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
- 访问 https://<your_domain>:65431/rss/weibo/user/1727858283 应该能看到微博博主宝玉xp文章的RSS输出
- 访问 https://<your_domain>:65431/fnos/ 应该能看到飞牛NAS的登录界面
- 访问 https://<your_domain>:65431/ikuai/ [未开启外链访问]应该能看到爱快路由器的登录界面
## IPv6
- 访问 https://<your_domain>:65432/rss/weibo/user/1727858283 应该能看到微博博主宝玉xp文章的RSS输出
- 访问 https://<your_domain>:65432/fnos/ 应该能看到飞牛NAS的登录界面
- 访问 https://<your_domain>:65432/ikuai/ [未开启外链访问]应该能看到爱快路由器的登录界面

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
