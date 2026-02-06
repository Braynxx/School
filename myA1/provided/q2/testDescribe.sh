#!/bin/bash
filePath=$1
printFiles() {
   if [ "$filePath" != *.txt ]; then
      echo "Error: file must be of *.txt" >&2
      exit 1
   fi

   i=1
   fileText="$(cat "$filePath")"
   while IFS= read -r innerFile <<< "$fileText"; do
      echo "Description for test case $innerFile:"
      echo "$(cat "$innerFile")"
      ((i++))
      if [ "$i" -eq 5]; then
         break
      fi
   done <<< "$fileText"
}

printFiles

