# The compiler we will be using.
CC=gcc

# The options we will pass to the compiler.
CSFLAGS=-c -Wall


all : cellular_automata

cellular_automata: main.o
	$(CC) main.o -o obj/main

main.o: src/main.c
	$(CC) $(CSFLAGS) src/main.c

clean:
	rm -rf obj/*

# Target that should install the dependencies in devian based linux distros.
deb-deps:
	@sudo apt-get install libsdl1.2-dev libsdl1.2debian
	
