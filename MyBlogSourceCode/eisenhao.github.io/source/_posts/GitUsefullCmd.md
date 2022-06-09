layout: post
title: Git 实用命令记录
date: 2021/7/24 17:54:44
updated: 2021/7/24 21:44:45
comments: true
tags:
- git
categories:
- 技术

---

<img src="https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/gitRevert.jpg" style="zoom:45%;"  />

记录Git生僻进阶用法，以备不时之需

<!-- more -->

常用基础命令速查：
<img src="https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/gitUsuallyUseCmd.png" style="zoom:35%;" />

# 1. Git 实用命令记录
## 1.1. Git 取出暂存区文件（保留文件更改）
```shell
# 将缓存区中文件取出到工作区，保留文件变更
git checkout -- file_path

# 不保留文件变更
git reset HEAD file_path
```

## 1.2. Git 取消对某个文件的跟踪
PS: 解决 .gitignore 文件对已跟踪的文件失效问题
```shell
# 列出需要取消跟踪的文件（未执行，检查）
git rm -r -n --cached <文件或目录>
# 取消（不想跟踪文件）的缓存
git rm -r --cached <文件或目录>
# 修改根目录 .gitignore 文件，添加
```

## 1.3. 丢弃文件修改（恢复文件）
```shell
git checkout HEAD file_path
```

## 1.4. 克隆子模块
默认不会在 clone 时下载
```shell
git submodule update --init --recursive
```

## 1.5. 统计代码提交行数
```shell
git log --author="user" --since==2000-01.01 --pretty=tformat: --numstat | gawk '{ add += $1 ; subs += $2 ; loc += $1 - $2 } END { printf "added lines: %s removed lines : %s total lines: %s\n",add,subs,loc }'
```

## 1.6. 提取当前 commit 到指定 commit 之前的所有提交
> 每此 commit 生成一个 *.patch 补丁文件
```shell
git format-patch 上一提交 ID
git format-patch b6c3a8bf
```

## 1.7. 补丁文件的制作、安装与取消
```shell
# 生成差异文件（补丁）
git diff -- filepath > differences.patch

# 打补丁
git apply differences.patch

# 取消补丁
git reset -hard HEAD
```

## 1.8. cherry pick
```shell
# -x 参数：在提交信息的末尾追加一行 (cherry picked from commit ...)
git cherry-pick -e -x <commit_id>
```

## 1.9. 分支更名
```shell
git branch -m 原名 新名
```

## 1.10. 忽略部分本地修改
eg. 个人定制 IDE 或者 Build 工具的配置文件
```shell
# Git 忽略本地对这个文件的所有修改
git update-index --skip-worktree /path/to/file

# 恢复
git update-index --no-skip-worktree /path/to/file

# 查看被忽略的文件项目
git ls-files -v | grep -E -i /path/to/file
git ls-files -v | Select-String -Pattern /path/to/file
```

