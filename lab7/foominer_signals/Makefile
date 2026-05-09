CC = cc
CFLAGS = -g
LDLIBS = -lcrypto

NAME1 = fooblockcheck
NAME2 = foominer

all: $(NAME1) $(NAME2)

fooblockcheck.o: fooblockcheck.c foominerlib.h
	$(CC) $(CFLAGS) -c fooblockcheck.c -o fooblockcheck.o

foominer.o: foominer.c foominerlib.h
	$(CC) $(CFLAGS) -c foominer.c -o foominer.o

foominerlib.o: foominerlib.c foominerlib.h
	$(CC) $(CFLAGS) -c foominerlib.c -o foominerlib.o

$(NAME1): fooblockcheck.o foominerlib.o
	$(CC) -o $(NAME1) fooblockcheck.o foominerlib.o $(LDLIBS)

$(NAME2): foominer.o foominerlib.o
	$(CC) -o $(NAME2) foominer.o foominerlib.o $(LDLIBS)

clean:
	rm -f $(NAME1) $(NAME2) *.o *.solved


re: clean all

.PHONY: all clean  re
