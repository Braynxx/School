#!/bin/bash
commandArg=$1
stemFiles=$(cat "$2")
while read -r files; do
    for file in $files; do
        if [ -f ""$file".args" ]; then
            fileArgs=$(cat "$file".args)
            input=$("$commandArg" $fileArgs < "$file".in)
        else
            input=$("$commandArg" < "$file".in)
        fi
        output=$(cat "$file".out)
        if diff -q <(printf '%s' "$input") <(printf '%s' "$output") >/dev/null; then
            printf "Test $file passed\n"
        else
            printf "Test $file failed\n"
            printf "Expected output:\n"
            printf '%s\n' "$output"
            printf "Actual output:\n"
            printf '%s\n' "$input"
        fi
    done
done <<< "$stemFiles"
