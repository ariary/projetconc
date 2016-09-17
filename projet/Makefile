CC=gcc
CFLAGS=-Wall -std=gnu99 -g

SRCDIR=src
SRC=$(wildcard $(SRCDIR)/*.c)
EXE=$(SRC:.c=)

all: $(EXE)

clean:
	rm -f $(EXE) *~