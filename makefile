PROGS = t1
CC = gcc
CFLAGS = -g -Wall -O2
objects = main.o fifo.o barrier.o

all: $(objects)
	$(CC) $(CFLAGS) -o $(PROGS) $(objects) -lpthread

main.o: main.c fifo/fifo.h barrier/barrier.h
	$(CC) $(CFLAGS) -c main.c

fifo.o: fifo/fifo.c fifo/fifo.h
	$(CC) $(CFLAGS) -c fifo/fifo.c

barrier.o: barrier/barrier.c barrier/barrier.h
	$(CC) $(CFLAGS) -c barrier/barrier.c

clean:
	-rm -f *~ *.o

purge: clean
	-rm -f $(PROGS)