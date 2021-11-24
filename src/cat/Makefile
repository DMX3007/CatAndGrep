CC =  gcc
FLAGS = -g 

all: main is_it

main: main.o is_it.o
	$(CC) $(FLAGS) $^ -o $@
main.o: main.c
	$(CC) -c $(FLAGS) $< -o $@.o
is_it.o: is_it.c
	$(CC) -c $(FLAGS) $< -o $@.o
clean: 
	rm -rf *.o main *.dSYM testing cat a.out
rebuild:
	$(MAKE)clean
	$(MAKE)all