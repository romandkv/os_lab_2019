CC=gcc
CFLAGS=-I.
all : mutex mod

mutex : mutex.o
	$(CC) -o mutex -lpthread mutex.o

mod : mod.o
	$(CC) -o mod -lpthread mod.o

mutex.o : 
	$(CC) -o mutex.o -c -std=c99 mutex.c $(CFLAGS)

mod.o :
	$(CC) -o mod.o -c -std=c99 mod.c $(CFLAGS)

clean : 
	rm mutex.o mutex mod.o mod