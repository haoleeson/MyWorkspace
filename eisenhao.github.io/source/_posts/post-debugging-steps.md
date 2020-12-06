layout: post
title: 基于Hexo的博客文章编写＆调试＆发布步骤
date: 2018/8/29 13:45:31
updated: 2018/9/2 15:02:45
comments: true
tags:
- Hexo
categories:
- 技术

---
<img src="https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/post-debugging-steps.png" class="full-image" />

## 博客文章编写＆调试＆发布
### 进入Hexo根目录
1. 输入密码,进入root用户模式
```
$ sudo su
```
2. 进入Hexo站点根目录
```
$ cd /home/eisenhao/eisenhao.github.io
```
<!-- more -->

### 写文章

1. 进入发布文件夹
```
$ cd /home/eisenhao/eisenhao.github.io/source/_posts
```
2. 新建md文件
```
$ touch example.md
```
3. 编辑example.md文件，编写文章(用Markdown大肆发挥吧，可参考[Markdown文章语法](https://eisenhao.cn/2018/08/31/write-a-md-file/))
```
$ vim example.md
```

### 本地调试

1. 开启测试
```c 命令执行目录：~/你的博客站点根目录
$ sudo hexo s
```
2. 在浏览器中输入: [http://localhost:4000/](http://localhost:4000/)以查看效果.

### 发布

1. 测试没问题后，我们就生成静态网页文件发布至我们的Github pages 中。
```c 命令执行目录：~/你的博客站点根目录
$ cd /home/eisenhao/eisenhao.github.io
$ hexo clean && hexo g && hexo d
```
2. 可能会要求输入github账号密码：ei13911468370@gmail.com
3. 如果上传失败显示如下信息,可能是由于我们没有配置root环境中的GitHub账号global
```
*** 请告诉我你是谁。

运行

  git config --global user.email "you@example.com"
  git config --global user.name "Your Name"

来设置您账号的缺省身份标识。
如果仅在本仓库设置身份标识，则省略 --global 参数。

fatal: 无法自动探测邮件地址（得到 'root@g510.(none)'）
Username for 'https://github.com': ei13911468370@gmail.com
Password for 'https://ei13911468370@gmail.com@github.com': 
Everything up-to-date
分支 'master' 设置为跟踪来自 'https://github.com/EisenHao/eisenhao.github.io.git' 的远程分支 'master'。
INFO  Deploy done: git

```
4. 按照提示配置一下GitHub的global账号即可.
```
$ git config --global user.email "you@example.com"
$ git config --global user.name "Your Name"

```

## 主题配置

1. 主题配置文件在主题文件夹中,我们可以更改config.yml文件进行配置.
```
/home/eisenhao/eisenhao.github.io/themes/next/_config.yml
```
2. 用文本编辑器打开编辑主题配置文件,点击查看[设置详细介绍.](http://theme-next.iissnan.com/getting-started.html#theme-settings)
```
$ vim /home/eisenhao/eisenhao.github.io/themes/next/_config.yml
```

* * *

## Linux 技巧每日一练

用管理员运行文档管理器. sudo nautilus 会打开root版的文档管理器，可在终端键入ctrl+c就会关闭这个文档管理器。
```
$ sudo nautilus
```
