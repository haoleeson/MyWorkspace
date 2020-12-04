# MyBlogSourceCode
我的博客源码

## clone 方式
```shell
# 将我的博客源码及子模块源码一起克隆下来
git clone --recursive https://github.com/EisenHao/MyBlogSourceCode.git
# cd 到下来仓库，执行下方命令确保子模块已经下载完全了
git submodule update --init --recursive1
```
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

# 将 NexT Git 仓库添加为子模块
git submodule add https://github.com/next-theme/hexo-theme-next eisenhao.github.io/themes/next

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