# The compiler we will be using.
CC=gcc

# The options we will pass to the compiler.
CSFLAGS=-c -Wall


all : cell_automata

cell_automata: main.o cellular_automata.o
	$(CC) main.o cellular_automata.o -o obj/main

cellular_automata.o: src/cellular_automata.c src/cellular_automata.h
	$(CC) $(CSFLAGS) src/cellular_automata.c 

main.o: src/main.c
	$(CC) $(CSFLAGS) src/main.c

clean:
	rm -rf obj/*

# Target that should install the dependencies in devian based linux distros.
deb-deps:
	@sudo apt-get install libsdl1.2-dev libsdl1.2debian
	
