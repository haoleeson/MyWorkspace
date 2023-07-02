layout: post
title: Python查看本周口碑电影
date: 2019/04/30 11:28:30
updated: 2019/04/30 12:48:45
comments: true
tags:
- Python
categories:
- 技术

---
<img src="../../../../uploads/PythonSimpleWebCTest.jpg" class="full-image" />

# 1. 查看豆瓣周口碑榜的电影列表
执行结果展示：
```Python
查看豆瓣一周口碑榜:
复仇者联盟4：终局之战
触不可及(美版)
盗梦特攻队
深红累之渊
遇见女孩的感觉
撞死了一只羊
归家：碧昂斯电影作品
西班牙之旅
娑婆诃
番石榴岛
```

<!-- more -->

# 2. 准备工作
- 安装Python环境。详见[安装Python3.7](https://eisenhao.cn/2018/09/23/AfterInstallManjaro/#%E5%AE%89%E8%A3%85Python3-7)
- 使用pip3安装requests、lxml模块。参考[使用pip3安装Numpy模块](https://eisenhao.cn/2018/09/23/AfterInstallManjaro/#%E4%BD%BF%E7%94%A8pip3%E5%AE%89%E8%A3%85Numpy%E6%A8%A1%E5%9D%97)
- 运行平台：终端或Python IDE软件(eg.[PyCharm](http://www.jetbrains.com/pycharm/))

# 3. 练习1：查看豆瓣一周口碑榜
代码比较简单，如下所示：
```Python
# 查看豆瓣一周口碑榜 https://movie.douban.com/
import requests
from lxml import html

url = 'https://movie.douban.com/'
page = requests.Session().get(url)
tree = html.fromstring(page.text)
result = tree.xpath('//td[@class="title"]//a/text()')
# //td ：这个相当于指定是大目录；
# [@class="title"]：这个相当于指定的小目录；
# //a ：这个相当于最小的目录；
# /text()：这个是提取其中的数据。

# 格式输出
print("查看豆瓣一周口碑榜:")
for i in result:
    print(i, end='\n')
```

关键点总结：
- 网址，eg.上述事例代码中的<code>https://movie.douban.com/</code>
- 数据格式，eg.上述事例代码中的<code>'//td[@class="title"]//a/text()'</code>
    - 具有一定规律，可通过查看 HTML 源码（浏览器 F12）得出
<img src="../../../../uploads/PythonSimpleWebCTest2.jpg" class="full-image" />
    - 其中：
      - <code>//td</code> ：相当于大目录；
      - <code>[@class="title"]</code>：相当于小目录；
      - <code>//a</code> ：这个相当于最小的目录；
      - <code>/text()</code>：这个是提取其中的数据。

# 4. 练习2：查看豆瓣-西安-影讯-上映内容
代码如下：
```Python
import requests
from lxml import html

url = 'https://movie.douban.com/cinema/later/xian/' # 数据的网址：豆瓣-西安-影讯-即将上映内容
page = requests.Session().get(url)
tree = html.fromstring(page.text)
# //div ：这个相当于指定是大目录；
# [@class="intro"]：这个相当于指定的小目录；
# //a ：这个相当于最小的目录；
# /text()：这个是提取其中的数据。
result = tree.xpath('//div[@class="intro"]//a/text()')
print(result)

# # 格式输出
# print("查看豆瓣-西安-影讯-即将上映内容")
# for i in result:
#     print(i, end='\n')
```

运行结果：
```Python
['港珠澳大桥', '预告片', '下一任：前任', '预告片', '悟空奇遇记', '预告片', '猫公主苏菲', '预告片', '国礼', '预告片', '大破天门阵', '柔情史', '预告片', '罗马', '预告片', '大侦探皮卡丘', '预告片', '进京城', '预告片', '一个母亲的复仇', '预告片', '欢迎来北方II', '预告片', '半边天', '预告片', '一路疯癫', '预告片', '周恩来回延安', '预告片', '海蒂和爷爷', '预告片', '企鹅公路', '预告片', '妈阁是座城', '预告片', '致命梦魇', '预告片', '音乐家', '预告片', '你好现任']
```

# 5. 备注
虽然实例代码比较简单，但实际中运行时仍会面临很多问题，比如： 
- 网页数据内容的规则难以归纳 
- 查看的数据不规范（需进一步处理） 
- 大部分网站拥有反Pa机制等
