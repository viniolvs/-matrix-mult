#!/bin/bash
gcc multmat.c -o multmat.x
for ((j = 200; j <= 2000; j+=200))
    do
    for ((i=0; i < 10; i++))
        do
        ./multmat.x $j $j $j $j o out >> noStructRun/o$j.csv
        ./multmat.x $j $j $j $j t out >> noStructRun/t$j.csv
        done
    done