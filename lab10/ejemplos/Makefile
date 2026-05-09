CC = gcc
CFLAGS = -Wextra -g

SRCS = ejemplo1.c ejemplo1_uchar.c ejemplo2.c ejemplo1_add.c ejemplo2_uchar.c ejemplo2_readall.c ejemplo2_mmap.c
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
