layout: post
title: 如何在Manjaro系统安装.rpm或.deb后缀软件
date: 2018/9/30 15:39:45
updated: 2018/9/30 16:34:45
comments: true
tags:
- Linux
categories:
- 技术

---
<img src="https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/howToConvert.rpmPackagesIntoArchPackages.jpg" class="full-image" />

尽管AUR被称为这个星球上最大的软件资源库，但不可避免的，我们有时会遇到在AUR库中没有待装软件，而待装软件官网只提供.rpm或.deb软件包的情况。本文将介绍如何利用.rpm或.deb软件包资源创建一个Arch软件包，然后在Manjaro系统下安装这些软件。如果你有兴趣读完本文，你会发现其实很简单。
<!-- more -->

# 1. 通过.deb包安装(推荐)

## 1.1. .deb包安装流程简述：
- 用一个叫“Debtap”的软件将.deb软件包转换成Arch软件包
- 用我们熟悉的<code>pacman</code>命令安装上一步创建的Arch软件包

## 1.2. 准备工作：
- 确保系统已安装<code>debtap</code>，可通过以下命令查询

```[] 命令执行目录：~
debtap -v #查询debtap安装的版本号
```
若没安装也可通过（<code>pacaur</code>、<code>packer</code>、<code>yaourt</code>）三种方式下载debtap源码文件然后安装debtap，以下是通过<code>yaourt</code>安装debtap的示例。<code>yaourt -S debtap</code>命令会下载debtap源码文件压缩包及<code>PKGBUILD</code>配置文件，我们只需要在下载完成后编译并安装debtap即可:

```[] 命令执行目录：~
sudo pacman -S yaourt #安装yaourt
yaourt -S debtap

#不用更改下载配置文件，一路No
Edit PKGBUILD ? [Y/n] --> N
Edit debtap.install ? --> N
Continue building debtap ? [Y/n] --> Y

#安装过程中访问/var目录会询问一次管理员密码
Continue installing debtap ? [Y/n] --> Y
Proceed with installation? [Y/n] --> Y
debtap -v #查询debtap安装的版本号
```
- 确保系统已安装<code>bash</code>, <code>binutils</code>, <code>pkgfile</code>和<code>fakeroot</code>
一般情况均已安装。安装Debtap和所有上述依赖项后，运行以下命令来创建/更新pkgfile和debtap数据库（至少执行一次）。
```[] 命令执行目录：~
sudo debtap -u
# 等待。。。创建/更新pkgfile和debtap数据库。当看到下列信息时，表明debtap已安装完毕。
==> Generating base group packages list...
==> All steps successfully completed!
```

- 去待安装软件官网下载与你系统相匹配的(64位或32位)<code>.deb</code>软件包，推荐下载到<code>~/Downloads</code>目录

## 1.3. 实际操作及代码

1. 跳转到.deb软件包的下载目录：
如果准备工作中<code>.deb软件包</code>下载到<code>~/Downloads</code>目录的话
```[] 命令执行目录：~
cd ~/Downloads
```

2. 用<code>debtap</code>命令转换.deb软件包为arch软件包
```[] 执行命令目录：你下载的.deb文件目录 eg:~/Download
debtap EasyConnect_x64.deb

# 如果您不想在程序包转换期间回答任何问题，可使用-q标志绕过所有问题
debtap -q EasyConnect_x64.deb(建议)

# 或使用-Q标志绕过所有问题（不建议使用）
debtap -Q EasyConnect_x64.deb
```
系统将要求您输入软件包维护者和许可证的名称。 只需输入它们并按ENTER键即可开始转换过程。软件包转换需要几秒钟到几分钟，具体取决于您的CPU速度。期间可以喝杯咖啡休息一下
```[] 若标志绕过所有问题，则不需要以下操作
:: Enter Packager name: --> EasyConnect
:: Enter package license: --> 填'GPL'或'unknow'
:: If you want to edit: --> Enter(跳过编辑)
```
转换完成后会在当前目录生成一个Arch软件包：<code>packagename.pkg.tar.xz</code>形式的文件(eg:<code>easyconnect-7.6.3.0.86415-1-x86_64.pkg.tar.xz</code>)

3. 用熟悉的<code>pacman</code>命令安装刚创建的Arch软件包
```[] 命令执行目录：刚刚转换Arch包的文件目录
#安装刚创建的Arch软件包
sudo pacman -U easyconnect-7.6.3.0.86415-1-x86_64.pkg.tar.xz
```
恭喜，至此已顺利安装软件。

4. **若安装失败或想卸载该软件**，执行以下命令即可

```[] 命令执行目录：~
sudo pacman -R easyconnect
```

# 2. 通过.rpm软件包安装

## 2.1. .rpm安装流程简述：
- 新建一个文件夹作为软件安装目录，并将待安装软件<code>.rpm</code>软件包移动到该文件夹内
- 在安装文件夹内创建并配置<code>PKGBUILD</code>文件
- 在待装软件文件夹内运行<code>makepkg</code>，然后创建Arch软件包
- 用我们熟悉的<code>pacman</code>命令安装上一步创建的Arch软件包

