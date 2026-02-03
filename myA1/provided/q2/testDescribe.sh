#!/bin/bash
filePath=$1
printFiles() {
   if ["$filePath" != *.txt]; then
      echo "stderr"
      exit 1
   fi
   i=1
   while [$i -le $(wc -l "$filePath")]; do
      echo "$filePath" head -n "$i"
      ((i++))
   done
}
printFiles

