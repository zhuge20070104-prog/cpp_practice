#!/bin/bash

count=`ls | grep -v "printer.sh" | wc -l`
batch=`echo "sclae=2; $count/20+1" | bc`
echo "Total files count: $count"
echo "Total batch count: $batch"

times=20
for ((i=0; i<$batch; i++))
do   
    start=`expr $i \* $times`
    end_index=`expr $i + 1`

    end_batch=`expr $batch - 1`
    if [ $i -ne  $end_batch ]; then
        end=`expr $end_index \* $times`
    else
        end=$count
    fi 

    start=`expr $start + 1`
    
    echo "$start"
    echo "$end"
    
   echo  "ls | grep -v \"printer.sh\" | sed -n \"${start},${end}p\" | xargs -I {} /usr/bin/lp -d HP_DeskJet_2700_series_C6B7DE_ -o landscape -o fit-to-page -o media=A4 ./{}" > printer_$i.sh
done