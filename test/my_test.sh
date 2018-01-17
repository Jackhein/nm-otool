#!/usr/bin/bash

FILE=a.out

FILESIZE=$(wc -c $FILE | awk '{print $1}')

echo $FILESIZE

for i in `seq 1 $FILESIZE`;
do
    echo "$i / $FILESIZE"
    # head -c$i $FILE > test_$i
    # tail -c$i $FILE > test_$i
    tail -c+$i $FILE > test_$i
    # ./ft_nm test_$i
    ./ft_otool test_$i
    rm test_$i
done
