# The compiler we will be using.
CC=gcc

# The options we will pass to the compiler.
CSFLAGS=-Wall

LIBS=-I /usr/include/SDL -lSDL

# all : cell_automata

analyze: cell_automata_analyze

analyze_gprof: cell_automata_analyze_gprof

display: cell_automata

threads: cell_automata_threads

run_gprof:
	./exe/main_analyze_gprof
	gprof ./exe/main_analyze_gprof gmon.out > analise.txt

run:
	./exe/main

run_ca_thread:
	./exe/main_thread

ca_thread:
	$(CC) src/main_thread.c -o exe/main_thread -Wall -lpthread

cell_automata_analyze: main_analyze.o cellular_automata.o
	$(CC) obj/main_analyze.o obj/cellular_automata.o -o exe/main_analyze

cell_automata_analyze_gprof:
	$(CC) -g -pg src/main_analyze_gprof.c -o exe/main_analyze_gprof

main_analyze.o: src/main_analyze.c
	$(CC) $(CSFLAGS) src/main_analyze.c -o obj/main_analyze.o $(CSFLAGS)

cell_automata: main.o cellular_automata.o cellular_automata_gfx.o 
	$(CC) obj/main.o obj/cellular_automata.o obj/cellular_automata_gfx.o -o exe/main $(LIBS)

cellular_automata.o: src/cellular_automata.c src/cellular_automata.h
	$(CC) $(CSFLAGS) src/cellular_automata.c -o obj/cellular_automata.o

main.o: src/cellular_automata.o
	$(CC) $(CSFLAGS) src/main.c obj/main.o $(LIBS)

clean:
	rm -rf obj/*
	rm -rf exe/*
#rm analise.txt
	rm gmon.out

# Target that should install the dependencies in devian based linux distros.
deb-deps:
	@sudo apt-get install libsdl1.2-dev libsdl1.2debian
	@sudo apt-get install libsdl-image1.2-dev
	
