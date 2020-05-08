#!/bin/bash
gcc -c $1 $2;
IFS='/' read -ra dirs <<< "$1/$2";
declare -a files;
for i in "${dirs[@]}"
do
  if [[ $i =~ ".c" ]]; then
      files=("$i" "${files[@]}")
  fi
done
declare -a file_names;
for i in "${files[@]}"
do
  i=${i::${#i}-2};
  file_names=("$i" "${file_names[@]}")
done

gcc -o ${file_names[0]} "${file_names[0]}.o" "${file_names[1]}.o";
./${file_names[0]};