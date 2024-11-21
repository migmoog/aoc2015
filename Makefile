CC :=gcc
CFLAGS :=-g -std=c99 -Wall -Werror

SOURCES := $(wildcard *.c)
OBJS := $(SOURCES:.c=.o)

.PHONY: clean

all: aoc 

aoc: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f $(OBJS)
	rm aoc