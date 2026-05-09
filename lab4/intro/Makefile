CC = gcc
CFLAGS = -Wall -Wextra

all: prueba prueba2

prueba: prueba.c
	$(CC) $(CFLAGS) -o prueba prueba.c

prueba2: prueba2.c
	$(CC) $(CFLAGS) -o prueba2 prueba2.c

clean:
	rm -f prueba prueba2

.PHONY: all clean