layout: post
title: 配置Manjaro
date: 2018/9/23 22:30:45
updated: 2018/10/26 22:10:45
comments: true
tags: 
- Linux
categories:
- 技术

---
<img src="../../../../uploads/AfterInstallManjaro.png" class="full-image" />

# 1. Manjaro设置国内源

## 1.1. 添加官方镜像源(包括: core, extra, community, multilib)
```[] 命令执行目录：~
sudo pacman-mirrors -i -c China -m rank //更新镜像排名
sudo pacman -Syy //更新数据源
```

<!-- more -->

## 1.2. 添加archlinxCN源(中科大)
```
sudo gedit /etc/pacman.conf
```
以管理员权限修改/etc/pacman.conf，在pacman.conf文件末尾添加以下内容
```[] 文件位置：/etc/pacman.conf
# USTC
[archlinuxcn]
SigLevel = Optional TrustedOnly
Server =https://mirrors.ustc.edu.cn/archlinuxcn/$arch
```
修改配置文件后，执行下面的命令：
```[] 命令执行目录：~
sudo pacman -Syy
sudo pacman -Syyu #(可选) 升级系统到最新
sudo pacman -S archlinuxcn-keyring //安装导入GPG key
```

## 1.3. 添加AUR源
修改/etc/yaourtrc文件，去掉 # AURURL 的注释，添加清华AUR源
```[] 文件位置：/etc/yaourtrc
AURURL="https://aur.tuna.tsinghua.edu.cn"  #添加清华AUR源
```

# 2. 安装Git
```[] 命令执行目录：~
sudo pacman -S git
```
- Git配置

```[] 命令执行目录：~
git config --global user.name "Your Name"
git config --global user.email "youremail@example.com"
git config --list #查看配置
```
- 编辑配置信息：

```
gedit ~/.gitconfig
```
查看内容是否如下：
```[] 文件位置：~/.gitconfig
[user]
name = Your Name
email = youremail@domain.com
```

- 创建公钥(一路回车，全部默认)：

```[] 命令执行目录：~
ssh-keygen -C 'you email address@gmail.com' -t rsa
```

- 复制公钥
打开刚刚新建的公钥，并复制文件所有内容 Ctrl + A
```
gedit /home/eisenhao/.ssh/id_rsa.pub
```

