BINDIR=bin
EXEC=$(BINDIR)/mazegame.app

CXX=clang++
CXX_FLAGS=-Wall -O2
LIBS=-lSDL2 -lSDL2_image

SRCDIR=src
SOURCES=$(SRCDIR)/mazeGame.cpp

OBJDIR=$(BINDIR)
OBJECTS=$(OBJDIR)/mazeGame.o

.PHONY: all
all: build

build: bin/mazeGame.o
	$(CXX) $(CXX_FLAGS) -o $(EXEC) bin/mazeGame.o $(LIBS)

bin/mazeGame.o: src/mazeGame.cpp
	$(CXX) $(CXX_FLAGS) -c -o bin/mazeGame.o $(SOURCES)

clean:
	rm $(OBJECTS)
	rm $(EXEC)

help:
	@echo "              Maze game using SDL"
	@echo "================================================"
	@echo "      make - build application"
	@echo "make clean - remove application and object files"
