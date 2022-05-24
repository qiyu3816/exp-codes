#!/bin/bash
#change all files with $1 suffix into $2 suffix
old=$1
new=$2
dir=$(eval pwd)
for file in $(ls $dir | grep .$old)
    do
    name=$(ls $file | cut -d. -f1)
    mv $file ${name}$new
    done
echo "change done!"

