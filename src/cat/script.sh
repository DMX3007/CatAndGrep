#!/bin/bash

fl=$(cat flags.txt)

touch gen_output.txt
touch stand_out_cat.txt
touch myoutput.txt

gcc get_random.c -o get_r
./get_r

cat -$fl gen_output.txt > stand_out_cat.txt

gcc -g mycat.c -o mycat
./mycat -$fl gen_output.txt > myoutput.txt

diff stand_out_cat.txt myoutput.txt
if [[ $@ -ne 0 ]];then 
echo $fl
fi
