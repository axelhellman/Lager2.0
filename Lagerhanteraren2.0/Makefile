CC=gcc
FLAGS= -Wall -std=c11 -ggdb

all: warehouse

warehouse: main.c menu.o IO.o smallfunc.o tree.o list.o
	$(CC) $(FLAGS) main.c menu.o IO.o smallfunc.o tree.o list.o -o warehouse

menu.o: menu.c menu.h #IO.o smallfunc.o tree.o
	$(CC) $(FLAGS) menu.c -c

IO.o: IO.c IO.h #smallfunc.o tree.o
	$(CC) $(FLAGS) IO.c -c

smallfunc.o: smallfunc.c smallfunc.h #tree.o
	$(CC) $(FLAGS) smallfunc.c -c

tree.o: tree.c tree.h list.o
	$(CC) $(FLAGS) tree.c -c

list.o: list.c list.h
	$(CC) $(FLAGS) list.c -c

run: warehouse #run är beroende av warehouse
	echo "Running program, woho!"
	./warehouse

clean:
	rm -f main #-f betyder att om filen inte existerar händer ingenting
	rm *.o
	rm -r *.dSYM
