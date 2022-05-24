#!/bin/bash
#compare two number from command input
if [ $1 -gt $2 ]
then
    echo "$1 is bigger than $2";
elif [ $1 -eq $2 ]
then
    echo "$1 is equal to $2";
elif [ $1 -lt $2 ]
then
    echo "$1 is smaller than $2";
fi
