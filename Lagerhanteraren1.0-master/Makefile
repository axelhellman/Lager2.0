CC=gcc
FLAGS=-Wall -std=c11 -ggdb


all: main

#Build main
main: main.c
	$(CC) $(FLAGS) main.c -o main


#Run the program
run: main
	@echo "Running the prgram"
	@./main

clean:
	rm -f main
	rm -f *.o
	rm -rf *.dSYM
# ^$ alla dependencies

.PHONY: clean main run all
