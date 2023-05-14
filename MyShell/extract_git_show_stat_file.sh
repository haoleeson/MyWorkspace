#!/bin/bash

###########################################
# extract git show stat file of commit id
# usage: extract_git_show_stat_file.sh $HOME/1 123456
###########################################

filepath=$1
commit_id=$2
COLUMNS=300
GIT_SHOW_HEAD_RM_LINE=6

echo "input file path: $filepath"
echo "input commit_id: $commit_id"

if [ ! -n "$filepath" ]; then
    echo "return failed: you need input a file path"
    exit 1
fi

if [ ! -n "$commit_id" ]; then
    echo "return failed: you need input a commit_id"
    exit 1
fi

git show --stat=$COLUMNS $commit_id | tail -n +$GIT_SHOW_HEAD_RM_LINE | fgrep -v ' changed,' > $filepath

if [ ! -f $filepath ]; then
    echo "return failed: git show --stat failed, please check commit_id and you are in repo DIR"
    exit 1
fi

function fuzzy_type(){
    if [ $# -ne 2 ]; then
        echo $0
        echo "usage: fuzzy_type ‹file path> ‹file type>"
        echo "   eg: fuzzy_type /root/Downloads/1 json"
        return 1
    fi

    local f=$1
    local type=$2

    sed -i '' -E "s/[-\._0-9a-zA-Z]+\\.$type/*.$type/g" $f
    return 0
}

function ignore_type(){
    if [ $# -ne 2 ]; then
        echo $@
        echo "usage: fuzzy_type ‹file path> ‹file type>"
        echo "   eg: fuzzy_type /root/Downloads/1 json"
        return 1
    fi


    local f=$1
    local type=$2

    # sed -i '' -E "s/[-\._0-9a-zA-Z]+\\.$type/*.$type/g" $f
    sed -i '' "/\\.$type\$/d" $f
    return 0
}
 
# delete |    22 +
sed -i '' -E 's/ +\|[ 0-9\+-]+$//g' $filepath

# delete space
sed -i '' 's/ //g' $filepath

# delete Bin3779->0bytes
sed -i '' -E 's/\|Bin[0-9]+->[0-9]+bytes$//g' $filepath

# keep file type, ignore file name
fuzzy_type $filepath 'json'
fuzzy_type $filepath 'pm'
fuzzy_type $filepath 'cpp'
fuzzy_type $filepath 'c'
fuzzy_type $filepath 'h'
fuzzy_type $filepath 'tt'
fuzzy_type $filepath 'p4'
fuzzy_type $filepath 'py'
fuzzy_type $filepath 'html'
fuzzy_type $filepath 'js'
fuzzy_type $filepath 'xml'

# ignore file type
ignore_type $filepath 'md'
ignore_type $filepath 'css'
ignore_type $filepath 'docx'
ignore_type $filepath 'html'
ignore_type $filepath 'o'
ignore_type $filepath 'png'
ignore_type $filepath 'pm'
ignore_type $filepath 'vsdx'
ignore_type $filepath 'js'
ignore_type $filepath 'svg'
ignore_type $filepath 'gv'
ignore_type $filepath 'xslt'
ignore_type $filepath 'xsd'
#ignore_type $filepath 'json'
#ignore_type $filepath 'md'
#ignore_type $filepath 'README'

cat $filepath | sort | uniq > /tmp/1
cat /tmp/1 > $filepath
