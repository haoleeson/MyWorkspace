'''
网页爬虫练习2： 爬取豆瓣-西安-影讯-即将上映内容 https://movie.douban.com/cinema/later/xian/
'''

import requests
from lxml import html

url = 'https://movie.douban.com/cinema/later/xian/' #需要爬数据的网址：豆瓣-西安-影讯-即将上映内容
page = requests.Session().get(url)
tree = html.fromstring(page.text)
# //td ：这个相当于指定是大目录；
# [@class=”title”]：这个相当于指定的小目录；
# //a ：这个相当于最小的目录；
# /text()：这个是提取其中的数据。
result = tree.xpath('//div[@class="intro"]//a/text()') #爬取豆瓣爬取豆瓣-西安-影讯-即将上映内容
print(result)

# # 格式输出
# print("爬取豆瓣-西安-影讯-即将上映内容")
# for i in result:
#     print(i, end='\n')