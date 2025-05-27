#!/usr/bin/env bash

sum() {
    local total=0 status val
    for val in "$@"; do
        total=$(expr "$total" + "$val" 2>/dev/null)
        status=$?
        [ $status -eq 2 ] && { echo 0; return; }
    done
    echo "$total"
}

read -r line1
read -r line2

sum1=$(sum $line1)
sum2=$(sum $line2)

[ "$sum1" -eq "$sum2" ] && echo "Equal" || echo "Not equal"