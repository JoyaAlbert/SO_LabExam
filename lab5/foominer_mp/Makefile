CC = cc
CFLAGS = -Wall -g
LDLIBS_CRYPTO = -lcrypto

TARGETS = fooblockcheck foominer foominer_mp

all: $(TARGETS)

fooblockcheck.o: fooblockcheck.c foominerlib.h
	$(CC) $(CFLAGS) -c fooblockcheck.c -o fooblockcheck.o

foominer.o: foominer.c foominerlib.h
	$(CC) $(CFLAGS) -c foominer.c -o foominer.o

foominerlib.o: foominerlib.c foominerlib.h
	$(CC) $(CFLAGS) -c foominerlib.c -o foominerlib.o

foominer_mp.o: foominer_mp.c foominer_mp.h
	$(CC) $(CFLAGS) -c foominer_mp.c -o foominer_mp.o

fooblockcheck: fooblockcheck.o foominerlib.o
	$(CC) -o $@ fooblockcheck.o foominerlib.o $(LDLIBS_CRYPTO)

foominer: foominer.o foominerlib.o
	$(CC) -o $@ foominer.o foominerlib.o $(LDLIBS_CRYPTO)

foominer_mp: foominer_mp.o
	$(CC) -o $@ foominer_mp.o

clean:
	rm -f $(TARGETS) *.o *.solved

re: clean all

.PHONY: all clean re
