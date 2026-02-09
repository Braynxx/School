#!/bin/bash
commandArg=$1
stemFiles=$(cat "$2")
while read -r files; do
    for file in $files; do
        fileArgs=$(cat "$file".args)
        input=$("$commandArg" $fileArgs < "$file".in)
        output=$(cat "$file".out)
        if diff -q <(printf "$input") <(printf "$output") >/dev/null; then
            printf "Test $file passed\n"
        else
            printf "Test $file failed\n"
            printf "Expected output:\n"
            printf "$output\n"
            printf "Actual output:\n"
            printf "$input\n"
        fi
    done
done <<< "$stemFiles"