CC = gcc
CFLAGS = -Wall -g

TARGET = picalc_pipes
OBJS = picalc_pipes.o picalc_agents.o integrate.o f1.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o picalc_pipes picalc_pipes.o picalc_agents.o integrate.o f1.o

picalc_pipes.o: picalc_pipes.c picalc_pipes.h
	$(CC) $(CFLAGS) -c picalc_pipes.c -o picalc_pipes.o

picalc_agents.o: picalc_agents.c picalc_pipes.h integrate.h f.h
	$(CC) $(CFLAGS) -c picalc_agents.c -o picalc_agents.o

integrate.o: integrate.c integrate.h
	$(CC) $(CFLAGS) -c integrate.c -o integrate.o

f1.o: f1.c f.h
	$(CC) $(CFLAGS) -c f1.c -o f1.o

clean:
	rm -f $(OBJS) $(TARGET)
