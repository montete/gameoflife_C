# Mój plik makefile - wpisz 'make all' aby skompilowac caly program
CC = gcc -ggdb 
PNG = -lpng -L/usr/local/lib
all: main.o file.o gol.o topng.o
	$(CC) $(PNG) main.o file.o gol.o topng.o -Wall -o gameoflife
main.o: main.c
	$(CC) main.c -c -o main.o -Wall
file.o: file.c
	$(CC) file.c -c -o file.o -Wall
gol.o: gol.c
	$(CC) gol.c -c -o gol.o -Wall
topng.o: topng.c
	$(CC) topng.c -c -o topng.o -Wall
clean:
		rm *.o