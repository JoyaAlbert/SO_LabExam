CC = gcc
.SUFFIXES:

SRC = ejemplo1_create.c ejemplo1_read.c ejemplo1_write.c ejemplo2_init.c ejemplo2_sell.c
BIN = $(SRC:.c=)
OBJ = $(SRC:.c=.o)

all: $(BIN)

$(BIN): %: %.o
	$(CC) -o $@ $<

%.o: %.c
	$(CC) -c -o $@ $<

clean:
	rm -f $(BIN) $(OBJ)

.PHONY: all clean
