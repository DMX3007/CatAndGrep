#!/bin/bash

gcc test_grep.c -o test_grep

touch text
touch flags
touch pattern
touch myoutput.txt
touch stand_out.txt

i=1
c=0

func() {
    ./test_grep text flags pattern
    fl="$(cat flags)"
    pat="$(cat pattern)"
    echo "TEST#$i FLAGS:($fl) PATTERN:($pat)"
grep -$fl $pat text > stand_out.txt
./s21_grep -$fl $pat text > myoutput.txt
((++i))
diff stand_out.txt myoutput.txt
if [ $? = 0 ]
    then 
        echo SUCCESED
    else 
        echo FAILED FLAGS:$fl
        sleep 3s
fi
}

while [ $c -lt 20 ]
do
    func
    ((++c))
    sleep 1s
done