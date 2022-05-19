#!/usr/bin/env bash
if [[ -e $1 ]]; then
   rm $1
fi    
g++ main.c -o programs
./programs $1 $2
cat $1