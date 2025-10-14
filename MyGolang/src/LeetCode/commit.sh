#!/usr/bin/bash

filename=$1

GITDIR='/root/MyWorkspace/MyGolang/src/LeetCode'

if [ ! -n "$filename" ];then
    /usr/bin/echo "filename param empty, exit!"
    exit 1
fi

if [ "${filename}" = "*.go" ]; then
    go_filename_prefix=${filename%.*}
else
    go_filename_prefix=${filename}
fi

go_filename="${go_filename_prefix}.go"

if [ ! -f ${go_filename} ]; then
    /usr/bin/echo "go filename ${go_filename} does not exist, exit!"
    exit 1
else
    /usr/bin/echo "go filename ${go_filename} exist"
fi

cd $GITDIR

/usr/bin/echo "git add ${go_filename}"
git add ${go_filename}

/usr/bin/echo "git commit -m \"coding(LeetCode): ${go_filename_prefix}\""
git commit -m "coding(LeetCode): ${go_filename_prefix}"

/usr/bin/echo 'git push'
git push

cd -
