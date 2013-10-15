# The compiler we will be using.
CC=gcc

# The options we will pass to the compiler.
CSFLAGS=-c -Wall

LIBS=-I /usr/include/SDL -lSDL

all : cell_automata

cell_automata: main.o cellular_automata.o cellular_automata_gfx.o 
	$(CC) obj/main.o obj/cellular_automata.o obj/cellular_automata_gfx.o -o exe/main $(LIBS)

cellular_automata.o: src/cellular_automata.c src/cellular_automata.h
	$(CC) $(CSFLAGS) src/cellular_automata.c -o obj/cellular_automata.o

cellular_automata_gfx.o: src/cellular_automata_gfx.c src/cellular_automata_gfx.h
	$(CC) $(CSFLAGS) src/cellular_automata_gfx.c -o obj/cellular_automata_gfx.o

main.o: src/main.c
	$(CC) $(CSFLAGS) src/main.c -o obj/main.o

clean:
	rm -rf obj/*
	rm -rf exe/*

# Target that should install the dependencies in devian based linux distros.
deb-deps:
	@sudo apt-get install libsdl1.2-dev libsdl1.2debian
	@sudo apt-get install libsdl-image1.2-dev
	