- 上传公钥到GitHub
将复制的代码上传到GitHub，打开 [GitHub.com](https://www.github.com)，登录后点击界面右上角用户图标，选择 Account Settings ==> SSH Public Keys ==> 粘贴刚刚复制的代码。

- 测试验证
```[] 命令执行目录：~
ssh -v git@github.com
```

# 3. 安装VIM

- 安装vim, ctags
打开ADD/REMOVE软件管理包，搜索vim、ctags并安装，或输入以下命令安装
```[] 命令执行目录：~
sudo pacman -S vim #vim文本编辑器
sudo pacman -S ctags #generates index tool
```
vim已安装完成，以下为导入GitHub大神分享的vim的IDE配置步骤，可调至下一个标题
- 打开终端，执行下面的命令自动下载[GitHub上一个做好的IDE式VIM:](https://github.com/ma6174/vim-deprecated)组件
```[] 命令执行目录：~
wget -qO- https://raw.github.com/ma6174/vim/master/setup.sh | sh -x
```

- 终端输入:"vim", 打开vim
```[] 命令执行目录：~
vim
```

- 命令模式输入:":BundleInstall"自动安装
"Shift" + ";"进入命令模式，在窗口左下角粘贴(Ctrl+Shift+V)以下代码后回车以自动安装组件
```[] 命令执行目录：vim命令模式下
BundleInstall
```

- 安装完成后打开配置
```
vim ~/.vimrc
```

- 添加如下配置
```[] 文件位置：~/.vimrc
"显示空格 回车符
" set listchars=eol:$(行尾),tab:>-(制表符),trail:~(空格),extends:>,precedes:<
set listchars=tab:>-,trail:-,extends:>,precedes:<
highlight WhitespaceEOL ctermbg=red guibg=red
match WhitespaceEOL /\s\+$/
set list
```

# 4. 安装Node.js
安装 Node.js 的最佳方式是使用 nvm。先卸载系统预装的nvm和nodejs
- 卸载预装nvm
```
sudo pacman -Q | grep nvm
sudo pacman -Rns nvm
```
- 卸载预装nodejs
```
sudo pacman -Q | grep nodejs
sudo pacman -Rns nodejs #
```
- 先通过cURL方式安装nvm:
```
curl -o- https://raw.githubusercontent.com/creationix/nvm/v0.33.11/install.sh | bash
```
- 待nvm安装完成后，重启终端 并执行下列命令即可安装 Node.js。
```
nvm install stable #安装 Node.js
```

# 5. ~~安装ZSH~~(可不更改，默认bash也不错)
ZSH可以说是shell中的极品，它的优点太多了，我就不一一写出来，有兴趣的同学可以看这篇文章知乎-为什么说zsh是shell中的极品，参考[JeanCheng](https://me.csdn.net/gatieme)的这篇博文：[Linux终极shell-Z Shell--用强大的zsh & oh-my-zsh把Bash换掉](https://blog.csdn.net/gatieme/article/details/52741221)

- 安装zsh
```[] 命令执行目录：~
sudo pacman -S zsh
```

- 配置oh-my-zsh
```[] 命令执行目录：~
sh -c "$(curl -fsSL https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
```

- 取代bash，设为默认shell
```[] 命令执行目录：~
sudo usermod -s /bin/zsh username1
或者
chsh -s /bin/zsha
chsh -s /bin/zsh1
chsh -s `which zsh`1
```
Finish，zsh已经安装完了

- 如果要切换回去bash：
想知道你的系统有几种shell，可以通过以下命令查看：
```
cat /etc/shells
```
切换回去bash
```
chsh -s /bin/bash
```
当然你实在不愿意把zsh当成默认的shell, 而又想使用它, 那么你可以每次进入是都使用**zsh**进入, 而输入exit退出

# 6. 安装IBus拼音输入法

- 搜索安装ibus-pinyin
```[] 命令执行目录：~
sudo pacman -S ibus-pinyin
```

- 在"系统设置" ==> "语言-配置" 中点击“+”添加刚刚安装的chinese-pinyin输入法

# 7. 用Terminator替换默认的Terminal终端
## 7.1. 安装Terminator
```[] 命令执行目录：~
sudo pacman -S Terminator
```
## 7.2. 设置Terminator启动快捷键。
打开系统设置，依次"Devices" ==> "keyboard" ==> 点击最末'+' ==> Name:"Open Terminator" ==> Command:"/usr/bin/terminator" ==> 设置启动快捷键(如：Ctrl+Alt+T)。
## 7.3. 配置Terminator配色及透明度。
右键窗体点击"Preferences" ==> "Colors" ==> Built-in schemes选择配色(如:"Green on black") ==> "Background" ==> 勾选"Transparent background" ==> 设置透明度Shade transparent background:(推荐0.8)
## 7.4. Terminator常用快捷键
```
Ctrl+Shift+C            #复制选中的内容到剪贴板
Ctrl+Shift+V            #粘贴剪贴板的内容到此处
Ctrl+Shift+O            #上下开新窗口
Ctrl+Shift+Up/Down      #分割条向上、下移动（终端上下多开窗口时）
Alt+Up/Down             #上、下窗口切换（终端上下多开窗口时）
Ctrl+Shift+W            #关闭当前终端
Ctrl+Shift+F            #搜索
#标签页快捷键
F11                     #全屏开关
Ctrl+Shift+T            #打开一个新的标签
Ctrl+PageDown           #移动到下一个标签
Ctrl+PageUp             #移动到上一个标签
```

# 8. 编译环境安装(Gcc, Java, Python)
## 8.1. 安装gcc make cmake gdb环境
- 安装gcc, make, cmake, gdb
```[] 命令执行目录：~
sudo pacman -S gcc make cmake gdb
```

- 查看GCC环境是否配置成功
```[] 命令执行目录：~
gcc --version
```

## 8.2. 安装JAVA环境

- ~~在主目录下，创建JAVA环境包存放目录~~（用更简便方式代替）
```
mkdir -p ~/Environment/JAVA
```

- ~~下载JDK [JAVA SE下载地址](http://www.oracle.com/technetwork/java/javase/downloads/jdk8-downloads-2133151.html)，下载到刚刚创建的目录。选择自己的安装平台，我选择的是"jdk-8u181-linux-x64.tar.gz"，如果下载的不是这个JDK包，后面的涉及JDK包文件时跟换到你的JDK包名就可。~~

- ~~跳转到压缩包目录解压~~
```
cd ~/Environment/JAVA  #跳转到压缩包目录
tar -xvf jdk-8u181-linux-x64.tar.gz  #解压JDK包
```

- ~~解压完成后，打开环境配置文件.bashrc(若配置了刚刚的zsh，则打开～/.zshrc)~~
```
vim ~/.bashrc
#或
vim ~/.zshrc #若刚刚已配置zsh
```

- ~~添加如下Java环境配置代码到文件末尾~~
```[] 文件位置：~/.bashrc 或 ~/.zshrc
#JAVA环境配置
export JAVA_HOME=$HOME/Environment/JAVA/jdk1.8.0_181
export JRE_HOME=${JAVA_HOME}/jre
export PATH=${JAVA_HOME}/bin:$PATH
export CLASSPATH=.:${JAVA_HOME}/lib/dt.jar:${JAVA_HOME}/lib/tools.jar
#IDEA软件需用到
export IDEA_JDK=$HOME/Environment/JAVA/jdk1.8.0_181
export IDEA_JDK_64=$HOME/Environment/JAVA/jdk1.8.0_181
```

- ~~生效刚刚配置的JAVA环境：~~
```[] 命令执行目录：~
source ~/.bashrc
或
source ~/.zshrc #若刚刚已配置zsh
```

- ~~查看JAVA环境是否配置成功~~
```
java -version
```

## 8.3. 通过'Add/Remove Software'软件**自动安装JAVA环境**
- 删除系统预装的openjdk
```
sudo pacman -Q | grep opnjdk #删除openjdk,'sudo pacman -Q'为查询已装软件，'| grep' 只显示与'opnjdk'相关内容
sudo pacman -Rns openjdk # sudo pacman -Rns 最小破换性地卸载（推荐），有效防止删除A软件时误删B软件所需的依赖(大致是这意思吧)..
sudo pacman -Rns openjdkheadless #删除openjdk相关
```
- 使用'Add/Remove Software'软件智能安装JAVA环境，不需手动配置(推荐)
在搜索框中搜索'jdk8'关键字，勾选'jdk8'(Oracle Java 8 Development Kit)'，再点击应用即可安装。

## 8.4. ~~安装Python环境~~(系统已经预装Python2.7和Python3.7(默认))

### 8.4.1. 安装Python3.7
- 直接在软件管理包中搜索"python  3.7.0-3"手动安装即可
- 或用pacman安装安装Python3.7
```[] 命令执行目录：~
sudo pacman -S python3.7
```
- 查看Python环境是否配置成功
```
python
```

### 8.4.2. ~~手动安装数据处理必备Numpy模块~~(较麻烦且容易失败，后文介绍用pip3方式安装)

~~参考自[linux下python3安装numpy与scipy](https://blog.csdn.net/chenyefei/article/details/77289289?utm_source=blogxgwz0)，由于numpy依赖于nose，故在需先安装依赖包nose，再安装numpy。~~

- ~~安装Python的nose模块~~
```
cd ~/Downloads
wget https://pypi.python.org/packages/38/96/7aa1c2583ddec558a230175d6aeddba796cde7191852bf3e6eb3cfb873e1/nose-1.1.2.tar.gz //下载nose-1.1.2
tar -zxvf nose-1.1.2.tar.gz //解压nose安装包(以实际下载的包名为准)
cd nose-1.1.2 //进入刚刚解压的目录
sudo python3 setup.py install //执行安装命令以安装nose 
```

- ~~安装Python的atlas模块~~
```
cd ~/Downloads
wget https://files.pythonhosted.org/packages/3b/30/a02c60e3a232cfcfdb9910ea2b5b83a567efeb1d3f1cb4622ce3eba63f9d/atlas-0.27.0.tar.gz //下载atlas-0.27.0
tar -zxvf atlas-0.27.0.tar.gz //解压atlas安装包(以实际下载的包名为准)
cd atlas-0.27.0 //进入刚刚解压的目录
sudo python3 setup.py install //执行安装命令以安装atlas
```

- ~~安装Python的numpy模块~~
```
cd ~/Downloads
wget https://sourceforge.net/projects/numpy/files/NumPy/1.9.0/numpy-1.9.0.zip //下载numpy包
unzip numpy-1.9.0.zip //解压numpy包
cd numpy-1.9.0 //进入刚刚解压的目录
sudo python3 setup.py install //执行安装命令安装numpy
```
安装完成后可用以下命令测试是否成功安装
```
python -c 'import numpy; numpy.test()'
```
- ~~Python数据处理常用包~~
```
各个安装包：
scipy-0.19.0  下载：https://github.com/scipy/scipy
numpy-1.9.0  下载：https://sourceforge.net/projects/numpy/files/NumPy/1.9.0/numpy-1.9.0.zip
nose-1.1.2   下载：https://pypi.python.org/packages/38/96/7aa1c2583ddec558a230175d6aeddba796cde7191852bf3e6eb3cfb873e1/nose-1.1.2.tar.gz
lapack-3.7.1   下载： www.netlib.org/lapack/lapack-3.7.1.tgz
atlas-0.27.0   下载： https://files.pythonhosted.org/packages/3b/30/a02c60e3a232cfcfdb9910ea2b5b83a567efeb1d3f1cb4622ce3eba63f9d/atlas-0.27.0.tar.gz
Cython-0.26    下载： https://pypi.python.org/pypi/Cython/0.26
依赖关系：scipy 的安装需要依赖于 numpy、lapack、atlas（后两者都是线性代数工具包，而 numpy 和scipy 的测试程序的运行又依赖于 nose，因此，整个安装过程必须要按顺序执行的，否则是无法执行下去的。
```

### 8.4.3. 使用pip3安装Numpy模块
访问[Python packages](https://pypi.org/)网站搜索相应模块(如"Numpy"),本地管理员运行其pip3安装代码<code>pip3 install numpy</code>
```
sudo pip3 install -i https://pypi.tuna.tsinghua.edu.cn/simple numpy
```

**同理顺序安装其他模块**

```
sudo pip3 install -i https://pypi.tuna.tsinghua.edu.cn/simple numpy        //安装Numpy库:提供数组支持，以及相应的高效的处理函数
sudo pip3 install -i https://pypi.tuna.tsinghua.edu.cn/simple SciPy        //安装SciPy库：提供矩阵支持，以及矩阵相关的数值计算模块
sudo pip3 install -i https://pypi.tuna.tsinghua.edu.cn/simple matplotlib   //安装Matplotlib库：强大的数据可视化工具、作图库
sudo pip3 install -i https://pypi.tuna.tsinghua.edu.cn/simple pandas       //安装Pandas库：强大、灵活的数据分析和探索工具
sudo pip3 install -i https://pypi.tuna.tsinghua.edu.cn/simple statsmodels  //安装StatsModels库：统计建模和计量经济学，包括描述统计、统计模型估计和推断
sudo pip3 install -i https://pypi.tuna.tsinghua.edu.cn/simple scikit-learn //安装Scikit-Learn库：支持回归、分类、聚类等强大的机器学习库
sudo pip3 install -i https://pypi.tuna.tsinghua.edu.cn/simple keras        //安装Keras库：深度学习库，用于建立神经网络以及深度学习模型
sudo pip3 install -i https://pypi.tuna.tsinghua.edu.cn/simple gensim       //安装Gensim库：用来做文本主题模型的库，可能用于文本挖掘
```

# 9. 常用软件安装
- 工具软件
```[] 命令执行目录：~
sudo pacman -S git #代码仓库
sudo pacman -S ctags #generates index tool
sudo pacman -S vim #vim文本编辑器
sudo pacman -S zsh #shell中的极品
sudo pacman -S ibus-pinyin #中文输入法支持
sudo pacman -S python-pip #Python Packages安装工具
sudo pacman -S nvm #Nodejs版本管理器，可以轻松切换Nodejs版本
sudo pacman -S nodejs #Nodejs
sudo pacman -S npm
```
- 应用软件
```[] 命令执行目录：~
sudo pacman -S google-chrome #谷歌浏览器
sudo pacman -S netease-cloud-music #网易云音乐
sudo pacman -S electronic-wechat #微信
sudo pacman -S typora #Typora,Markdown文档编辑器
sudo pacman -S Shadowsocks-Qt5 #VPN梯子
```
- 生产工具
```[] 命令执行目录：~
sudo pacman -S gcc make cmake gdb #安装gcc，make, cmake，gdb环境
sudo pacman -S clion #C/C++集成IDE开发工具
sudo pacman -S IntelliJ IDEA #Java集成IDE开发工具
sudo pacman -S pycharm-professional #python集成IDE开发工具
```

# 10. 系统常见问题及解决方案：
## 10.1. Windows和Linux双系统时间不一致问题
如何解决 Windows 和 Linux 双系统时间差8小时的问题 ， [可参考文章](https://blog.csdn.net/aaazz47/article/details/78696899)
```[] 命令执行目录：~
sudo timedatectl set-local-rtc 1
```
在系统设置->Details->Date & Time 中点击Automatic Date & Time联网更新时间
```[] 命令执行目录：~
sudo hwclock --localtime --systohc #将时间写入硬件
```
## 10.2. 桌面某些组建不正常显示时，重装gnome即可
桌面不正常显示，或某些显示功能不正常可能出现在通过软件管理包卸载软件时卸载部分未知依赖导致出错，如“系统设置未出现“，重新安装gnome所有组建可解决问题。
```
sudo pacman -S gnome
//选择"all",然后一直确定覆盖安装"y
```
## 10.3. 解决GitHub访问慢，修改host
- 修改hosts文件配置
```
sudo vim /etc/hosts
```
- a.手动查询DNS
打开 http://tool.chinaz.com/dns,这是一个查询域名映射关系的工具
查询 github.global.ssl.fastly.net 和 assets-cdn.github.com 两个地址
```
github.global.ssl.fastly.net
assets-cdn.github.com
```
多查几次，选择一个稳定，延迟较低的 ip 按如下方式添加到host文件

- b.使用大神分享的, eg:
```[] 文件位置：/etc/hosts
# Github  直接输入IP，可以让git变得非常快
151.101.44.249 github.global.ssl.fastly.net 
192.30.253.113 github.com 
103.245.222.133 assets-cdn.github.com 
23.235.47.133 assets-cdn.github.com 
203.208.39.104 assets-cdn.github.com 
204.232.175.78 documentcloud.github.com 
204.232.175.94 gist.github.com 
107.21.116.220 help.github.com 
207.97.227.252 nodeload.github.com 
199.27.76.130 raw.github.com 
107.22.3.110 status.github.com 
204.232.175.78 training.github.com 
207.97.227.243 www.github.com 
185.31.16.184 github.global.ssl.fastly.net 
185.31.18.133 avatars0.githubusercontent.com 
185.31.19.133 avatars1.githubusercontent.com
```
- 刷新DNS
```[] 命令执行目录：~
sudo systemctl restart NetworkManager
```
Finish, 享受飞速GitHub吧!

## 10.4. 解决pip3命令安装软件速度慢，使用-i参数
参考[Python-解决pip3下载安装速度慢](https://blog.csdn.net/wukai0909/article/details/62427437)
临时使用：
可以在使用pip3的时候加参数-i https://pypi.tuna.tsinghua.edu.cn/simple
```
pip3 install -i https://pypi.tuna.tsinghua.edu.cn/simple numpy
#这样就会从清华这边的镜像去安装numpy库。
```
## 10.5. 解决打开IDEA时弹出JDK路径错误
错误出现原因，删除原系统open-jdk后手动安装JDK时可能出现未知bug，导致终端JDK配置没问题，致使IDEA的idea.sh启动时并不能正确找到JDK路径。因此我们的解决思路是可以修改idea.sh文件的某些位置，强制设置JDK路径为上一步我们配置的地址。
```[] 修改文件:/usr/share/idea/bin/idea.sh
sudo gedit /usr/share/idea/bin/idea.sh #打开idea.sh文件
# Ctrl + F 搜索 “JAVA_BIN”
JDK=$HOME/Environment/JAVA/jdk1.8.0_181 #待添加强制定义JDK路径代码，将此行代码添加到idea.sh中的“JAVA_BIN="$JDK/bin/java”代码的上方一行，强制定义JDK路径，问题解决 Done:)
```

# 11. Linux 每日一练
压缩文件／文件夹
```
7za a -t7z -r Mytest.7z /opt/phpMyAdmin-3.3.8.1-all-languages/*
7za a -t7z -r eisenhao.github.io_backup20180928.7z /home/eisenhao/eisenhao.github.io/*  #压缩本站所有文件
```
其中：
- a  代表添加文件／文件夹到压缩包
- -t 是指定压缩类型，这里定为7z，可不指定，因为7za默认压缩类型就是7z。
- -r 表示递归所有的子文件夹
- Mytest.7z 是压缩好后的压缩包名
- /opt/phpMyAdmin-3.3.8.1-all-languages/\*：是压缩目标。

注意：7za不仅仅支持.7z压缩格式，还支持.tar.bz2等压缩类型的。如上所述，用-t指定即可。

# 12. 参考文档
- [简书Manjaro安装后配置](https://www.jianshu.com/p/79dae972b1e9)
- [系统安装|鲁Linux](https://www.lulinux.com/archives/category/linux_newbie)
- [Manjaro安装后配置](https://blog.csdn.net/dp_dp/article/details/80139283)
