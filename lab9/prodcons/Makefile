CC = gcc
CFLAGS = -Wall -g
LDLIBS = -lrt
TARGETS = prod cons

all: $(TARGETS)

prod: prod.c prodcons.h
	$(CC) $(CFLAGS) -o $@ prod.c $(LDLIBS)

cons: cons.c prodcons.h
	$(CC) $(CFLAGS) -o $@ cons.c $(LDLIBS)

clean:
	rm -f $(TARGETS)

re: clean all

.PHONY: all clean re
