#!bin/bash

# Brief      : Include a sub git repo to current repo(Keep commit records)
# Description: Run this shell in your Root Repo Dir
# Param1     : sub repo name
# Param2     : sub repo branch name

# Input args check
if [ $# == 0 ] && [ ! -n "$1" ]; then
    echo "input empty args"
    exit 0;
fi

SUB_REPO_NAME=$1
# SUB_REPO_NAME=MySpark

ROOT_BRANCH_NAME=main
#default branch name
SUB_REPO_BRANCH_NAME=master

if [ $# > 1 ] && [ -n "$2" ]; then
    SUB_REPO_BRANCH_NAME=$2
    # SUB_REPO_BRANCH_NAME=main
fi

GIT_USER_NAME=EisenHao
GIT_REPO_URL=git@github.com:${GIT_USER_NAME}/${SUB_REPO_NAME}.git

echo "SUB_REPO_NAME=${SUB_REPO_NAME}"
echo "SUB_REPO_BRANCH_NAME=${SUB_REPO_BRANCH_NAME}"

# Add sub remote repo
git remote add sub${SUB_REPO_NAME} ${GIT_REPO_URL}

# Fetch commits of sub remote repo
git fetch sub${SUB_REPO_NAME}

# Checkout sub remote repo
git checkout -b sub${SUB_REPO_NAME}_${SUB_REPO_BRANCH_NAME} sub${SUB_REPO_NAME}/${SUB_REPO_BRANCH_NAME}

# Checkout return to Root Repo branch
git checkout ${ROOT_BRANCH_NAME}

# Merge sub repo to Root Repo(allow unrelated histories)
git merge sub${SUB_REPO_NAME}_${SUB_REPO_BRANCH_NAME} --allow-unrelated-histories

# Del sub repo branch
git branch -d sub${SUB_REPO_NAME}_${SUB_REPO_BRANCH_NAME}

# Del remote
git remote rm sub${SUB_REPO_NAME}

# Push to Root Repo forcely
git push origin HEAD --force

# bug fix
rm -rf 1
