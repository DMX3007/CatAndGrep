CC = gcc
FLAGS = -Werror -Wextra -Wall

all: s21_cat

s21_cat: s21_cat.o
	$(CC) $(FLAGS) $< -o $@

s21_cat.o: cat.c
	$(CC) -c $(FLAGS) $< -o $@

clean:
	rm -rf *.o
