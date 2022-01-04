#!/bin/bash

fl=$(cat test/flags)
pat=$(cat test/pattern)

cd test
gcc test_grep.c -o test_grep
./test_grep text flags pattern

cd ..

grep -$fl \'$pat\' test/text > stand_out.txt
./grep -$fl \'$pat\' test/text > myoutput.txt

diff stand_out.txt myoutput.txt