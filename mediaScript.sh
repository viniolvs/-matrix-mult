#!/bin/bash
gcc media.c -o media.x
DIRETORIO="DesktopO3"

echo "Tam Matriz,Mode o,Mode t,Mode v" >> $DIRETORIO/medias.csv
for ((i = 200; i <= 2000; i+=200))
    do
    echo -n "$i," >> $DIRETORIO/medias.csv
    ./media.x $DIRETORIO/o$i.csv >> $DIRETORIO/medias.csv
    ./media.x $DIRETORIO/t$i.csv >> $DIRETORIO/medias.csv
    ./media.x $DIRETORIO/v$i.csv >> $DIRETORIO/medias.csv
    echo >> $DIRETORIO/medias.csv
    done
