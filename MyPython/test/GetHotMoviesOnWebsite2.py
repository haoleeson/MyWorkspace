# 获取网页内容练习2： 获取豆瓣-西安-影讯-即将上映内容 https://movie.douban.com/cinema/later/xian/
import requests
from lxml import html

url = 'https://movie.douban.com/cinema/later/xian/' #需要获取数据的网址：豆瓣-西安-影讯-即将上映内容
page = requests.Session().get(url)
tree = html.fromstring(page.text)
# //div ：这个相当于指定是大目录；
# [@class="intro"]：这个相当于指定的小目录；
# //a ：这个相当于最小的目录；
# /text()：这个是提取其中的数据。
result = tree.xpath('//div[@class="intro"]//a/text()') #获取豆瓣-西安-影讯-即将上映内容
print(result)

# # 格式输出
# print("获取豆瓣-西安-影讯-即将上映内容")
# for i in result:
#     print(i, end='\n')



# 运行结果：
# ['港珠澳大桥', '预告片', '下一任：前任', '预告片', '悟空奇遇记', '预告片', '猫公主苏菲', '预告片', '国礼', '预告片', '大破天门阵', '柔情史', '预告片', '罗马', '预告片', '大侦探皮卡丘', '预告片', '进京城', '预告片', '一个母亲的复仇', '预告片', '欢迎来北方II', '预告片', '半边天', '预告片', '一路疯癫', '预告片', '周恩来回延安', '预告片', '海蒂和爷爷', '预告片', '企鹅公路', '预告片', '妈阁是座城', '预告片', '致命梦魇', '预告片', '音乐家', '预告片', '你好现任']