备注：
- [Git 四种忽略本地文件修改的方法对比](https://mengqi92.github.io/2020/07/17/hide-files-from-git/)：
  - [gitignore 文件](https://git-scm.com/docs/gitignore)
  - .git/info/exclude 文件
  - [git update-index --assume-unchanged](https://www.git-scm.com/docs/git-update-index)
  - [git update-index --skip-worktree](https://www.git-scm.com/docs/git-update-index)

## 1.11. 对比指定文件在本地分支与远端分支的差异

<b><font color="#7E3D76" style="">1. 对比指定【单个文件】在【本地分支与远端】分支的差异</font></b>

可以识别到暂存区中未提交的修改（其他跨分支的比较均无法识别暂存区中未提交的修改）。

前置条件：本地当前分支在远端有相对应分支。

示例代码：
```shell
git diff --stat -- src/file1.cpp src/file1.cpp
```

--stat 参数作用：显示简要信息（精度到文件），默认 diff 会显示精度到行的差异信息

只需填写需对比的文件路径分别在本地和远端分支各自的地址即可，第一个路径为本地文件地址，第二个路径为远端仓库文件地址（此示例两文件路径相同）

<b><font color="#7E3D76" style="">2. 对比指定的多个文件在两分支间的差异</font></b>
```shell
git diff --stat master dev  -- file1.md src/file2.java
```

## 1.12. 对比俩分支文件差异

<b><font color="#7E3D76" style="">1. 对比【本地两分支】差异</font></b>

比较本地 master 和 dev 分支所有文件的差异
```shell
git diff --stat master dev
```

<b><font color="#7E3D76" style="">2. 对比【本地两分支】差异（限定文件）</font></b>

只比较关注的指定文件，在本地 master 和 dev 分支的差异
```shell
git diff --stat master dev -- filepath1 filepath2 filepath3
```

<b><font color="#7E3D76" style="">3. 对比【本地分支与远端分支】差异</font></b>

比较本地 dev 分支和远端 master 分支所有文件的差异
```shell
git diff --stat dev origin/master
```

<b><font color="#7E3D76" style="">4. 对比【本地分支与远端分支】差异（限定文件）</font></b>

比较指定文件，在本地 dev 分支和远端 master 分支的差异
```shell
git diff --stat dev origin/master -- filepath1 filepath2 filepath3
```

## 1.13. 对比两分支的"commit 差异"
```shell
git log --left-right --stat master...dev
git log --left-right --oneline master...dev
```

## 1.14. 在远端仓库新建一个分支

实现方式：本地建分支后同步到远端仓库
```shell
git checkout -b newBranch origin/master
git push --set-upstream origin newBranch
```

## 1.15. 删除远端分支
```shell
git branch -r -d origin/newBranch
```

## 1.16. 本地分支与远端分支关联
```shell
git checkout --track origin/branchName
```

## 1.17. Cherry pick
常用用法：
```shell
git cherry-pick [Option] <commit-id>

# 示例
git cherry-pick -e -x 123456
```

附加参数：
- <code>-e，--edit</code> 。打开外部编辑器，编辑提交信息。
- <code>-n，--no-commit</code> 。只更新工作区和暂存区，不产生新的提交。
- <code>-x</code> 。在提交信息的末尾追加一行 (cherry picked from commit ...)，方便以后查到这个提交是如何产生的。
- <code>-s，--signoff</code> 。在提交信息的末尾追加一行操作者的签名，表示是谁进行了这个操作。
- <code>-m parent-number，--mainline parent-number</code> 。如果原始提交是一个合并节点，来自于两个分支的合并，那么 Cherry pick 默认将失败，因为它不知道应该采用哪个分支的代码变动。-m 配置项告诉 Git，应该采用哪个分支的变动。它的参数 parent-number 是一个从 1 开始的整数，代表原始提交的父分支编号。

若发生 Cherry-pick 冲突：
- 若能成功解决冲突，则继续 cherry-pick 过程。
```shell
git add <成功处理后的冲突文件>
git cherry-pick --continue
```

- 若未能成功解决冲突，可终止 cherry-pick 过程。
```shell
# 终止 cherry-pick 过程，且恢复到操作之前的状态
git cherry-pick --abort

# 注：quit 虽能退出 Cherry pick ，但不能恢复到操作之前的状态。
git cherry-pick --quit
```

## 1.18. git 分支改名
```shell
git branch -m ${原分支名} ${新分支名}
```

## 1.19. 撤销暂存区文件（git add 的逆向，保留修改）
```shell
git reset HEAD files
```

# 2. Git 命令进阶用法

## 2.1. reset 回滚

reset 参数说明：
- --hard：重置时清空工作目录的所有改动
- --soft：重置时保留工作目录和暂存区的内容；
- --mixed（默认）：重置时保留工作目录的内容，并清空暂存区。
```shell
git reset --hard HEAD^          # 方式 1：回滚到上一次提交
git reset --hard ${commitID}    # 方式 2：回滚到指定 commit 处，丢弃其后所有 commit
git reflog                      # 方式 3：撤销历史操作（如撤销上一次回滚操作）
git reset --hard ${历史操作 ID}
```

## 2.2. amend 修复上次提交的操作
```shell
git add ${changeFiles}  # s1. 将修复错误的文件添加到提交
git commit --amend      # s2. 修复上次提交，注意 amend 只适用于还处于评审中的 CR。
```

## 2.3. 恢复单个文件到最新提交
```shell
git checkout HEAD path_to_file
```

## 2.4. rebase 变基的操作步骤
前置条件：dev 分支拉取自 master（eg.dev 分支拉取时间：20210715），且在之后（eg.20210720）master 又有新提交（或合入），且现在（eg.20210730）dev 分支需要在引入该新提交（或合入）后再开发。

变基操作成功执行后，dev 分支相当于是从变基操作时（eg.20210730）新拉取的分支，且 (20210715 ~ 20210730) 之间的提交和修改仍保留。
```shell
git checkout dev        # s1. 切换到待变基分支 dev
git rebase master       # s2. 将分支的起点移动到想要合并的分支的 HEAD 上

git checkout master     # s3. 切换到主分支（本地）
git merge dev           # s4. 移到最新的提交
```

## 2.5. rebase 修改完善之前某次提交的操作步骤
```shell
# s1. 触发 git 修改弹窗，将对应 commit 标记为 edit。
git rebase -i ${commitID}
# s2. 修改完善某次提交的文件
# s3. 添加已修改的文件
git add changedFiles
# s4. 将修正应用到当前最新的 commit
git commit --amend
# s5. 继续 rebase 过程。
git rebase --continue
```

## 2.6. rebase 撤销过往提交命令的两种方式

<b><font color="#7E3D76" style="">1. 方式 1——触发 git 修改并在弹出 git 编辑界面中删除想撤销的 commits</font></b>
实现原理：在触发的 git 编辑界面中添加 drop ${待删除 commitID}

```shell
# s1. 触发 rebase 编辑界面
git rebase -i ${待删除的前一条 commitID}
# s2. 在修改文件中 pick commitId.. 下方将 pick 命令改为丢弃命令
pick ${待删除 commitID}  ==》  drop ${待删除 commitID}
# s3. 手动解决${冲突 files}的冲突
vi ${冲突 files}
# s4. 添加已修改的文件
git add ${冲突 files}
# s5. 继续 rebase 过程
git rebase --continue
```

<b><font color="#7E3D76" style="">2. 方式 2——将修正应用到当前最新的 commit</font></b>

实现原理：对本地当前分支，将左开右闭区间 (commitID_B, commitID_C] 的提交覆盖到 commitID_A 之后。相当于原左开右闭区间 (commitID_A, commitID_B] 的提交被删除了。

示例代码：

当前分支提交记录顺序为：commitID_A, ... , commitID_B , ... , commitID_C。现要删除左开右闭区间 (commitID_A, commitID_B] 的提交：
```shell
# s1. 触发 rebase
git rebase --onto ${目标 commitID_A} ${起点 commitID_B} ${终点 commitID_C}
# s2. 手动解决${冲突 files}的冲突
vi ${冲突 files}
# s3. 添加已修改的文件
git add ${冲突 files}
# s4. 继续 rebase 过程
git rebase --continue
```

## 2.7. 根据操作历史回退
根据 git 操作历史记录回退，eg. 撤销上一步 git reset --hard 操作，以恢复到执行该操作前的状态（需确保 git 全局配置中 core.logallrefupdates 已打开 true）
```shell
# s1. 查询 git 操作命令历史记录对应的${上一步操作 ID}
git reflog
# s2. 恢复到执行该操作的前一个操作状态
git reset --hard ${上一步操作 ID}
```

# 参考博文
- [Git 合并多次 commit 、 删除某次 commit](https://www.cnblogs.com/zhaoyingjie/p/10259715.html)
- [git diff 比较本地文件记录和远程文件记录的修改项](https://blog.csdn.net/weixin_34268843/article/details/92032933)
