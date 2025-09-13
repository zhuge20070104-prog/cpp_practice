#!/bin/bash
for line in $(cat ./sales.csv); do
    if [[ $line =~ .*[Vv]isa.* ]]; then
        if [[ $line =~ [0-9]{16} ]]; then
            echo ${BASH_REMATCH[0]} | sed -E 's/([0-9]{4})([0-9]{4})([0-9]{4})([0-9]{4})/\1-\2-\3-\4/'
        fi
    fi
done