## 2.2. 准备工作：
- 确保系统已安装<code>rpmextract</code>
```[] 命令执行目录：~
sudo pacman -S rpmextract #安装rpmextract
```
- 去待安装软件官网下载与你系统相匹配的(64位或32位)<code>.rpm</code>软件包

## 2.3. 实际操作及代码：

1. 新建一个软件的安装文件夹，并将待安装软件<code>.rpm</code>包移动到该文件夹内
```
mkdir package #新建待安装软件文件夹，取名尽量具有可读性
cd package #跳转到该文件夹
#将待安装软件.rpm包复制到该文件夹内
```

2. 在待装软件文件夹内创建并配置<code>PKGBUILD</code>文件
这个<code>PKGBUILD</code>文件包含有关我们将要创建的包的所有配置信息，而Manjaro系统自带原生的<code>PKGBUILD</code>文件模板，所以直接复制到本目录再配置一下便可，可参考：[官方PKGBUILD文件配置说明](https://jlk.fjfi.cvut.cz/arch/manpages/man/PKGBUILD.5)。
```
cp /usr/share/pacman/PKGBUILD.proto PKGBUILD #复制系统自带的原生PKGBUILD文件模板到待安装软件目录
gedit PKGBUILD #配置PKGBUILD文件
```
我的<code>PKGBUILD</code>文件最终配置如下：
```
pkgname=google-musicmanager-beta
pkgver=current
pkgrel=1
pkgdesc="Add a simple disprection."
arch=('x86_64')
url="https://music.google.com/"
license=('unknown')
depends=('libidn')
makedepends=('rpmextract')
options=('emptydirs')
source=("http://dl.google.com/linux/direct/google-musicmanager-beta_current_x86_64.rpm")
md5sums=('6c05f087f9cd77563b7d001584e3b2d8')

build() {
cd "$pkgdir"
rpmextract.sh ../google-musicmanager-beta_current_x86_64.rpm
}
package() {
cd $srcdir
rsync -ruDq $srcdir $pkgdir
}
```
<code>PKGBUILD</code>文件中代码说明如下：
```
程序名称（强制格式：小写，无空格等）
版本（默认“current”吧）
内部版本号，对于包的每次更改都应增加1
简短描述（少于约80个字符）
架构（i686，x86_64，两者任意一种，或都支持）
包的官方网站的URL（可选）
许可证（GPL，BSD，unknown等）
程序可能具有的任何依赖项（若多个以空格分隔，而不是逗号）
只需要构建但不运行程序的依赖关系('rpmextract optipng'或'rpmextract')
任意选项（在这种情况下，提取后有一些空目录，我发现不必要，所以我使用了emptydirs选项）
源文件列表（如果是URL，则会在安装时下载这些.rpm文件，但也可以直接将.rpm软件包放在与PKGBUILD文件相同的文件夹中）
文件的md5sums列表（您可以通过在包含文件的文件夹中运行“makepkg -g”来获取这些文件的md5sums）。
最后是构建脚本进行提取
```

3. 在待装软件文件夹内运行<code>makepkg</code>创建Arch软件包
首先，在待装软件文件夹内运行<code>makepkg -g</code>。其次，待下载PKGBUILD文件中指定文件并返回一行<code>md5sum</code>，并复制<code>md5sum</code>到PKGBUILD文件中 。再次，再根据提示安装依赖项。最后，用<code>makepkg</code>创建最终的Arch软件包(即：<code>pkgname.pkg.tar.xz</code>文件)
```[] 命令执行目录：待装软件文件夹内
makepkg -g #该命令将下载PKGBUILD文件中指定文件并返回一md5sum行
gedit PKGBUILD #再次编辑PKGBUILD文件，将返回的md5sums行复制到md5sums=('')中
makepkg #创建Arch包，可能会提示存在尚未安装的依赖项，按提示安装所需依赖项
```

4. 用熟悉的<code>pacman</code>命令安装刚创建的Arch软件包
```[] 命令执行目录：刚刚转换Arch包的文件目录
pacman -U pkgname.pkg.tar.xz
```
恭喜，至此已顺利安装软件。

5. **若安装失败或想卸载该软件**，执行以下命令即可
```
pacman -R pkgname #其中pkgname为PKGBUILD文件中配置的软件名
```

# 3. Linux每日一练

在Linux系统中搜索文件命令<code>find</code>
```
sudo find / -name *example*.*

#其中
'/'表示搜索路径为/根目录，也可自定
'-name'表示搜索条件为名称
'\*' 表不确定内容，可搜索文件或文件夹
```

# 4. 参考文档

- [Install RPM packages on Arch Linux](http://nemrod.se/guides/install-rpm-packages-on-arch-linux/)
- [Creating packages](https://wiki.archlinux.org/index.php/Creating_packages)
- [PKGBUILD](https://wiki.archlinux.org/index.php/PKGBUILD)
