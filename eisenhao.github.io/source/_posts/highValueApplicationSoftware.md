layout: post
title: 高效软件推荐
date: 2018/9/26 14:14:45
updated: 2018/9/28 0:22:45
comments: true
tags:
- 效率
categories:
- 效率

---
<img src="https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/highValueApplicationSoftware.jpg" class="full-image" />

# 1. **浏览器**
## 1.1. chrome
第三方搜集的Google官方离线包，Google Chrome下载地址：https://api.shuax.com/tools/getchrome

<!-- more -->

**必备插件**：
- Adblock Plus 屏蔽广告
- SearchPreview 网页预览
- Multi-highlight 网页关键字高亮
- Bilibili Helper: Bilibili.com Auxiliary 哔哩哔哩
- IDM Integration Module 使chrome支持IDM
- Video Speed Controller 网页视频倍速播放
- Cool Clock 网页时钟
- **Proxy SwitchyOmega 智能选择梯子类似：PAC**
  - Proxy SwitchyOmega插件官网：https://www.switchyomega.com/
  - 在chrome://extensions/ 中添加crx插件，注意先勾选Developer mode
  - **配合Shadowsockers使用，设置Proxy SwitchyOmega**
  - **VPN提供商服务器**<==443端口通讯==>**本地VPN软件**<==1080端口通讯==>**Proxy SwitchyOmega插件**<==其他未知通讯==>**chrome浏览器**
```
proxy:
	SOCKS5-->127.0.0.1-->1080  #即Proxy SwitchyOmega插件监听本地1080端口
auto switch:
	Rule list rules-->proxy
	Default-->Direct
	Rule List Config-->AutoProxy
	Rule List URL-->https://raw.githubusercontent.com/gfwlist/gfwlist/master/gfwlist.txt
```

常用Google链接：

```
- Google：https://www.google.com/ncr
- Google学术搜索：https://scholar.google.com/
- Google翻译：http://translate.google.cn/
- GooGle香港：https://www.google.com.hk/ncr 
- chrome同步状态Sync: chrome://sync-internals/
```
# 2. 云盘
- 坚果云。文件容器：用于[重要且常用、不重要却常用]文件及时分享，使用。
- oneDrive。文件仓库：用于[重要但不常用]文件长期存放。
- 百度云
- Dropbox

# 3. 云笔记
- 有道云笔记
- EveryNote
- oneNote

# 4. 输入法
- Win：**手心输入法** #无广告无弹窗
- Linux：**ibus-pinyin** #无广告无弹窗
# 5. 梯子
## 5.1. ShadowsocksR
- [ShadowsocksR介绍](https://lolico.moe/tutorial/shadowsocksr.html)
- ss免费账号分享：
  - [分享链接1](https://github.com/Alvin9999/new-pac/wiki/ss%E5%85%8D%E8%B4%B9%E8%B4%A6%E5%8F%B7)
  - [分享链接2](https://gitlab.com/Alvin9999/free/wikis/ss%E5%85%8D%E8%B4%B9%E8%B4%A6%E5%8F%B7)
  - [分享链接3](https://github.com/gfw-breaker/ssr-accounts)
## 5.2. v2rayN
- [V2Ray官网](https://www.v2ray.com)
- [**V2RayPro官网**](https://v2raypro.top)<br>[附链](https://myv2.us)
- [V2RayPro**多平台客户端**及说明](https://dl.v2raypro.us)

## 5.3. 手动更改hosts文件
### 5.3.1. 查询hosts
推荐[老D博客](https://laod.cn/)，长期更新hosts
### 5.3.2. 管理员修改hosts文件，hosts所在文件夹：
```
Windows 系统hosts位于 C:\Windows\System32\drivers\etc\hosts
Android（安卓）系统hosts位于 /etc/hosts
Mac（苹果电脑）系统hosts位于 /etc/hosts
iPhone（iOS）系统hosts位于 /etc/hosts
Linux系统hosts位于 /etc/hosts
绝大多数Unix系统都是在 /etc/hosts
```
### 5.3.3. 使修改后的hosts生效
**Windows**

开始 -> 运行 -> 输入cmd -> 在CMD窗口输入
```
ipconfig /flushdns
```
**Linux**

终端输入
```
sudo rcnscd restart
```
对于systemd发行版，请使用命令
```
sudo systemctl restart NetworkManager
```
**Mac OS X**

终端输入
```
sudo killall -HUP mDNSResponder
```
**Android**

开启飞行模式 -> 关闭飞行模式

**通用方法**

拔网线(断网) -> 插网线(重新连接网络)

如不行请清空浏览器缓存

# 6. 生产工具
## 6.1. 代码编辑器
- VIM
- Notepad++
## 6.2. 集成IDE开发环境
- CLion：C++集成IDE开发工具
- CodeBlocks：C++集成IDE开发工具
- IDEA：Java集成IDE开发工具
- PyCharm：Python集成IDE开发工具

## 6.3. Markdown编辑器
- Typora
- VScode
## 6.4. 思维导图
- ManagerPortable
- Mindmaster
## 6.5. 辅助工具
- 辅助计算工具：Matlab
- 数学公式编辑器：MathType
## 6.6. 文献管理工具
- EndNote
# 7. 下载工具
- IDM，IDM 6.25.11汉化破解版
- 迅雷，迅雷 精简版最后一版1.0.35.366
- PanDownload，第三方提供百度云管家替代下载工具，PanDownload_v1.5.2
