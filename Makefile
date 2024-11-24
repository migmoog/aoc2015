CC :=gcc
CFLAGS :=-g -std=c99 -Wall -Werror -Wno-error=deprecated-declarations
LIBS := -lssl -lcrypto -lm

SOURCES := $(wildcard *.c)
OBJS := $(SOURCES:.c=.o)

.PHONY: clean

all: aoc 

aoc: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@ $(LIBS)

clean:
	rm -f $(OBJS)
	rm aoc