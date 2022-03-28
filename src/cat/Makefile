CC = gcc
FLAGS = -Werror -Wextra -Wall

all: mycat test

mycat: mycat.o
	$(CC) $(FLAGS) $< -o $@

mycat.o: mycat.c
	$(CC) -c $(FLAGS) $< -o $@
check:
	cppcheck *.h *.c
test:
	./script.sh
clean:
	rm -rf *.o
	
