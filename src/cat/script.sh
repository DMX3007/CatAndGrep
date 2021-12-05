#!/bin/bash

fl=$(cat flags.txt)

gcc random_test.c -o random
./random

cat -$fl gen_output.txt > stand_out_cat.txt

gcc -g s21_cat.c -o mycat
./mycat -$fl gen_output.txt > myoutput.txt

gcc str_cmp.c -o cmp && ./cmp
