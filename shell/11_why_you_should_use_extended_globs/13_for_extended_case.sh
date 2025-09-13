# Extended glob for case
#!/bin/bash

echo  "" > ./result_extended_case.txt

shopt -s extglob

for file in `ls ./tars/`; do
    case $file in
        Backup*.@(@(tar|arc).gz|tgz))  
            echo $file >> ./result_extended_case.txt ;;
    esac
done