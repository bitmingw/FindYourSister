#!/bin/bash
count=1
for file in *.jpg; do
    mv -n $file "${count}.jpg"
    count=$((count+1))
done
unset file count
