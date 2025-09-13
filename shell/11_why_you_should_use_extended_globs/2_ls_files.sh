#!/bin/bash
for file in `ls ./files/`; do
    if [[ $file =  @(IMG|DSC)* ]]; then
        echo $file
    fi
done