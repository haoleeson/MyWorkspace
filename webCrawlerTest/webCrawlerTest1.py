# 爬取豆瓣一周口碑榜的电影列表（十个）
# https://movie.douban.com/

import requests
from lxml import html

url = 'https://movie.douban.com/' #需要爬数据的网址
page = requests.Session().get(url)
tree = html.fromstring(page.text)
result = tree.xpath('//td[@class="title"]//a/text()') #获取需要的数据
print(result)