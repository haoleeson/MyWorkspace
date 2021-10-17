#!/bin/bash

# Brief      : Add a Root Dir to a Git repo
# Description: run this shell in your anywhere you like
# Param1     : repo name
# Param2     : root dir name

# Input args check
if [ $# == 0 ] && [ ! -n "$1" ]; then
    echo "input empty args"
    exit 0;
fi

GIT_USER_NAME=EisenHao
REPO_NAME=$1
ROOT_DIR_NAME=${REPO_NAME}
GIT_REPO_URL=git@github.com:${GIT_USER_NAME}/${REPO_NAME}.git

if [ $# > 1 ] && [ -n "$2" ]; then
    ROOT_DIR_NAME=$2
fi

echo "REPO_NAME=${REPO_NAME}"
echo "ROOT_DIR_NAME=${ROOT_DIR_NAME}"

# Clone
git clone ${GIT_REPO_URL}

# Backup files(excpet .git)
mkdir ${REPO_NAME}_ROOT
mv -f ${REPO_NAME}/* ${REPO_NAME}_ROOT/
mv -f ${REPO_NAME}/.* ${REPO_NAME}_ROOT/
mv -f ${REPO_NAME}_ROOT/.git ${REPO_NAME}/

cd ${REPO_NAME}

# Add del commit
git add -f .

# Mv backup files to root dir
mv -f ../${REPO_NAME}_ROOT ${ROOT_DIR_NAME}

# Convert CRLF eol files to LF eol
find . -type f | xargs dos2unix

# Add backup files commit
git add -f ${ROOT_DIR_NAME}

git commit -m "add Root Dir"

# Push to origin forcely
git push origin HEAD --force

cd ..

unset REPO_NAME
unset ROOT_DIR_NAME
unset GIT_USER_NAME

# bug fix
rm -rf 1
