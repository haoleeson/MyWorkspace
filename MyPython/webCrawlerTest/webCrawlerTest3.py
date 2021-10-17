'''
实战：
爬取老D博客 访客留言板 https://laod.cn/guestbook
'''

import requests
from lxml import html

url = 'https://laod.cn/guestbook' #需要爬数据的网址
page = requests.Session().get(url)
tree = html.fromstring(page.text)
result = tree.xpath('//div[@class="comment-body"]//p/text()')# 爬取豆瓣一周口碑榜的电影列表（十个）https://movie.douban.com/
# //td ：这个相当于指定是大目录；
# [@class=”title”]：这个相当于指定的小目录；
# //a ：这个相当于最小的目录；
# /text()：这个是提取其中的数据。

# 格式输出
print("爬取老D博客 访客留言板:")
for i in result:
    print(i, end='\n')