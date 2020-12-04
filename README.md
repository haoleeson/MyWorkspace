# MyBlogSourceCode
我的博客源码

* 本博客采用[Hexo](https://hexo.io/zh-cn/docs/)博客框架
* 本博客主题为[NexT v8.1.0](https://github.com/next-theme/hexo-theme-next)

## 依赖
* [Node.js](http://nodejs.org/)
* [Git](http://git-scm.com/)
* [Hexo](https://hexo.io/zh-cn/)

## 依赖 npm 组件
* 


## 流程
```shell 
# 建站
hexo init eisenhao.github.io
cd eisenhao.github.io
npm install

# 获取 NexT 主题
mkdir themes/next
# 下载最新 Release tar包
cd themes/next
curl -o next.tar.gz --insecure https://codeload.github.com/next-theme/hexo-theme-next/tar.gz/v8.1.0
# 解压
tar -zxf next.tar.gz
# 重命名文件夹为 next
mv hexo-theme-next-8.1.0 next
cd ../../

# 修改 Hexo 配置文件
vi ./_config.yml

# 修改 NexT 配置文件
vi ./themes/next/_config.yml

# 为博客添加文章
# ...

# 构建静态博客网站
hexo Clean && hexo g

# 本地调试（http://localhost:4000）
hexo s

# 发布
hexo d
```