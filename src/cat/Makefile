CC =  gcc
FLAGS = -g 

all: main

main: main.c
	$(CC) -c $(FLAGS) $^ -o $@.o
	$(CC) $(FLAGS) $@.o -o main
clean: 
	rm *.o main
rebuild:
	$(MAKE)clean
	$(MAKE)all