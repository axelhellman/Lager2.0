CC=gcc
FLAGS= -Wall -std=c11 -ggdb

all: warehouse

warehouse: main.c menu.o IO.o smallfunc.o tree.o
	$(CC) $(FLAGS) main.c menu.o IO.o smallfunc.o tree.o -o main

menu.o: menu.c menu.h #IO.o smallfunc.o tree.o
	$(CC) $(FLAGS) menu.c -c

IO.o: IO.c IO.h #smallfunc.o tree.o
	$(CC) $(FLAGS) IO.c -c

smallfunc.o: smallfunc.c smallfunc.h #tree.o
	$(CC) $(FLAGS) smallfunc.c -c

#database.o: database.c database.h
#	$(CC) $(FLAGS) database.c -c

tree.o: tree.c tree.h
	$(CC) $(FLAGS) tree.c -c


run: warehouse #run är beroende av warehouse
	echo "Running program, woho!"
	./main

clean:
	rm -f main #-f betyder att om filen inte existerar händer ingenting
	rm *.o
	rm -r *.dSYM
