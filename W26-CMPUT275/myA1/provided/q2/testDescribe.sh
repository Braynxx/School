#!/bin/bash
filePath=$1
printFiles() {
   if [[ "$filePath" != *.txt ]]; then
      echo "Error: file must be of *.txt" >&2
      exit 1
   fi

   fileText="$(cat "$filePath")"
   while read -r innerFile; do
      for word in $innerFile; do
         echo "Description for test case $word:"
         if [ -f "$word".desc ]; then
            echo "$(cat "$word".desc)"
         else
            echo "$word No test description"
         fi
         done
   done <<< "$fileText"
}

printFiles

