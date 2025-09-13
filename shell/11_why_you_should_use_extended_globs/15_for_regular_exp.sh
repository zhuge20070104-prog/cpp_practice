#!/bin/bash 

echo  "" > ./result_regular_if.txt
for file in `ls ./tars/`; do
    if [[ $file =~ Backup.*\.((tar|arc).gz|tgz) ]]; then 
        echo $file >> ./result_regular_if.txt
    fi
done