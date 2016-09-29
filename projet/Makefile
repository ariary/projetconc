#=======================================================================
# Basic C++: makefile example to use as a reminder or as a template
#-----------------------------------------------------------------------
# Julien DeAntoni --- No Copyright 2016
# $Id: convenient Makefile but muist be tuned for templated project 
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
SOURCES = main.cpp personne.cpp terrain.cpp

SRCDIR = src
BINDIR = bin

#PATH to extra header used in the project (when using libs not installed in the OS)
INC_PATHS= -I 
OBJ = $(COMPILER) -c -I ./src/include

#extra libs used in the project (for instance -lpthread)
LIBS	= -L 

GRAPH = `pkg-config --libs --cflags sfml-system sfml-window sfml-graphics sfml-audio sfml-network`

#LINKOBJ	= $(SOURCES:.cpp=.o)
#SOURCEHEADERS = $(SOURCES:.cpp=./include/.h)

avec: $(EXE_NAME)

$(EXE_NAME): main.o
	$(COMPILER) -o $(BINDIR)/$(EXE_NAME) $(BINDIR)/*.o $(GRAPH) $(FLAGS)

main.o: terrain.o personne.o
	$(OBJ) -o $(BINDIR)/main.o $(SRCDIR)/main.cpp

terrain.o: personne.o 
	$(OBJ) -o $(BINDIR)/terrain.o $(SRCDIR)/terrain.cpp

personne.o:
	$(OBJ) -o $(BINDIR)/personne.o $(SRCDIR)/personne.cpp

clean:
	rm -f $(BINDIR)/*.o $(BINDIR)/$(EXE_NAME)