#!/bin/bash
gcc media.c -o media.x
for ((i = 200; i <= 2000; i+=200))
    do
    ./media.x noStructRun/o$i.csv >> noStructRun/medias.csv
    ./media.x noStructRun/t$i.csv >> noStructRun/medias.csv
    done