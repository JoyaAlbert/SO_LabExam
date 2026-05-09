CC = cc
CFLAGS = -Wall -g
LDLIBS = -lcrypto

TARGETS = fooblockcheck foominer

all: $(TARGETS)

fooblockcheck.o: fooblockcheck.c foominerlib.h
	$(CC) $(CFLAGS) -c fooblockcheck.c -o fooblockcheck.o

foominer.o: foominer.c foominerlib.h
	$(CC) $(CFLAGS) -c foominer.c -o foominer.o

foominerlib.o: foominerlib.c foominerlib.h
	$(CC) $(CFLAGS) -c foominerlib.c -o foominerlib.o

fooblockcheck: fooblockcheck.o foominerlib.o
	$(CC) -o $@ fooblockcheck.o foominerlib.o $(LDLIBS)

foominer: foominer.o foominerlib.o
	$(CC) -o $@ foominer.o foominerlib.o $(LDLIBS)

clean:
	rm -f $(TARGETS) *.o *.solved

re: clean all

.PHONY: all clean re
