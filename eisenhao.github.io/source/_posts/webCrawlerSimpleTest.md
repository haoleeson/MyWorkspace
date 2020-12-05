layout: post
title: Python简单网页爬虫练习
date: 2019/04/30 11:28:44
updated: 2019/04/30 12:48:45
comments: true
tags:
- Python
categories:
- 技术

---
<img src="https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/webCrawlerSimpleTest.jpg" class="full-image" />
# 爬取豆瓣一周口碑榜的电影列表
先展示爬取结果：
``` Python
爬取豆瓣一周口碑榜的电影列表（十个）:
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
# 准备工作
* 安装Python环境。详见[安装Python3.7](https://eisenhao.cn/2018/09/23/AfterInstallManjaro/#%E5%AE%89%E8%A3%85Python3-7)
* 使用pip3安装requests、lxml模块。参考[使用pip3安装Numpy模块](https://eisenhao.cn/2018/09/23/AfterInstallManjaro/#%E4%BD%BF%E7%94%A8pip3%E5%AE%89%E8%A3%85Numpy%E6%A8%A1%E5%9D%97)
* 运行平台：终端或Python IDE软件(eg.[PyCharm](http://www.jetbrains.com/pycharm/))

# 开始动手吧
仅9行代码能爬豆瓣一周口碑榜的电影列表?
答案是肯定的，运行下方python代码即可实现首部结果。
```Python 源码文件:webCrawlerTest1.py
# 爬取豆瓣一周口碑榜的电影列表（十个）https://movie.douban.com/
import requests
from lxml import html

url = 'https://movie.douban.com/' #需要爬数据的网址
page = requests.Session().get(url)
tree = html.fromstring(page.text)
result = tree.xpath('//td[@class="title"]//a/text()')# 爬取豆瓣一周口碑榜的电影列表（十个）https://movie.douban.com/
# //td ：这个相当于指定是大目录；
# [@class="title"]：这个相当于指定的小目录；
# //a ：这个相当于最小的目录；
# /text()：这个是提取其中的数据。

# 格式输出
print("爬取豆瓣一周口碑榜的电影列表（十个）:")
for i in result:
    print(i, end='\n')
```

# 总结
## 爬取网页内容关键点：
* 待爬取网页地址，eg.上述事例代码中的'https://movie.douban.com/'
* 待爬取网页数据格式，eg.上述事例代码中的'//td[@class="title"]//a/text()'

## 网页数据格式
对于第二点获取网页数据格式，只能通过在网页浏览器F12查看HTML源码归纳总结得出
点击菜单栏左上按钮后再点击网页的待爬取内容，此时浏览器会跳转到该内容部分对应的HTML源码的对应代码，归纳总结源码得出正则表达式。
<img src="https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/webCrawlerSimpleTest_2.jpg" class="full-image" />
可以看出上图中选中的HTML代码部分与归纳得出的规则<code>'//td[@class="title"]//a/text()'</code>具有很大的相似度。
其中：
* //td ：这个相当于指定是大目录；
* [@class="title"]：这个相当于指定的小目录；
* //a ：这个相当于最小的目录；
* /text()：这个是提取其中的数据。

# 练习
爬虫小白上手简单用例就结束了，点击网页的即将上映，更改实例代码爬取“即将上映”练手试试吧！注意待爬取网页地址和内容格式一般不会有什么大问题。

针对上例爬取网页内容关注的两点：
* 待爬取网页地址，eg.上述事例代码中的'https://movie.douban.com/cinema/later/xian/'
* 待爬取网页数据格式，eg.上述事例代码中的'//div[@class="intro"]//a/text()'

```Python 源码文件:webCrawlerTest2.py
# 网页爬虫练习2： 爬取豆瓣-西安-影讯-即将上映内容 https://movie.douban.com/cinema/later/xian/
import requests
from lxml import html

url = 'https://movie.douban.com/cinema/later/xian/' #需要爬数据的网址：豆瓣-西安-影讯-即将上映内容
page = requests.Session().get(url)
tree = html.fromstring(page.text)
# //div ：这个相当于指定是大目录；
# [@class="intro"]：这个相当于指定的小目录；
# //a ：这个相当于最小的目录；
# /text()：这个是提取其中的数据。
result = tree.xpath('//div[@class="intro"]//a/text()') #爬取豆瓣爬取豆瓣-西安-影讯-即将上映内容
print(result)

# # 格式输出
# print("爬取豆瓣-西安-影讯-即将上映内容")
# for i in result:
#     print(i, end='\n')
```

运行结果：
```Python
['港珠澳大桥', '预告片', '下一任：前任', '预告片', '悟空奇遇记', '预告片', '猫公主苏菲', '预告片', '国礼', '预告片', '大破天门阵', '柔情史', '预告片', '罗马', '预告片', '大侦探皮卡丘', '预告片', '进京城', '预告片', '一个母亲的复仇', '预告片', '欢迎来北方II', '预告片', '半边天', '预告片', '一路疯癫', '预告片', '周恩来回延安', '预告片', '海蒂和爷爷', '预告片', '企鹅公路', '预告片', '妈阁是座城', '预告片', '致命梦魇', '预告片', '音乐家', '预告片', '你好现任']
```

# 拓展
虽然实例代码比较简单，但实际中运行爬虫时仍会面临很多问题，比如： 
* 网页数据内容的规则难以归纳 
* 爬取的数据不规范（需进一步处理） 
* 大部分网站拥有反爬虫机制等

参考博文：[5分钟，6行代码教你写爬虫！（python）](https://blog.csdn.net/csqazwsxedc/article/details/68498842)
