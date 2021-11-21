#!/bin/bash

function convert(){
        keyword=${1//\\/\\\\\\\\}
        keyword=${keyword//\./\\.}
        keyword=${keyword//\*/\\\\*}
        keyword=${keyword//\&/\\\\&}
        keyword=${keyword//\$/\\\\$}
        keyword=${keyword//\+/\\\\+}
        keyword=${keyword//\=/\\\\=}
        keyword=${keyword//\^/\\\\^}
        keyword=${keyword//\%/\\\\%}
        keyword=${keyword//\!/\\\\!}
        keyword=${keyword//\@/\\\\@}
        keyword=${keyword//\#/\\\\#}
        keyword=${keyword//\[/\\\\[}
        keyword=${keyword//\]/\\\\]}
        keyword=${keyword//\-/\\\\-}
        keyword=${keyword//\ /\\ }
#       keyword=${keyword//\?/\\\\?}    ?号不能转义.否则要报错
        keyword=${keyword//\"/\\\"}
        echo $keyword
}

echo "input: $1"
convert $1