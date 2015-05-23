#!/bin/bash

if (( $# == 1 ))
then
    make clean && make
fi

RED='\033[0;31m'
NC='\033[0m'

#input="test_io/test_in.txt" # 6M
input="test_io/s_6_first100000_1.fastq" # 64M
#input="test_io/s_6.first400000_2.fastq" # 273M
output="test_io/my.out"

#time bin/main test_io/s_6_first100000_1.fastq test_io/my.out
time bin/main "$input" "$output"

given=`wc -c "$input" | grep -oP "^[^[:space:]]*"`
comp=`wc -c "$output" | grep -oP "^[^[:space:]]*"`

x=$(bc <<< "scale=3;$given/$comp")

s="_decompressed"
printf "files $RED$input$NC and $RED$input$s$NC diff:\n"
printf "===========================================\n"
diff "$input" "$input$s"
printf "===========================================\n"
printf "compressed file is $x times less then source file\n"
