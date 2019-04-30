'''
爬取豆瓣一周口碑榜的电影列表（十个）https://movie.douban.com/
CSDN博文地址：https://blog.csdn.net/csqazwsxedc/article/details/68498842
'''

import requests
from lxml import html

url = 'https://movie.douban.com/' #需要爬数据的网址
page = requests.Session().get(url)
tree = html.fromstring(page.text)
result = tree.xpath('//td[@class="title"]//a/text()')# 爬取豆瓣一周口碑榜的电影列表（十个）https://movie.douban.com/
# //td ：这个相当于指定是大目录；
# [@class=”title”]：这个相当于指定的小目录；
# //a ：这个相当于最小的目录；
# /text()：这个是提取其中的数据。

# 格式输出
print("爬取豆瓣一周口碑榜的电影列表（十个）:")
for i in result:
    print(i, end='\n')