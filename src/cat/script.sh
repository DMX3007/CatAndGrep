#!/bin/bash

fl=$(cat flags.txt)

cat -$fl gen_output.txt > stand_out_cat.txt


gcc 1s21_cat.c -o mycat
./mycat -$fl gen_output.txt > myoutput.txt

gcc str_cmp.c -o cmp && ./cmp
