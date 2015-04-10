CC=gcc
BIN=main
CFLAGS=-std=c99 -O3 -Wall -pedantic

all: main 

main: main.o map.o
	$(CC) $(CFLAGS) main.o map.o -o $(BIN)

main.o: map.h main.c
	$(CC) $(CFLAGS) main.c -c

map.o: map.h map.c
	$(CC) $(CFLAGS) map.c -c

clean: ; rm -f *.o $(BIN)

test: main; @./main # run tests

.PHONY: test
