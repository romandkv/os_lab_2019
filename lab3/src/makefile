CC=gcc
CFLAGS=-I.

all: sequential_min_max parallel_min_max

5z: 
	$(CC) -o 5z  5z.c
sequential_min_max : s_min_max utils.o find_min_max.o utils.h find_min_max.h
	$(CC) -o sequential_min_max find_min_max.o utils.o sequential_min_max.o $(CFLAGS) -std=c99

p_min_max: utils.h
	$(CC) -o parallel_min_max.o -c parallel_min_max.c $(CFLAGS) -std=c99

parallel_min_max : p_min_max utils.o find_min_max.o utils.h find_min_max.h
	$(CC) -o parallel_min_max utils.o find_min_max.o parallel_min_max.o $(CFLAGS) -std=c99

s_min_max: utils.h
	$(CC) -o sequential_min_max -c sequential_min_max.c $(CFLAGS) -std=c99

utils.o : utils.h
	$(CC) -o utils.o -c utils.c $(CFLAGS) -std=c99

find_min_max.o : utils.h find_min_max.h
	$(CC) -o find_min_max.o -c find_min_max.c $(CFLAGS) -std=c99

clean :
	rm utils.o find_min_max.o sequential_min_max parallel_min_max
