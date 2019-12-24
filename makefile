CFLAGS=-g -O2 -Wall -pg
CC=gcc

PROGRAM_NAME= filter
OBJS = main.o readwrite.o filter.o

$(PROGRAM_NAME): $(OBJS)
	$(CC) -pg -o $@ $? -lm

clean:
	rm  *.o $(PROGRAM_NAME)