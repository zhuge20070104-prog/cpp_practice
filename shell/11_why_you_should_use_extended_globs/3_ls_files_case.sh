#!/bin/bash

ALLRAW=0
NIKRAW=0
NIKSUP=0
CANRAW=0
CANSUP=0
CANJPG=0
OTHER=0
shopt -s extglob
for file in `ls ./files/`; do
    case "$file" in 
        @(IMG|DSC)*@(@(.CR2|.NEF).xmp|.NEF|.CR2)) (( ALLRAW++ ))
            ;;& 
        DSC*@(.NEF|.NEF.xmp))  (( NIKRAW++ )) 
            ;;&
        DSC*@(.NEF.xmp))  (( NIKSUP++ )) 
            ;;
        IMG*@(.CR2|.CR2.xmp))  (( CANRAW++ ))
            ;;& 
        IMG*@(.CR2.xmp))      (( CANSUP++ )) 
            ;;
        IMG*@(.JPG|.jpg))      (( CANJPG++ ))
            ;;
        *)                    ((  OTHER++  )) ;;
    esac
done

echo "ALLRAW: ${ALLRAW}"
echo "NIKRAW: ${NIKRAW}"
echo "NIKSUP: ${NIKSUP}"
echo "CANRAW: ${CANRAW}"
echo "CANSUP: ${CANSUP}"
echo "CANJPG: ${CANJPG}"
echo "OTHER: ${OTHER}"