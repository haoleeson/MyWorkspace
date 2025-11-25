#!/usr/bin/bash

filename=$1

GIT_DIR='/root/MyWorkspace/MyGolang/src/LeetCode'
GIT_MSG_PRE='Recoding(LeetCode):'

if [ ! -n "$filename" ];then
    /usr/bin/echo -e "filename param empty, exit!\n"
    exit 1
fi

if [[ "${filename##*.}" == "go" ]]; then
    go_filename_prefix=${filename%.*}
else
    go_filename_prefix=${filename}
fi

go_filename="${go_filename_prefix}.go"

if [ ! -f ${go_filename} ]; then
    /usr/bin/echo -e "go filename ${go_filename} does not exist, exit!\n"
    exit 1
else
    /usr/bin/echo -e "go filename ${go_filename} exist\n"
fi

cd $GIT_DIR

/usr/bin/echo -e "git add ${go_filename}\n"
git add ${go_filename}

/usr/bin/echo -e "git commit -m \"${GIT_MSG_PRE} ${go_filename_prefix}\"\n"
git commit -m "${GIT_MSG_PRE} ${go_filename_prefix}"

/usr/bin/echo -e 'git push\n'
git push

cd -
