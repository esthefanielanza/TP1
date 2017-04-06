CC = gcc
CFLAGS = -g -O0 -Wall -Wextra -Werror -std=c99

all: main

main: main.o biblioteca.o quicksortExterno.o ordenacaoInterna.o
	$(CC) $(CFLAGS) main.o biblioteca.o quicksortExterno.o ordenacaoInterna.o -o main

main.o: main.c biblioteca.h quicksortExterno.h ordenacaoInterna.h
	$(CC) $(CFLAGS) -c main.c

biblioteca.o: biblioteca.c biblioteca.h
	$(CC) $(CFLAGS) -c biblioteca.c

quicksortExterno.o: quicksortExterno.c quicksortExterno.h
	$(CC) $(CFLAGS) -c quicksortExterno.c

ordenacaoInterna.o: ordenacaoInterna.c ordenacaoInterna.h
	$(CC) $(CFLAGS) -c ordenacaoInterna.c

clean:
	rm *.o main