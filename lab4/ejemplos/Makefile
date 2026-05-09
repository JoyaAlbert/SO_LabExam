CC = gcc
CFLAGS =  -Wextra -g

SRCS = ejemplo1.c ejemplo1bis.c ejemplo2.c ejemplo3.c ejemplo4.c ejemplo4b.c ejemplo5.c ejemplo6.c ejemplo6b.c
OBJS = $(SRCS:.c=.o)
BINS = $(SRCS:.c=)

.PHONY: all clean

all: $(OBJS) $(BINS)

%: %.o
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BINS)
