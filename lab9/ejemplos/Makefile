CC = gcc
CFLAGS =
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
BIN = $(SRC:.c=)

all: $(BIN)

%: %.o
	$(CC) $(CFLAGS) $< -o $@

%.o: %.c ejemplo1.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(BIN)

re: fclean all

.PHONY: all clean fclean re