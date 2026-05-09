CC = gcc
CFLAGS = -Wall -g
TARGETS = prod cons

all: $(TARGETS)

prod: prod.c prodcons.h
	$(CC) $(CFLAGS) -o $@ prod.c

cons: cons.c prodcons.h
	$(CC) $(CFLAGS) -o $@ cons.c

clean:
	rm -f $(TARGETS)

re: clean all

.PHONY: all clean re
