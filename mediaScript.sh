#!/bin/bash
gcc media.c -o media.x
DIRETORIO="DesktopO3"
for ((i = 200; i <= 2000; i+=200))
    do
    ./media.x $DIRETORIO/o$i.csv >> $DIRETORIO/medias.csv
    done

for ((i = 200; i <= 2000; i+=200))
    do
    ./media.x $DIRETORIO/t$i.csv >> $DIRETORIO/medias.csv
    done

for ((i = 200; i <= 2000; i+=200))
    do
    ./media.x $DIRETORIO/v$i.csv >> $DIRETORIO/medias.csv
    done