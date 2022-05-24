#!/bin/bash
#read file from commanded filename and print line by line
line_num=1
cat $1 | while read line
do
    echo $line_num $line
    line_num=`expr $line_num + 1`
done
