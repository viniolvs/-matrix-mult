#!/bin/bash
for ((j = 200; j <= 2000; j+=200))
    do
    for ((i=0; i < 10; i++))
        do
        ./multmat.x $j $j $j $j o >> secondRun/o$j.txt
        ./multmat.x $j $j $j $j t >> secondRun/t$j.txt
        done
    done