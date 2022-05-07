#!/bin/bash
for ((i = 200; i <= 2000; i+=200))
    do
    ./media.x firstRunDesktop/o$i.txt > firstRunDesktop/media_o$i.txt
    ./media.x firstRunDesktop/t$i.txt > firstRunDesktop/media_t$i.txt
    done