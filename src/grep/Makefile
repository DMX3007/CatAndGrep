CC = gcc
FLAGS = -g -Wall -Wextra -Werror

all: clean grep test2

grep: grep.o
	$(CC) $(FLAGS) $^ -o $@

grep.o: grep.c
	$(CC) -c $(FLAGS) $^ -o $@

test2:
	chmod +x script.sh
	./script.sh

clean:
	rm -f grep a.out grep.o grep_test.o test/test_grep