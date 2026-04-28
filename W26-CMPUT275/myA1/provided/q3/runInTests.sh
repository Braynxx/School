#!/bin/bash
commandArg=$1
stemFiles=$(cat "$2")
while read -r files; do
    for file in $files; do
        if diff -q <("$commandArg" < "$file".in) <(cat "$file".out) >/dev/null; then
            printf "Test $file passed\n"
        else
            printf "Test $file failed\n"
            printf "Expected output:\n"
            printf "$(cat "$file".out)\n"
            printf "Actual output:\n"
            printf "$("$commandArg" < "$file".in)\n"
        fi
    done
done <<< "$stemFiles"