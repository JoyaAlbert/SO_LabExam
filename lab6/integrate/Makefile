CC = gcc
CFLAGS = -g
LDLIBS = -lm
PTHREAD_LDFLAGS = -pthread

all: test picalc_1 picalc_2 picalc_mt_1 picalc_mt_2

test.o: test.c integrate.h
	$(CC) $(CFLAGS) -c test.c -o test.o

picalc.o: picalc.c integrate.h f.h
	$(CC) $(CFLAGS) -c picalc.c -o picalc.o

picalc_mt.o: picalc_mt.c integrate_mt.h
	$(CC) $(CFLAGS) -c picalc_mt.c -o picalc_mt.o

integrate.o: integrate.c integrate.h
	$(CC) $(CFLAGS) -c integrate.c -o integrate.o

integrate_mt.o: integrate_mt.c integrate_mt.h integrate.h
	$(CC) $(CFLAGS) -c integrate_mt.c -o integrate_mt.o

f1.o: f1.c f.h
	$(CC) $(CFLAGS) -c f1.c -o f1.o

f2.o: f2.c f.h
	$(CC) $(CFLAGS) -c f2.c -o f2.o

test: test.o integrate.o
	$(CC) -o test test.o integrate.o $(LDLIBS)

picalc_1: picalc.o integrate.o f1.o
	$(CC) -o picalc_1 picalc.o integrate.o f1.o $(LDLIBS)

picalc_2: picalc.o integrate.o f2.o
	$(CC) -o picalc_2 picalc.o integrate.o f2.o $(LDLIBS)

picalc_mt_1: picalc_mt.o integrate_mt.o integrate.o f1.o
	$(CC) -o picalc_mt_1 picalc_mt.o integrate_mt.o integrate.o f1.o $(LDLIBS) $(PTHREAD_LDFLAGS)

picalc_mt_2: picalc_mt.o integrate_mt.o integrate.o f2.o
	$(CC) -o picalc_mt_2 picalc_mt.o integrate_mt.o integrate.o f2.o $(LDLIBS) $(PTHREAD_LDFLAGS)

clean:
	rm -f test picalc_1 picalc_2 picalc_mt_1 picalc_mt_2 *.o

.PHONY: all clean
