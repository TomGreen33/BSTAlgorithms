# Name: Thomas Green
# ID: 1048389
# Date: March 27 2021
# Assignment #: 4


CC = gcc
CFLAGS = -ansi -Wall -pedantic -Iincludes

default: main

main: main.o Q1.o Q2.o
	$(CC) Q1.o Q2.o main.o -o main -lm

main.o: main.c
		$(CC) $(CFLAGS) -c -o main.o main.c

Q1.o: Q1.c
	$(CC) $(CFLAGS) -c -o Q1.o Q1.c

Q2.o: Q2.c
	$(CC) $(CFLAGS) -c -o Q2.o Q2.c

clean:
	rm -f main main.o Q1.o Q2.o
