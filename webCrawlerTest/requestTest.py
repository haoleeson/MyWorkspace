'''
request的使用练习：请求百度首页，并将获取内容存文件

urlopen方法:
def urlopen(url, data=None, timeout=socket._GLOBAL_DEFAULT_TI
            MEOUT,*, cafile=None, capath=None,
            cadefault=False, context=None):
Request方法:
class Request:
    def __init__(self, url, data=None, headers={},
                 origin_req_host=None, unverifiable=False,
                 method=None):
'''

import urllib.request

#自定义保存文件函数
def saveToFile(file_name, file_content):
    #注意windows文件命名的禁用符，比如 /
    with open(file_name.replace('/', '_')+".html", "wb") as f:
        #写文件用bytes而不是str，所以要转码 （str -> bytes）
        f.write(bytes(file_content, encoding="utf8"))


# 防止反爬机制，添加header
headers = {'User_Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/72.0.3626.121 Safari/537.36'}
req = urllib.request.Request('http://www.baidu.com/', headers=headers )

# response = urllib.request.urlopen('http://www.baidu.com/') # 方式1：直接用网址
response = urllib.request.urlopen(req) # 方式2：用Request对象，可添加头（防反爬机制）
result = response.read().decode('utf-8')
print(result)

saveToFile("test1", result)