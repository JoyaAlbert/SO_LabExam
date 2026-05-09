CC = gcc
CFLAGS = -Wall -Wextra -g

SRCS = race.c player.c
OBJS = $(SRCS:.c=.o)
TARGET = race

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c player.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
