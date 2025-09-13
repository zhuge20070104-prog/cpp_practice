#!/bin/bash

shopt -s extglob

cd files
# 2. 使用Glob做Pattern Matching


XGLOB='@(Archive|Backup)-[0-9][0-9][0-9][0-9]-[0-9][0-9]-@([0-9]|[0-9][0-9])@(@(.bak|.tar)?(.bz2|.gz|.xz)|.tgz)'

for FILE in *; do
    if [[ $FILE = $XGLOB ]]; then
        echo "$FILE matches the extended glob"
    fi
done