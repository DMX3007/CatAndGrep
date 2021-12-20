CC = gcc
FLAGS = -Wall -Wextra -Werror

all: grep

grep: grep.o
	$(CC) $(FLAGS) $^ -o $@

grep.o: grep.c
	$(CC) -c $(FLAGS) $^ -o $@

testing: testing.o
	$(CC) -c $(FLAGS) $^ -o $@

testing.o: testing.c
	$(CC) -c $(FLAGS) $^ -o $@

test: grep_test.o
	$(CC) -g $^ -o $@ -D T1

grep_test.o: grep.c
	$(CC) -g -c $^ -o $@ -D T1

clean:
	rm -rf grep a.out test grep.o grep_test.o