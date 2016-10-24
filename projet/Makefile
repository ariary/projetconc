#=======================================================================
# Basic C++: makefile
#-----------------------------------------------------------------------
# template :Julien DeAntoni --- No Copyright 2016
# modified by: Adrien Prestini & Antoine Rabenandrasana
#      v0.2 2016/09/06
#=======================================================================

#only ok for project with no templated classes

#compiler
COMPILER = g++
#linker
LINKER =g++

#options for linker and compiler
FLAGS =-g -ansi -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -D_DEBUG_ -std=c++11

EXE_NAME = main.exe

#can have several ones separated by spaces, only cpp files
SOURCES = main.cpp personne.cpp terrain.cpp mythreads.cpp contexte.cpp

SRCDIR = src
BINDIR = bin

#PATH to extra header used in the project (when using libs not installed in the OS)
INC_PATHS= -I 
OBJ = $(COMPILER) -c -I ./src/include

#extra libs used in the project (for instance -lpthread)
LIBS	= -lpthread -lrt


sans: $(EXE_NAME)

$(EXE_NAME): main.o
	$(COMPILER) -o $(BINDIR)/$(EXE_NAME) $(BINDIR)/*.o $(LIBS) $(FLAGS)

main.o: terrain.o personne.o mythreads.o contexte.o
	$(OBJ) -o $(BINDIR)/main.o $(SRCDIR)/main.cpp --std=c++11

terrain.o: personne.o 
	$(OBJ) -o $(BINDIR)/terrain.o $(SRCDIR)/terrain.cpp

personne.o:
	$(OBJ) -o $(BINDIR)/personne.o $(SRCDIR)/personne.cpp

mythreads.o:
	$(OBJ) -o $(BINDIR)/mythreads.o $(SRCDIR)/mythreads.cpp

contexte.o:
	$(OBJ) -std=c++11 -o $(BINDIR)/contexte.o $(SRCDIR)/contexte.cpp

clean:
	rm -f $(BINDIR)/*.o $(BINDIR)/$(EXE_NAME)
