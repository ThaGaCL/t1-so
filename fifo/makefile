PROGS = fifo
CC = gcc
CFLAGS = -g -Wall -O2
objects = main.o fifo.o

all: $(objects)
	$(CC) $(CFLAGS) -o $(PROGS) $(objects) -lpthread


main.o: main.c fifo.h
	$(CC) $(CFLAGS) -c main.c

fifo.o: fifo.c fifo.h
	$(CC) $(CFLAGS) -c fifo.c

clean:
	-rm -f *~ *.o

purge: clean
	-rm -f $(PROGS)