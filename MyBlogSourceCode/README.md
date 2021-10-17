我的博客源码分享

- 本博客采用[Hexo](https://hexo.io/zh-cn/docs/)博客引擎驱动
- 本博客主题为[NexT v8.7.0](https://github.com/next-theme/hexo-theme-next)

# 1. 本博客所依赖的工具
- **Node.js**: [官网下载安装Node.js](http://nodejs.org/)，（npm -v，6.14.15）
- **Git**: [官网下载安装Git](http://git-scm.com/), （git --version，v2.29.2）
- **Hexo**: [参考Hexo官网命令行安装](https://hexo.io/zh-cn/), （hexo: v5.2.0, hexo-cli: v4.2.0）
- **Next主题**: [Next主题Git仓库](https://github.com/next-theme/hexo-theme-next)，（v8.7.0）

# 2. 本博客所依赖的 npm 组件列表
```shell
hexo-deployer-git@2.1.0
hexo-generator-archive@1.0.0
hexo-generator-category@1.0.0
hexo-generator-index@2.0.0
hexo-generator-searchdb@1.3.3
hexo-generator-tag@1.0.0
hexo-related-popular-posts@5.0.1
hexo-renderer-ejs@1.0.0
hexo-renderer-marked@3.3.0
hexo-renderer-stylus@2.0.1
hexo-server@2.0.0
hexo-tag-aplayer@3.0.4
hexo-tag-dplayer@0.3.3
hexo@5.2.0
intersection-observer@0.11.0
lozad@1.16.0
pangu@4.0.7
quicklink@2.0.0
```

# 3. 本博客构建总体流程分享
## 3.1. Hexo 生成基础 Blog 站点文件
```shell
YOUR_BLOG_DIR=eisenhao.github.io
hexo init ${YOUR_BLOG_DIR}
cd ${YOUR_BLOG_DIR}
```

## 3.2. 获取 Hexo 主题（eg. NexT）
```shell
git clone https://github.com/next-theme/hexo-theme-next themes/next
```

## 3.3. 自定义修改 Hexo 引擎配置文件
```shell
vi ./_config.yml
```

## 3.4. 自定义修改 NexT 主题配置文件
```shell
vi ./themes/next/_config.yml
```

## 3.5. 自定义安装所需 npm 小插件
```shell
# # Symbols count and time to read for articles in Hexo blog
# npm install hexo-word-counter
# # A hexo plugin that generates a list of links to related posts or popular posts.
# npm install hexo-related-popular-posts --save
# # Highly performant, light and configurable lazy loader in pure JS with no dependencies for images, iframes and more, using IntersectionObserver API
# npm install --save lozad
# # Automatically insert blank space between all Chinese characters and semi form English, numbers and symbols in the web page
# npm install pangu --save
# # automatically prefetch URLs for links that are in-viewport during idle time.
# npm install --save quicklink
# # A plugin to fix a serious security bug in leancloud visitor counter for NexT theme site and other site that integrated this function using a similar way.
# # npm install --save hexo-leancloud-counter-security
# # generating a search index file, which contains all the necessary data of your articles that you can use to write a local search engine for your blog
# npm install hexo-generator-searchdb
# npm install hexo-deployer-git --save
# npm install hexo-tag-dplayer --save
# npm install --save hexo-tag-aplayer
```

## 3.6. 深度修改 style, css, njk 站点文件源码... 

## 3.7. 博文撰写...

## 3.8. 本地构建博客站点文件与调测
```shell
# 生成站点文件
hexo clean && hexo g

# 启动本地调试服务
hexo s

# 打开浏览器访问 http://localhost:4000
```

## 3.9. 发布站点文件到远程服务器
hexo d

# 4. 克隆我的博客的调试步骤
1. 安装前文提及的依赖工具
2. 从博主的 [MyWorkspace](https://github.com/EisenHao/MyWorkspace) 仓库中，下载我的博客源码子文件（MyBlogSourceCode）
3. 进入站点目录
```shell
cd MyBlogSourceCode/eisenhao.github.io
```
4. 一键安装本博客所需的 npm 插件
```shell
npm install
```
5. （本地）调用 Hexo 命令进行 **清理旧站点文件**、**构建站点文件**、**开启本地调试服务**
```shell
hexo clean && hexo g && hexo s
```
6. 本地浏览器访问 http://localhost:4000/ 以进行调试
