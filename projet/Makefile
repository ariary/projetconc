CC=gcc
CFLAGS=-Wall -std=gnu99 -g

SRCDIR=src
EXEDIR=bin
SRC=$(wildcard $(SRCDIR)/*.c)
EXE=$(SRC:.c=)
OBJ=$(SRC:.c=.o)


all: $(EXE)

clean:
	rm -f *~ $(SRCDIR)/$(OBJ) $(EXEDIR)/executable

avec: $(SRCDIR)/personne.o $(SRCDIR)/terrain.o
	$(CC) -o $(EXEDIR)/executable $(SRCDIR)/personne.o $(SRCDIR)/terrain.o

$(SRCDIR)/personne.o: $(SRCDIR)/personne.c $(SRCDIR)/personne.h
	$(CC) -o $(SRCDIR)/personne.o -c $(SRCDIR)/personne.c $(CFLAGS)

$(SRCDIR)/terrain.o: $(SRCDIR)/terrain.c $(SRCDIR)/terrain.h
	$(CC) -o $(SRCDIR)/terrain.o -c $(SRCDIR)/terrain.c $(CFLAGS) 


sans: all
