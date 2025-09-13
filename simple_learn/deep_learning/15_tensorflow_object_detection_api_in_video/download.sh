#!/bin/bash

if [[ "$#" -lt 1 ]]; then 
    echo "Usage: ./download.sh {You tube file link}"
    exit 1
fi

./yt-dlp "${1}"  --proxy http://10.224.0.110:3128 --yes-playlist -f best
