CC = gcc
CFLAGS = -Wall -g

TARGETS = tickets_init tickets_sell
OBJECTS = tickets_init.o tickets_sell.o

all: $(TARGETS)

tickets_init.o: tickets_init.c tickets.h
	$(CC) $(CFLAGS) -c tickets_init.c -o tickets_init.o

tickets_sell.o: tickets_sell.c tickets.h
	$(CC) $(CFLAGS) -c tickets_sell.c -o tickets_sell.o

tickets_init: tickets_init.o
	$(CC) -o tickets_init tickets_init.o

tickets_sell: tickets_sell.o
	$(CC) -o tickets_sell tickets_sell.o

clean:
	rm -f $(TARGETS) $(OBJECTS)

.PHONY: all clean
