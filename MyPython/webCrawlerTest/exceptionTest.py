'''
error属性里面主要包括了两个重要的exception类，URLError类和HTTPError类。

- URLError类是OSError的子类，继承OSError，没有自己的任何行为特点，但是将作为error里面所有其它类型的基类使用。
- URLError类初始化定义了reason参数，意味着当使用URLError类的对象时，可以查看错误的reason。

- HTTPError是URLError的子类，当HTTP发生错误将举出HTTPError。
- HTTPError也是HTTP有效回应的实例，因为HTTP协议错误是有效的回应，包括状态码，headers和body。所以看到在HTTPError初始化的时候定义了这些有效回应的参数。
- 当使用HTTPError类的对象时，可以查看状态码，headers等。

下方代码使用了try..exception的结构，实现了简单的网页爬取，当有异常时，如URLError发生时，就会返回reason，或者HTTPError发生错误时就会返回code。异常的增加丰富了爬取的结构，使其更加健壮。
'''

import urllib.request
import urllib.error

try:
    # 防止反爬机制，添加header
    headers = {
        'User_Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/72.0.3626.121 Safari/537.36'}
    req = urllib.request.Request('http://www.baidu.com/', headers=headers)

    # response = urllib.request.urlopen('http://www.baidu.com/') # 方式1：直接用网址
    response = urllib.request.urlopen(req)  # 方式2：用Request对象，可添加头（防反爬机制）
    result = response.read().decode('utf-8')
    print(result)
except urllib.error.URLError as e:
    if hasattr(e, 'reason'):
        print('错误原因是' + str(e.reason))
except urllib.error.HTTPError as e:
    if hasattr(e, 'code'):
        print('错误状态码是' + str(e.code))
else:
    print('请求成功通过。')