#!/bin/bash
# gcc -Wall -O3 multmat.c -o multmat.x
gcc -Wall multmat.c -o multmat.x
DIRETORIO="Notebook"
for ((j = 200; j <= 2000; j+=200))
    do
    for ((i=0; i < 10; i++))
        do
        ./multmat.x $j $j $j $j o out >> $DIRETORIO/o$j.csv
        ./multmat.x $j $j $j $j t out >> $DIRETORIO/t$j.csv
        ./multmat.x $j $j $j $j v out >> $DIRETORIO/v$j.csv
        done
    done
