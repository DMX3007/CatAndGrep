CC = gcc
FLAGS = -Werror -Wextra -Wall

all: s21_cat

s21_cat: s21_cat.o
	$(CC) $(FLAGS) $< -o $@

s21_cat.o: s21_cat.c
	$(CC) -c $(FLAGS) $< -o $@

check:
	cppcheck *.h *.c
	python3 ../../materials/linters/cpplint.py --extension=c *.c *.h
	CK_FORK=no leaks --atExit -- ./s21_cat

clean:
	rm -rf *.o
	