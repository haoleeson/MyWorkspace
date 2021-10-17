layout: post
title: Git实用命令记录
date: 2021/07/25 19:41:44
comments: true
tags:

- git
categories:
- 技术

---
<img src="https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/gitRevert.jpg" style="zoom:45%;"  />

<!-- more -->

# 1. Git常用基础命令

<img src="https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/gitUsuallyUseCmd.png" style="zoom:35%;" />

# 2. Git实用操作命令

## 2.1. 对比指定文件在本地分支与远端分支的差异

<b><font color="#7E3D76" style="">1. 对比指定【单个文件】在【本地分支与远端】分支的差异</font></b>

可以识别到暂存区中未提交的修改（其他跨分支的比较均无法识别暂存区中未提交的修改）。

前置条件：本地当前分支在远端有相对应分支。

示例代码：
```shell
git diff --stat -- src/file1.cpp src/file1.cpp
```

--stat参数作用：显示简要信息（精度到文件），默认diff会显示精度到行的差异信息

只需填写需对比的文件路径分别在本地和远端分支各自的地址即可，第一个路径为本地文件地址，第二个路径为远端仓库文件地址（此示例两文件路径相同）

<b><font color="#7E3D76" style="">2. 对比指定的多个文件在两分支间的差异</font></b>
```shell
git diff --stat master dev  -- file1.md src/file2.java
```

## 2.2. 对比俩分支文件差异

<b><font color="#7E3D76" style="">1. 对比【本地两分支】差异</font></b>

比较本地master和dev分支所有文件的差异
```shell
git diff --stat master dev
```

<b><font color="#7E3D76" style="">2. 对比【本地两分支】差异（限定文件）</font></b>

只比较关注的指定文件，在本地master和dev分支的差异
```shell
git diff --stat master dev -- filepath1 filepath2 filepath3
```

<b><font color="#7E3D76" style="">3. 对比【本地分支与远端分支】差异</font></b>

比较本地dev分支和远端master分支所有文件的差异
```shell
git diff --stat dev origin/master
```

<b><font color="#7E3D76" style="">4. 对比【本地分支与远端分支】差异（限定文件）</font></b>

比较指定文件，在本地dev分支和远端master分支的差异
```shell
git diff --stat dev origin/master -- filepath1 filepath2 filepath3
```

## 2.3. 对比两分支commit差异
```shell
git log --left-right --stat master...dev
```

## 2.4. 在远端仓库新建一个分支

实现方式：本地建分支后同步到远端仓库
```shell
git checkout -b newBranch origin/master
git push --set-upstream origin newBranch
```

## 2.5. 删除远端分支
```shell
git branch -r -d origin/newBranch
```

## 2.6. 本地分支与远端分支关联
```shell
git checkout --track origin/branchName
```

# 3. Git命令进阶用法

## 3.1. reset 回滚

reset参数说明：
- --hard：重置时清空工作目录的所有改动
- --soft：重置时保留工作目录和暂存区的内容；
- --mixed（默认）：重置时保留工作目录的内容，并清空暂存区。

```shell
git reset --hard HEAD^          # 方式1：回滚到上一次提交
git reset --hard ${commitID}    # 方式2：回滚到指定commit处，丢弃其后所有commit
git reflog                      # 方式3：撤销历史操作（如撤销上一次回滚操作）
git reset --hard ${历史操作ID}
```

## 3.2. amend 修复上次提交的操作
```shell
git add ${changeFiles}  # s1.将修复错误的文件添加到提交
git commit --amend      # s2.修复上次提交，注意amend只适用于还处于评审中的CR。
```

## 3.3. rebase 变基的操作步骤
前置条件：dev分支拉取自master（eg.dev分支拉取时间：20210715），且在之后（eg.20210720）master又有新提交（或合入），且现在（eg.20210730）dev分支需要在引入该新提交（或合入）后再开发。

变基操作成功执行后，dev分支相当于是从变基操作时（eg.20210730）新拉取的分支，且(20210715 ~ 20210730)之间的提交和修改仍保留。
```shell
git checkout dev        # s1.切换到待变基分支dev
git rebase master       # s2.将分支的起点移动到想要合并的分支的HEAD上

git checkout master     # s3.切换到主分支（本地）
git merge dev           # s4.移到最新的提交
```

## 3.4. rebase 修改完善之前某次提交的操作步骤
```shell
# s1.触发git修改弹窗，将对应commit标记为edit。
git rebase -i ${commitID}
# s2.修改完善某次提交的文件
# s3.添加已修改的文件
git add changedFiles
# s4.将修正应用到当前最新的 commit
git commit --amend
# s5.继续rebase过程。
git rebase --continue
```

## 3.5. rebase 撤销过往提交命令的两种方式

<b><font color="#7E3D76" style="">1. 方式1——触发git修改并在弹出git编辑界面中删除想撤销的commits</font></b>
实现原理：在触发的git编辑界面中添加drop ${待删除commitID}

```shell
# s1. 触发rebase编辑界面
git rebase -i ${待删除的前一条commitID}
# s2. 在修改文件中pick commitId.. 下方将pick命令改为丢弃命令
pick ${待删除commitID}  ==》  drop ${待删除commitID}
# s3. 手动解决${冲突files}的冲突
vi ${冲突files}
# s4. 添加已修改的文件
git add ${冲突files}
# s5. 继续rebase过程
git rebase --continue
```

<b><font color="#7E3D76" style="">2. 方式2——将修正应用到当前最新的commit</font></b>

实现原理：对本地当前分支，将左开右闭区间 (commitID_B, commitID_C] 的提交覆盖到 commitID_A 之后。相当于原左开右闭区间(commitID_A, commitID_B]的提交被删除了。

示例代码：

当前分支提交记录顺序为：commitID_A, ... , commitID_B , ... , commitID_C。现要删除左开右闭区间(commitID_A, commitID_B]的提交：
```shell
# s1. 触发rebase
git rebase --onto ${目标commitID_A} ${起点commitID_B} ${终点commitID_C}
# s2. 手动解决${冲突files}的冲突
vi ${冲突files}
# s3. 添加已修改的文件
git add ${冲突files}
# s4. 继续rebase过程
git rebase --continue
```

## 3.6. 根据操作历史回退
根据git操作历史记录回退，eg.撤销上一步git reset --hard操作，以恢复到执行该操作前的状态（需确保git全局配置中core.logallrefupdates已打开true）
```shell
# s1.查询git操作命令历史记录对应的${上一步操作ID}
git reflog
# s2.恢复到执行该操作的前一个操作状态
git reset --hard ${上一步操作ID}
```

# 4. 参考文档
- [Git 合并多次 commit 、 删除某次 commit](https://www.cnblogs.com/zhaoyingjie/p/10259715.html)
- [git diff 比较本地文件记录和远程文件记录的修改项](https://blog.csdn.net/weixin_34268843/article/details/92032933)

