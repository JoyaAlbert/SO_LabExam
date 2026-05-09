CC = gcc
CFLAGS = -Wall -g

TARGETS = ejemplo1 ejemplo1_send ejemplo1_recv
OBJECTS = ejemplo1.o ejemplo1_send.o ejemplo1_recv.o

all: $(TARGETS)

ejemplo1.o: ejemplo1.c
	$(CC) $(CFLAGS) -c ejemplo1.c -o ejemplo1.o

ejemplo1_send.o: ejemplo1_send.c
	$(CC) $(CFLAGS) -c ejemplo1_send.c -o ejemplo1_send.o

ejemplo1_recv.o: ejemplo1_recv.c
	$(CC) $(CFLAGS) -c ejemplo1_recv.c -o ejemplo1_recv.o

ejemplo1: ejemplo1.o
	$(CC) -o ejemplo1 ejemplo1.o

ejemplo1_send: ejemplo1_send.o
	$(CC) -o ejemplo1_send ejemplo1_send.o

ejemplo1_recv: ejemplo1_recv.o
	$(CC) -o ejemplo1_recv ejemplo1_recv.o

clean:
	rm -f $(TARGETS) $(OBJECTS) myfifo

.PHONY: all clean
