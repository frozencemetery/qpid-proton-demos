# this is for testing purposes only
# clean it up before distribution

CFLAGS=-Wall -Wextra -pedantic -std=c99
CFLAGS+=-O0 -ggdb
CFLAGS+=$(shell pkg-config --cflags libqpid-proton)

LDFLAGS=$(shell pkg-config --libs libqpid-proton)

simple: simple.c
	gcc $(CFLAGS) $(LDFLAGS) simple.c -o simple

all: simple

default: simple

clean:
	rm -f simple
