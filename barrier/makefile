PROGS = barrier
CC = gcc
CFLAGS = -g -Wall -O2
objects = main.o barrier.o

all: $(objects)
	$(CC) $(CFLAGS) -o $(PROGS) $(objects) -lpthread


main.o: main.c barrier.h
	$(CC) $(CFLAGS) -c main.c

barrier.o: barrier.c barrier.h
	$(CC) $(CFLAGS) -c barrier.c

clean:
	-rm -f *~ *.o

purge: clean
	-rm -f $(PROGS)