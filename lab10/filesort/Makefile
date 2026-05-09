CC = gcc
CFLAGS = -g

OBJS = showgrades.o filesort.o gradesort_std.o gradesort_mmap.o
BINS = showgrades filesort_std filesort_mmap

.PHONY: all clean datos

all: $(BINS)

showgrades: showgrades.o
	$(CC) -o $@ $^

filesort_std: filesort.o gradesort_std.o
	$(CC) -o $@ $^

filesort_mmap: filesort.o gradesort_mmap.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

datos:
	tar -xzf datos.tgz
cdata:
	rm -f *.bin
clean:
	rm -f $(OBJS) $(BINS) datos.bin datosord.bin
