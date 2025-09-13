#!/bin/bash 

echo  "" > ./result_extended_if.txt
for file in `ls ./tars/`; do
    if [[ $file = Backup*.@(@(tar|arc).gz|tgz) ]]; then 
        echo $file >> ./result_extended_if.txt
    fi
done