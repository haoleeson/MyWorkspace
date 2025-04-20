layout: post
title: 基于Hexo的Markdown博文语法简介
date: 2018/8/31 12:10:30
updated: 2018/10/04 19:15:45
comments: true
tags:
- Hexo
categories:
- 技术

---
<img src="../../../../uploads/write-a-md-file.jpg" class="full-image" />

# 1. md文件预定义参数

## 1.1. 预定义参数
以下是预先定义的参数，您可在模板中使用这些参数值并加以利用。

<!-- more -->

layout|布局|post
title|标题|
date|建立日期|文件建立日期
updated|更新日期|文件更新日期
comments|开启文章的评论功能|true
tags|标签（不适用于分页）|
categories|分类（不适用于分页）|
permalink|覆盖文章网址|

## 1.2. 本文的md文件预定义参数
```
layout: post
title: Markdown文章写作格式＆语法
date: 2018/8/31 12:10:30
updated: 2018/9/1 19:24:45
comments: true
tags:
- Markdown
- Hexo
categories:
- Markdown

---
```

# 2. Hexo下的Markdown语法
## 2.1. 语法简明描述
1. **分段：** <code>两个回车</code>
2. **换行：** <code>两个空格 + 回车</code>
3. **标题：** # ~ ######，#号的个数表示几级标题，即表示一～六级标题。(eg: <code>### 三级标题</code>)
4. **强调：** *倾斜*(<code>\*倾斜\*</code>) 、 **加粗**(<code>\*\*加粗\*\*</code> or <code>\_\_加粗\_\_</code>) 、***倾斜加粗***(<code>\*\*\*倾斜加粗\*\*\*</code>) 、 ~~删除线~~(<code>\~\~删除线\~\~</code>) 、 `标记`  (<code>\`标记\`</code>)
5. **列表：** <code>\* </code> 、<code>+ </code> 、<code>- </code> 、<code>数字序号. </code>(有序)  选其中之一，注意后面都紧跟一个空格
6. **引用：** <code>\> </code> ，注意\>后面紧跟一个空格(eg: <code>\> 引用文字</code>)，结束引用时输入<code>两个回车</code>以结束引用
7. **图片：** 在需要添加图片的位置<code>\!\[图片](图片地址)</code>便可，图片地址可以是本地路径，或网络地址
8. **表格：** - 和 | 分割行和列 ，<code>:</code>与<code>-</code>的相对位置控制当前列的左对齐、居中对齐、右对齐方式(<code>:\--\--\|:\--\--:\|\--\--:</code>)，表格代码段可能需要与上部分代码空一行
9. **代码块：** 每行代码前加四个空格(不显示行号)，或 使用<code>\`\`\`代码内容\`\`\`</code>(显示行号，<code>\`</code>为键盘Esc下方按键)
10. **文本链接：** \[文字链接名称\](链接地址)，eg: [我的博客](https://haoleeson.github.io/) (<code>\[我的博客\]\(https://haoleeson.github.io/</code>)
11. **小型文本：** <small>小型文本</small>
```
<small>小型文本</small>
```
12. **高亮：** 比如<code>突出背景色</code>来显示强调效果
```
    <code>突出背景色</code>
```
13. **代码注释：** 注释内容有助于理解代码，而不会被编译
```
<!-- 注释内容 -->
```
14. **网址链接：** <网址链接>，eg: 我的博客:<https://haoleeson.cn/>
```
我的博客:<https://haoleeson.cn/>
```
15. **阅读全文：** 常用于文章过长，只显示文章前半部分，结合Hexo实现文章截断，点击阅读更多后显示全文
```
<!-- more -->
```
16. **文本右对齐：** 
正常文本
<div align = center>文本居中</div>
<div align = right>文本右对齐</div>
```
正常文本
<div align = center>文本居中</div>
<div align = right>文本右对齐</div>
```
17. **代码块高级用法**
```
# 请忽视"`\``"中的转移符"\"
`\``[language] [title] [url] [link-text]
代码块内容
`\``
[language] 是代码语言的名称，用来设置代码块颜色高亮，非必须；
[title] 是顶部左边的说明，非必须；
[url] 是顶部右边的超链接地址，非必须；
[link text] 如它的字面意思，超链接的名称，非必须。
```
亲测这 4 项应该是根据空格来分隔，而不是[]，故请不要加[]。除非如果你想写后面两个，但不想写前面两个，那么就必须加[]了，要这样写：[] [] [url] [link text]，更多关于代码块的高级用法可参考文档：[HEXO下的语法高亮拓展修改](https://www.ofind.cn/blog/HEXO/HEXO%E4%B8%8B%E7%9A%84%E8%AF%AD%E6%B3%95%E9%AB%98%E4%BA%AE%E6%8B%93%E5%B1%95%E4%BF%AE%E6%94%B9.html)。
例如以下代码:
```
# 请忽视"`\``"中的转移符"\"
`\``c++ 文件位置：~/GitHub/Cpp_Learning/Cpp_demo.cpp
#include <iostream>
using namespace std;

int main(void) {
    cout << "Hello World!" << endl;
    return 0;
}
`\``
```
效果如下:
```c++ 文件位置：~/GitHub/Cpp_Learning/Cpp_demo.cpp
#include <iostream>
using namespace std;

int main(void) {
    cout << "Hello World!" << endl;
    return 0;
}
```

## 2.2. 引用嵌套
引用的嵌套使用，注意引用字段结束后输入两个回车结束
```
> 植物
>> 陆生植物
>>> 树
>>> 草
>>>> 苹果树
>>>> 梨树
>>橘子树 //由于没有用没有空行间隔，忽略降级引用标记
香蕉树 //由于没有用没有空行间隔，忽略降级引用标记

>> 水生植物
>>> 藻
海草

共输入两个回车，结束引用
```
> 植物
>> 陆生植物
>>> 树
>>> 草
>>>> 苹果树
>>>> 梨树
>>橘子树 //由于没有用没有空行间隔，忽略降级引用标记
香蕉树 //由于没有用没有空行间隔，忽略降级引用标记

>> 水生植物
>>> 藻
海草

共输入两个回车，结束引用

## 2.3. 列表
### 2.3.1. 无序列表
<code>* </code>、<code>+ </code>、<code>- </code>三种方式都能表示无序列表
```
- 无序列表1
+ 无序列表2
- 无序列表3
```
- 无序列表1
+ 无序列表2
- 无序列表3

### 2.3.2. 有序列表
只取第一个列表的数字序号，序号依次增加，与接下来的数字序号无关
```
3. 有序列表3
9. 有序列表9
2. 有序列表2
```
3. 有序列表3
9. 有序列表9
2. 有序列表2

## 2.4. 分割线
分割线可以由<code>\*</code>、<code>-</code>、<code>\_</code>这3种符号每种至少3个来表示(不必严格连续)
```
- * *
-- -
_ _ _

```
对应效果:

- * *
-- -
_ _ _


# 3. 内置标签

标签(Tag Plugin)是Hexo提供的一种快速生成特定内容的方式。例如，在标准Markdown语法中，我们无法指定图片的大小。这种情景，我们即可使用标签来解决。Hexo内置来许多标签来帮助写作者可以更快的书写，参考Hexo的[完整的标签列表](https://hexo.io/zh-cn/docs/tag-plugins.html)。Hexo也开放来接口给主题，使提供给写作者更简便的写作方法成为可能。

## 3.1. 文本居中的引用
此标签将生成一个带上下分割线的引用，同时引用内文本将自动居中。文本居中时，多行文本若长度不等，视觉上会显得不对称，因此建议在引用单行文本的场景下使用。例如作为文章开篇引用或者结束语之前的总结引用。
### 3.1.1. HTML引用方式:
使用HTML方式：直接在Markdown文件中编写HTML来调用
```
<!-- HTML方式: 直接在 Markdown 文件中编写 HTML 来调用 -->
<!-- 其中 class="blockquote-center" 是必须的 -->
<blockquote class="blockquote-center">HTML引用方式</blockquote>
```
<!-- HTML方式: 直接在 Markdown 文件中编写 HTML 来调用 -->
<!-- 其中 class="blockquote-center" 是必须的 -->
<blockquote class="blockquote-center">HTML引用方式</blockquote>

### 3.1.2. 标签引用方式:
使用<code>centerquote</code>或者<code>cq</code>

```
<!-- 标签 方式，要求版本在0.4.5或以上 -->
{% centerquote %}标签引用方式1{% endcenterquote %}
<!-- 标签别名 -->
{% cq %}标签引用方式2{% endcq %}
```
<!-- 标签 方式，要求版本在0.4.5或以上 -->
{% centerquote %}标签引用方式1{% endcenterquote %}
<!-- 标签别名 -->
{% cq %}标签引用方式2{% endcq %}

## 3.2. 突破容器宽度限制的图片引用
当使用此标签引用图片时，图片将自动扩大26%，并突破文章容器的宽度。此标签使用于需要突出显示的图片,图片的扩大与容器的偏差从视觉上提升图片的吸引力。此标签有两种调用方式（详细参看底下示例）：

### 3.2.1. HTML引用图片方式
使用这种方式时，为<code>img</code>添加属性<code>class="full-image"</code>即可
```
<!-- HTML引用图片方式: 直接在 Markdown 文件中编写 HTML 来调用 -->
<!-- 其中 class="full-image" 是必须的 -->
<img src="https://cdn.wfolio.ru/w/4b318a3da2f7d3a89fa5957a8dd9a00dd2609616/m_limit%2Cw_1920/sites/181/assets/1524794399_7fc3ff.jpg" class="full-image" />
```
<!-- HTML引用图片方式: 直接在 Markdown 文件中编写 HTML 来调用 -->
<!-- 其中 class="full-image" 是必须的 -->

<img src="https://cdn.wfolio.ru/w/4b318a3da2f7d3a89fa5957a8dd9a00dd2609616/m_limit%2Cw_1920/sites/181/assets/1524794399_7fc3ff.jpg" class="full-image" />


# 4. Bootstrap Callout
这些样式出现在[Bootstrap官方文档](http://getbootstrap.com/)中。

**使用方式**

```
{% note class_name %} Content (md partial supported) {% endnote %}
```
其中，<code>class\_name</code>可以是以下一个值：
```
default
primary
success
info
warning
danger
```
代码实例:
```
{% note default %}1.default效果{% endnote %}
{% note primary %}2.primary效果{% endnote %}
{% note success %}3.success效果{% endnote %}
{% note info %}4.info效果{% endnote %}
{% note warning %}5.warning效果{% endnote %}
{% note danger %}6.danger效果{% endnote %}
```
{% note default %}1.default效果{% endnote %}
{% note primary %}2.primary效果{% endnote %}
{% note success %}3.success效果{% endnote %}
{% note info %}4.info效果{% endnote %}
{% note warning %}5.warning效果{% endnote %}
{% note danger %}6.danger效果{% endnote %}

# 5. 主题自带样式 label 标签
首先需要在主题配置文件中有配置，需要配置下
```
gedit /你的Hexo站点目录/themes/next/_config.yml
# Label tag.
label: true
```
效果如下：(目前存在一个 bug，如果把它加在一段文字的段首，则会有点问题，issue 页面。)
{% label default@default %}
```
{% label default@default %}
```
{% label primary@primary %}
```
{% label primary@primary %}
```
{% label success@success %}
```
{% label success@success %}
```
{% label info@info %}
```
{% label info@info %}
```
{% label warning@warning %}
```
{% label warning@warning %}
```
{% label danger@danger %}
```
{% label danger@danger %}
```
# 6. NexT主题自带样式 tabs 标签

在主题配置文件中有配置，需要配置下:
```
gedit /你的Hexo站点目录/themes/next/_config.yml
# Tabs tag.
tabs:
  enable: true
  transition:
    tabs: true
    labels: true
  border_radius: 0
```
效果如下：

{% tabs 选项卡, 2 %}
<!-- tab -->
**这是选项卡 1** 呵呵哈哈哈哈哈哈哈哈呵呵哈哈哈哈哈哈哈哈呵呵哈哈哈哈哈哈哈哈呵呵哈哈哈哈哈哈哈哈呵呵哈哈哈哈哈哈哈哈呵呵哈哈哈哈哈哈哈哈……
<!-- endtab -->
<!-- tab -->
**这是选项卡 2**
<!-- endtab -->
<!-- tab -->
**这是选项卡 3** 哇，你找到我了!
<!-- endtab -->
{% endtabs %}

源码：
```
{% tabs 选项卡, 2 %}
<!-- tab -->
**这是选项卡 1** 呵呵哈哈哈哈哈哈哈哈呵呵哈哈哈哈哈哈哈哈呵呵哈哈哈哈哈哈哈哈呵呵哈哈哈哈哈哈哈哈呵呵哈哈哈哈哈哈哈哈呵呵哈哈哈哈哈哈哈哈……
<!-- endtab -->
<!-- tab -->
**这是选项卡 2**
<!-- endtab -->
<!-- tab -->
**这是选项卡 3** 哇，你找到我了！φ(≧ω≦*)♪～
<!-- endtab -->
{% endtabs %}
```
然后上面源码中, 2表示一开始在第二个选项卡，非必须，若数值为-1则隐藏选项卡内容。更多用法请查看 [这个页面](https://almostover.ru/2016-01/hexo-theme-next-test/#Tab-tag-test)。

# 7. 主题自带样式--**按钮**
效果：
{% btn https://www.baidu.com, 点击下载百度, download fa-lg fa-fw %}
源码：
```
{% btn https://www.baidu.com, 点击下载百度, download fa-lg fa-fw %}
```
关于按钮的更多使用可以前往 [这个网页](https://almostover.ru/2016-01/hexo-theme-next-test/#Button-tag-test)查看。

# 8. 插入音乐
音乐的话，网易云音乐的外链很好用，不仅有可以单曲，还能有歌单，有兴趣的自己去网易云音乐找首歌尝试。但是有一些音乐因为版权原因放不了，还有就是不完全支持 https，导致小绿锁不见了。要解决这些缺点，就需要安装插件alien。

## 8.1. 方法1：可以直接用 HTML 的标签，写法如下：
```
<audio src="https://什么什么什么.mp3" style="max-height :100%; max-width: 100%; display: block; margin-left: auto; margin-right: auto;" controls="controls" loop="loop" preload="meta">Your browser does not support the audio tag.</audio>
```

## 8.2. 方法2：用插件，有显示歌词功能，也美观，建议使用这种方法。 
首先在<code>站点</code>文件夹根目录安装插件：
```
npm install hexo-tag-aplayer --save
```

然后文章中的写法：

```
{% aplayer "歌曲名" "歌手名" "https://什么什么什么.mp3" "https://封面图.jpg" "lrc:https://歌词.lrc" %}

```

另外可以支持歌单：

```
{% aplayerlist %}
{
    "autoplay": false,
    "showlrc": 3,
    "mutex": true,
    "music": [
        {
            "title": "歌曲名",
            "author": "歌手名",
            "url": "https://什么什么什么.mp3",
            "pic": "https://封面图.jpg",
            "lrc": "https://歌词.lrc"
        },
        {
            "title": "歌曲名",
            "author": "歌手名",
            "url": "https://什么什么什么.mp3",
            "pic": "https://封面图.jpg",
            "lrc": "https://歌词.lrc"
        }
    ]
}
{% endaplayerlist %}
```

效果可以见[易象辞的 Hello World](https://reuixiy.github.io/uncategorized/2010/01/01/test.html)，里面的详细参数见[README](https://github.com/MoePlayer/hexo-tag-aplayer) 和这插件的“母亲” Aplayer 的[官方文档](https://aplayer.js.org/)。

## 8.3. 下方测试插入音乐

### 8.3.1. 方式1：HTML的标签插入音乐（网易云音乐）

网易云音乐 -> 生成外链播放器 -> 复制代码 -> 粘贴到md文档

网易云iframe插件：

<iframe frameborder="no" border="0" marginwidth="0" marginheight="0" width=330 height=86 src="//music.163.com/outchain/player?type=2&id=414611053&auto=1&height=66"></iframe>

网易云flash插件：

<embed src="//music.163.com/style/swf/widget.swf?sid=414611053&type=2&auto=1&width=320&height=66" width="340" height="86"  allowNetworking="all"></embed>

### 8.3.2. 方式2：用hexo-tag-aplayer插件音乐
巧取网易云音乐mp3外链方法，不知到现在有没有被禁
例如：在网易云网页版点击"陈芳语-爱你"，从浏览器地址栏发现"陈芳语-爱你"的id为：22852057，则将下方代码'id='后的数字更改为‘22852057’之后就是"陈芳语-爱你"mp3格式的外链，新建标签页粘贴该地址可直接播放，应用在博客里插入外链还是很方便的（ps:在网易云还没禁用此bug之前）。

将歌词文件放在“hexo站点文件夹/source/uploads/”文件夹内，封面图、歌词文件引用地址为：
"https://haoleeson.github.io/uploads/封面图.jpg"、"https://haoleeson.github.io/uploads/歌词.lrc"

```
# 网易云网页版关于"陈芳语-爱你"的歌曲id=22852057
http://music.163.com/song/media/outer/url?id=22852057.mp3 #可直接播放外链（已失效）
https://haoleeson.github.io/uploads/loveYou.jpg #封面图
https://haoleeson.github.io/uploads/fangyuchen_loveyou.lrc #歌词 //暂时无法添加lrc歌词，只能内嵌歌词
```

## 8.4. 下方测试插件插入音乐（无歌词，lrc方式歌词失效）：
```
{% aplayer "爱你" "陈芳语" "../../../../uploads/22852057.mp3" "https://haoleeson.github.io/uploads/loveYou.jpg" "lrc:https://haoleeson.github.io/uploads/fangyuchen_loveyou.lrc" %}
```

{% aplayer "爱你" "陈芳语" "../../../../uploads/22852057.mp3" "https://haoleeson.github.io/uploads/loveYou.jpg" "lrc:https://haoleeson.github.io/uploads/fangyuchen_loveyou.lrc" %}

## 8.5. 下方测试插件插入内嵌音乐歌词：

```
{% aplayerlrc "爱你" "陈芳语" "../../../../uploads/22852057.mp3" "../../../../uploads/loveYou.jpg" %}
[00:00.25]Kimberley(陈芳语) - 爱你[00:06.43]我闭上眼睛 贴着你心跳呼吸[00:13.42]而此刻地球 只剩我们而已[00:20.16]你微笑的唇型 总勾着我的心[00:26.73]每一秒初吻 我每一秒都想要吻你[00:36.11]就这样 爱你 爱你 爱你 随时都要一起[00:42.43]我喜欢 爱你 外套 味道 还有你的怀里[00:49.11]把我们 衣服 钮扣 互扣 那就不用分离[00:56.49]美好爱情 我就爱这样贴近 因为你[01:16.85]有时没生气 故意闹脾气[01:23.42]你的紧张在意 让我觉得安心[01:30.04]从你某个角度 我总看见自己[01:36.76]到底你懂我 或其时我本来就像你[01:46.17]就这样 爱你 爱你 爱你 随时都要一起[01:52.70]我喜欢 爱你 外套 味道 还有你的怀里[01:59.28]把我们 衣服 钮扣 互扣 那就不用分离[02:06.80]美好爱情 我就爱这样贴近 因为你[02:17.73]想变成你的氧气 溜进你身体里[02:31.49]好好看看在你心里 你有多麽宝贝 我爱你[02:44.44]就这样 爱你 爱你 爱你 随时都要一起 （爱你）[02:49.27]我喜欢 爱你 外套 味道 还有你的怀里[02:55.92]把我们 衣服 钮扣 互扣 那就不用分离[03:03.50]美好爱情 我就爱这样贴近 因为你[03:10.28]我们爱情 会一直没有距离 最美丽
{% endaplayerlrc %}
```

{% aplayerlrc "爱你" "陈芳语" "../../../../uploads/22852057.mp3" "../../../../uploads/loveYou.jpg" %}
[00:00.25]Kimberley(陈芳语) - 爱你[00:06.43]我闭上眼睛 贴着你心跳呼吸[00:13.42]而此刻地球 只剩我们而已[00:20.16]你微笑的唇型 总勾着我的心[00:26.73]每一秒初吻 我每一秒都想要吻你[00:36.11]就这样 爱你 爱你 爱你 随时都要一起[00:42.43]我喜欢 爱你 外套 味道 还有你的怀里[00:49.11]把我们 衣服 钮扣 互扣 那就不用分离[00:56.49]美好爱情 我就爱这样贴近 因为你[01:16.85]有时没生气 故意闹脾气[01:23.42]你的紧张在意 让我觉得安心[01:30.04]从你某个角度 我总看见自己[01:36.76]到底你懂我 或其时我本来就像你[01:46.17]就这样 爱你 爱你 爱你 随时都要一起[01:52.70]我喜欢 爱你 外套 味道 还有你的怀里[01:59.28]把我们 衣服 钮扣 互扣 那就不用分离[02:06.80]美好爱情 我就爱这样贴近 因为你[02:17.73]想变成你的氧气 溜进你身体里[02:31.49]好好看看在你心里 你有多麽宝贝 我爱你[02:44.44]就这样 爱你 爱你 爱你 随时都要一起 （爱你）[02:49.27]我喜欢 爱你 外套 味道 还有你的怀里[02:55.92]把我们 衣服 钮扣 互扣 那就不用分离[03:03.50]美好爱情 我就爱这样贴近 因为你[03:10.28]我们爱情 会一直没有距离 最美丽
{% endaplayerlrc %}

# 9. 插入视频

## 9.1. 可以直接用 HTML 的标签，写法如下：
```
<video poster="https://封面图.jpg" src="https://什么什么什么.mp4" style="max-height :100%; max-width: 100%; display: block; margin-left: auto; margin-right: auto;" controls="controls" loop="loop" preload="meta">Your browser does not support the video tag.</video>

```

## 9.2. 用第三方视频网站提供的嵌入式代码
如bilibili提供的iframe插件，可在博客md文件中插入以下代码插入视频。获取iframe代码简诉：
- 找到想要分享的视频
- 点击视频右上角三个竖点按钮 -> 点击功能窗口 -> 点击分享 -> 复制视频的唯一嵌入代码
```
<iframe src="//player.bilibili.com/player.html?aid=26361000&cid=49053680&page=1&season_type=1" scrolling="no" border="0" frameborder="no" framespacing="0" allowfullscreen="true"></iframe>
```
<iframe src="//player.bilibili.com/player.html?aid=26361000&cid=49053680&page=1&season_type=1" scrolling="no" border="0" frameborder="no" framespacing="0" allowfullscreen="true"></iframe>

## 9.3. 用插件，功能更加强大，比如可以弹幕，非常建议食用。

首先在站点文件夹根目录安装插件：
```
npm install hexo-tag-dplayer --save
```
然后文章中的写法：
```
{% dplayer "url=https://什么什么什么.mp4" "https://封面图.jpg" "api=https://api.prprpr.me/dplayer/" "id=" "loop=false" %}
```
要使用弹幕，必须有<code>api</code>和<code>id</code>两项，并且若使用的是官方的api地址（即上面的），id的值不能与[这个列表](https://api.prprpr.me/dplayer/list)的值一样。id的值自己随便取，唯一要求就是前面这点。

如果唯一要求难倒了你，可以使用[这个工具](http://tool.oschina.net/encrypt?type=2)将一段与众不同的文字joy生成一段看起来毫无意义的哈希值，这样看起来是不是好多了。

效果，在这[易象辞的博客的video](https://reuixiy.github.io/tags/video/)标签里自己找一篇文章看看。

当然，这个插件的功能还有很多，可以去[README](https://github.com/MoePlayer/hexo-tag-dplayer)和这插件的“母亲” Dplayer 的[官方文档](https://dplayer.js.org/)看看。

- * *

# 10. Linux 技巧每日一练：cp命令

> cp命令。用来将一个或多个源文件或者目录复制到指定的目的文件或目录。它可以将单个源文件复制成一个指定文件名的具体的文件或一个已经存在的目录下。cp命令还支持同时复制多个文件，当一次复制多个文件时，目标文件参数必须是一个已经存在的目录，否则将出现错误。

> cp语法: cp(选项)(参数)

复制Folder文件夹所有文件到Backup文件夹，并显示所有改动的文件，常用于文件备份
```
cp -ruv Folder/* Backup
```

## 10.1. 选项参数及说明
```
-a    此参数的效果和同时指定"-dpR"参数相同；
-d    当复制符号连接时，把目标文件或目录也建立为符号连接，并指向与源文件或目录连接的原始文件或目录；
-f    强行复制文件或目录，不论目标文件或目录是否已存在；
-i    覆盖既有文件之前先询问用户；
-l    对源文件建立硬连接，而非复制文件；
-p    保留源文件或目录的属性；
-R/r  递归处理，将指定目录下的所有文件与子目录一并处理；
-s    对源文件建立符号连接，而非复制文件；
-u    使用这项参数后只会在源文件的更改时间较目标文件更新时或是名称相互对应的目标文件并不存在时，才复制文件；
-S    在备份文件时，用指定的后缀“SUFFIX”代替文件的默认后缀；
-b    覆盖已存在的文件目标前将目标文件备份；
-v    详细显示命令执行的操作。
```

# 11. 参考文档
- [reuixiy](https://reuixiy.github.io/technology/computer/computer-aided-art/2017/06/09/hexo-next-optimization.html#%E6%9B%B4%E6%96%B0%E4%B8%BB%E9%A2%98)
- [Hexo 使用 Markdown 编辑技巧大全](https://blog.csdn.net/WilliamZ98/article/details/81074219)
- [Hexo在Github中搭建博客系统(5)Markdown语法](https://blog.csdn.net/chwshuang/article/details/52350551)
- [Next-内置标签](http://theme-next.iissnan.com/tag-plugins.html)
- [Linux命令大全](http://man.linuxde.net/cp)
