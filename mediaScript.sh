#!/bin/bash
gcc media.c -o media.x
for ((i = 200; i <= 2000; i+=200))
    do
    ./media.x thirdRun/o$i.txt >> thirdRun/medias_o.txt
    ./media.x thirdRun/t$i.txt >> thirdRun/medias_t.txt
    done