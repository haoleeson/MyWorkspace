# 获取豆瓣一周口碑榜 https://movie.douban.com/
import requests
from lxml import html

url = 'https://movie.douban.com/' #需要获取数据的网址
page = requests.Session().get(url)
tree = html.fromstring(page.text)
result = tree.xpath('//td[@class="title"]//a/text()')
# //td ：这个相当于指定是大目录；
# [@class="title"]：这个相当于指定的小目录；
# //a ：这个相当于最小的目录；
# /text()：这个是提取其中的数据。

# 格式输出
print("获取豆瓣一周口碑榜:")
for i in result:
    print(i, end='\n')


# 运行结果：
# 获取豆瓣一周口碑榜:
# 复仇者联盟4：终局之战
# 触不可及(美版)
# 盗梦特攻队
# 深红累之渊
# 遇见女孩的感觉
# 撞死了一只羊
# 归家：碧昂斯电影作品
# 西班牙之旅
# 娑婆诃
# 番石榴岛

# 关键点总结：
# - 网址，eg.上述事例代码中的'https://movie.douban.com/'
# - 数据格式，eg.上述事例代码中的'//td[@class="title"]//a/text()'
#     - 具有一定规律，可通过查看 HTML 源码（浏览器 F12）得出
# <img src="https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/PythonSimpleWebCTest2.jpg" class="full-image" />
#     - 其中：
#       - //td ：这个相当于指定是大目录；
#       - [@class="title"]：这个相当于指定的小目录；
#       - //a ：这个相当于最小的目录；
#       - /text()：这个是提取其中的数据。
