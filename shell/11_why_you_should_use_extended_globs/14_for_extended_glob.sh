#!/bin/bash 

echo  "" > ./result_extended_glob.txt
shopt -s extglob
for file in  ./tars/Backup*.@(@(tar|arc).gz|tgz); do
    echo $file >> ./result_extended_glob.txt
done