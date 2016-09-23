CC=gcc
CFLAGS=-g -std=c89 -c

all: lab1

lab1: main.o prog_lab.o
	$(CC) main.o prog_lab.o -o lab1

prog_lab.o: prog_lab.c
	$(CC) $(CFLAGS) prog_lab.c

clean:
	rm prog_lab.o lab1
