#!/bin/bash

set -e

for i in ../examples/*
do
    if [ -f "$i/platformio.ini" ]
    then
        pio run -d "$i" -s
    fi
done
