#!/bin/bash
gcc media.c -o media.x
DIRETORIO="Notebook"

echo "Tam Matriz,Mode o,Mode t,Mode vo, Mode vt" >> $DIRETORIO/medias.csv
for ((i = 200; i <= 2000; i+=200))
    do
    echo -n "$i," >> $DIRETORIO/medias.csv
    ./media.x $DIRETORIO/o$i.csv >> $DIRETORIO/medias.csv
    ./media.x $DIRETORIO/t$i.csv >> $DIRETORIO/medias.csv
    ./media.x $DIRETORIO/vo$i.csv >> $DIRETORIO/medias.csv
    ./media.x $DIRETORIO/vt$i.csv >> $DIRETORIO/medias.csv
    echo >> $DIRETORIO/medias.csv
    done
