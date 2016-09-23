CC=gcc
CFLAGS=-g -std=c89 -c

all: prog

prog: main.o prog.o
	$(CC) main.o prog.o -o prog

prog.o: prog.c
	$(CC) $(CFLAGS) prog.c

clean:
	rm prog.o prog
