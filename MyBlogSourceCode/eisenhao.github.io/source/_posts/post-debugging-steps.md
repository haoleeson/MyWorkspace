layout: post
title: 基于Hexo的博文编写调试发布流程简介
date: 2018/8/29 13:45:31
updated: 2018/9/2 15:02:45
comments: true
tags:
- Hexo
categories:
- 技术

---
<img src="https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/post-debugging-steps.png" class="full-image" />

# 1. 博客文章编写＆调试＆发布
## 1.1. 进入Hexo根目录
1. 输入密码,进入root用户模式
```
$ sudo su
```
2. 进入Hexo站点根目录
```
$ cd /home/eisenhao/eisenhao.github.io
```
<!-- more -->

## 1.2. 写文章

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

## 1.3. 本地调试

1. 开启测试
```c 命令执行目录：~/你的博客站点根目录
$ sudo hexo s
```
2. 在浏览器中输入: [http://localhost:4000/](http://localhost:4000/)以查看效果.

## 1.4. 发布

1. 测试没问题后，我们就生成静态网页文件发布至我们的Github pages 中。
```c 命令执行目录：~/你的博客站点根目录
$ cd /home/eisenhao/eisenhao.github.io
$ hexo clean && hexo g && hexo d
```
1. 可能会要求输入github账号密码
2. 如果上传失败显示如下信息,可能是由于我们没有配置root环境中的GitHub账号global，按照提示配置一下GitHub的global账号即可.
```
$ git config --global user.email "you@example.com"
$ git config --global user.name "Your Name"

```

# 2. 主题配置

1. 主题配置文件在主题文件夹中,我们可以更改config.yml文件进行配置.
```
/home/eisenhao/eisenhao.github.io/themes/next/_config.yml
```
2. 用文本编辑器打开编辑主题配置文件,点击查看[设置详细介绍.](http://theme-next.iissnan.com/getting-started.html#theme-settings)
```
$ vim /home/eisenhao/eisenhao.github.io/themes/next/_config.yml
```

# 3. Linux 技巧每日一练

用管理员运行文档管理器. sudo nautilus 会打开root版的文档管理器，可在终端键入ctrl+c就会关闭这个文档管理器。
```
$ sudo nautilus
```
