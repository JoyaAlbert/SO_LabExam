CC = gcc
CFLAGS = -Wall -g

TARGETS = picalc_dispatcher picalc_worker picalc_gatherer picalc_fifos
OBJECTS = picalc_dispatcher.o picalc_worker.o picalc_gatherer.o picalc_fifos.o picalc_agents.o integrate.o f1.o

.PHONY: all clean run_fifos

all: $(TARGETS)

picalc_dispatcher.o: picalc_dispatcher.c picalc_pipes.h
	$(CC) $(CFLAGS) -c picalc_dispatcher.c -o picalc_dispatcher.o

picalc_worker.o: picalc_worker.c picalc_pipes.h
	$(CC) $(CFLAGS) -c picalc_worker.c -o picalc_worker.o

picalc_gatherer.o: picalc_gatherer.c picalc_pipes.h
	$(CC) $(CFLAGS) -c picalc_gatherer.c -o picalc_gatherer.o

picalc_fifos.o: picalc_fifos.c
	$(CC) $(CFLAGS) -c picalc_fifos.c -o picalc_fifos.o

picalc_agents.o: picalc_agents.c picalc_pipes.h integrate.h f.h
	$(CC) $(CFLAGS) -c picalc_agents.c -o picalc_agents.o

integrate.o: integrate.c integrate.h
	$(CC) $(CFLAGS) -c integrate.c -o integrate.o

f1.o: f1.c f.h
	$(CC) $(CFLAGS) -c f1.c -o f1.o

picalc_dispatcher: picalc_dispatcher.o picalc_agents.o integrate.o f1.o
	$(CC) -o picalc_dispatcher picalc_dispatcher.o picalc_agents.o integrate.o f1.o

picalc_worker: picalc_worker.o picalc_agents.o integrate.o f1.o
	$(CC) -o picalc_worker picalc_worker.o picalc_agents.o integrate.o f1.o

picalc_gatherer: picalc_gatherer.o picalc_agents.o integrate.o f1.o
	$(CC) -o picalc_gatherer picalc_gatherer.o picalc_agents.o integrate.o f1.o

picalc_fifos: picalc_fifos.o
	$(CC) -o picalc_fifos picalc_fifos.o

run_fifos: all
	rm -f work result
	mkfifo work
	mkfifo result
	./picalc_dispatcher 1000000 1000 work &
	./picalc_worker work result &
	./picalc_worker work result &
	./picalc_worker work result &
	./picalc_gatherer result
	rm -f work result

clean:
	rm -f $(TARGETS) $(OBJECTS) work result
