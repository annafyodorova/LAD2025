#!/bin/bash

if [ -n "$1" ]; then
    delay=$1
else
    delay=0.001
fi

mapfile -t lines
tput clear

positions=()
for ((row = 0; row < ${#lines[@]}; row++)); do
    len=${#lines[row]}
    for ((col = 0; col < len; col++)); do
        positions+=("$row,$col")
    done
done

positions=($(shuf -e "${positions[@]}"))

for pos in "${positions[@]}"; do
    row=${pos%,*}
    col=${pos#*,}
    symbol="${lines[row]:$col:1}"
    tput cup "$row" "$col"
    printf '%s' "$symbol"
    sleep "$delay"
done

tput cup ${#lines[@]} 0