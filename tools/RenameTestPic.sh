#!/bin/bash
DEFAULTIFS=$IFS
IFS=$(echo -en "\n\b")
count=1
for file in *.jpg; do
    echo $file
    mv -n $file "test${count}.jpg"
    count=$((count+1))
done
unset file count
IFS=$DEFAULTIFS
