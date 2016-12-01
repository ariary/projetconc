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

ifeq ($(GRAPHIQUE),yes)
	COMPILER = g++ -DGRAPH
else 
	
endif


#linker
LINKER =g++

#options for linker and compiler
FLAGS =-g -ansi -Wall -Wextra -Wold-style-cast -Woverloaded-virtual  -std=c++11

EXE_NAME = main.exe

#can have several ones separated by spaces, only cpp files
SOURCES = main.cpp personne.cpp terrain.cpp mythreads.cpp contexte.cpp CyclicBarrier.cpp

SRCDIR = src
BINDIR = bin

#PATH to extra header used in the project (when using libs not installed in the OS)
INC_PATHS= -I 
OBJ = $(COMPILER) -c -I ./src/include

#extra libs used in the project (for instance -lpthread)
LIBS	= -lpthread -ll

GRAPH = `pkg-config --libs --cflags sfml-system sfml-window sfml-graphics sfml-audio sfml-network`


compilation: $(EXE_NAME)

$(EXE_NAME): main.o
	$(COMPILER) -o $(BINDIR)/$(EXE_NAME) $(BINDIR)/*.o $(LIBS) $(GRAPH) $(FLAGS)

#main.o: terrain.o personne.o mythreads.o contexte.o graphique.o 


main.o: terrain.o personne.o mythreads.o contexte.o graphique.o CyclicBarrier.o
	$(OBJ) -o $(BINDIR)/main.o $(SRCDIR)/main.cpp --std=c++11

terrain.o: personne.o 
	$(OBJ) -o $(BINDIR)/terrain.o $(SRCDIR)/terrain.cpp --std=c++11

personne.o:
	$(OBJ) -o $(BINDIR)/personne.o $(SRCDIR)/personne.cpp --std=c++11

mythreads.o:
	$(OBJ) -o $(BINDIR)/mythreads.o $(SRCDIR)/mythreads.cpp --std=c++11

contexte.o: CyclicBarrier.o
	$(OBJ) -std=c++11 -o $(BINDIR)/contexte.o $(SRCDIR)/contexte.cpp --std=c++11

graphique.o:
	$(OBJ) -o $(BINDIR)/graphique.o $(SRCDIR)/graphique.cpp --std=c++11

CyclicBarrier.o:
	$(OBJ) -o $(BINDIR)/CyclicBarrier.o $(SRCDIR)/CyclicBarrier.cpp --std=c++11

clean:
	rm -f $(BINDIR)/*.o $(BINDIR)/$(EXE_NAME)
