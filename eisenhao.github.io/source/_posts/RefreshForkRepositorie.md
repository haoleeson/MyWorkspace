layout: post
title: Fork仓库同步官方源仓库的更新
date: 2019/11/18 21:31:44
updated: 2019/11/18 21:31:45
comments: true
tags:
- git
categories:
- 技术
---
<img src="https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/RefreshForkRepositorie.png" class="full-image" />

Fork仓库是对应官方源仓库的一份完全备份（类似快照，但却不能再接收到官方源仓库的更新内容），然而有时咱们需要Fork仓库涵盖官方源仓库的最新提交代码。本文总结介绍了从官方源仓库同步更新内容到Fork仓库的方法，过程大致如下：向本地Fork仓库添加官方源仓库远端，再获取(fetch)官方源仓库的更新内容到本地仓库，然后合并官方源仓库的更新内容到本地Fork仓库，最后推送到远端Fork仓库。

<!-- more -->

# 1. 步骤一、添加官方源仓库远端

## 1.1. 查看远端仓库

查看本地Fork仓库的远端信息
```
git remote -v
```
一般此时查询的结果只有一个Fork仓库远端（共两行fetch + push）eg.
```
origin      ssh://git@xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.git (fetch)
origin      ssh://git@xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.git (push)
```
其中 “origin” （默认值）为本地设置的Fork远端仓库的远端别名， 而“ssh://git@xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.git“ 对应为你的Fork仓库地址

## 1.2. 添加官方源仓库远端
添加官方源仓库远端到本地Fork仓库，使具有两个远端
```
git remote add origin_official https://oooooooooooooooooooooooooooooo.git
```
其中 “origin_official” 为自定义官方源仓库在本地的远端别名， “https://oooooooooooooooooooooooooooooo.git" 为官方源仓库地址

## 1.3. 再次检查本地的远程信息
```
git remote -v
```
此时查询本地Fork仓库应该有两个远端，一个Fork仓库远端和一个官方源仓库远端（共四行）eg.
```
origin            ssh://git@xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.git (fetch)
origin            ssh://git@xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.git (push)
origin_official   https://oooooooooooooooooooooooooooooo.git(fetch)
origin_official   https://oooooooooooooooooooooooooooooo.git(push)
```

# 2. 步骤二、获取远程官方源仓库的更新内容

## 2.1. 通过fetch命令获得一份官方源仓库的更新内容到本地Fork仓库
```
git fetch origin_official
```

## 2.2. 检查并切换到想同步更新的分支(一般为master分支)

### 2.2.1. 检查当前分支
```
git branch
```
一般此时查询结果为origin/master分支（默认），其对应远端分支为Fork远端仓库的master分支。若当前本地Fork仓库有未提交的修改内容则需先推送修改内容到Fork仓库远端，否则可能为后面合并操作带来不必要的工作量。

### 2.2.2. 切换到非master分支（可选）
若待同步的源仓库更新内容不在master分支，则需手动切换到对应分支（如xxxxxx分支），否则可跳过此## 步骤。切换到待同步源仓库远端分支有更新内容对应的Fork仓库在本地仓库的分支（有点绕，如xxxxxx分支）
```
git checkout -b xxxxxxFork origin/master
```
其中 “xxxxxxFork” 为自定义本地分支名，对应Fork仓库的xxxxxx分支， “origin” 对应Fork仓库远端别名

# 3. 步骤三、合并官方源仓库的更新内容到本地仓库
合并官方源仓库的更新内容到本地仓库对应分支(一般为master分支)。如合并origin_official/master的更新内容到本地Fork仓库的master分支（默认分支），若为其他分支则替换为对应分支便可（如：替换master为xxxxxx）
```
git merge origin_official/master
```
如果当前的本地仓库包含未提交的内容，则会提示合并失败，此时需要先推送本地修改内容到Fork仓库远端，再执行该合并操作。如果更新内容与本地仓库内容区别较大git合并时报冲突也会提示合并失败，处理冲突后便可完成合并

# 4. 步骤四、推送本地代码到远端Fork仓库
此时本地Fork仓库的master分支已包含官方源仓库master分支的更新内容，再执行push操作将这些更新内容推送到自己的远端Fork仓库即可
```
git push origin master
```
至此，已完成同步官方源仓库mater分支的所有更新到Fork仓库。