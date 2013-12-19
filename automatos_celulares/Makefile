# The compiler we will be using.
CC=gcc

# The options we will pass to the compiler.
CSFLAGS=-Wall

# Cuda flags
CUFLAGS= -arch=sm_21

# Cuda compiler
CU=nvcc

LIBS=-I /usr/include/SDL -lSDL

# all : cell_automata

analyze: cell_automata_analyze

analyze_gprof: cell_automata_analyze_gprof

display: cell_automata

threads: cell_automata_threads

ca_gpu:
	$(CU) src/main_gpu.cu -o exe/main_gpu $(CUFLAGS)	

run_ca_gpu:
	./exe/main_gpu

ca_thread_barr:
	$(CC) src/main_thread_barr.c -o exe/main_thread_barr -Wall -lpthread

run_ca_thread_barr:
	./exe/main_thread_barr

run_gprof:
	./exe/main_analyze_gprof
	gprof ./exe/main_analyze_gprof gmon.out > analise.txt

run_analyze:
	./exe/main_analyze

run_analyze_tests:
	make run_analyze_5
	make run_analyze_10
	make run_analyze_15
	make run_analyze_20

run_analyze_10:
	echo "Running: sequential, 10 runs, 250 maps, width: 256, height: 64, fill: 45%"
	./exe/main_analyze 10 250 256 64 45 > results/sequential/seq_10_250.out

	echo "Running: sequential, 10 runs, 500 maps, width: 256, height: 64, fill: 45%"
	./exe/main_analyze 10 500 256 64 45 > results/sequential/seq_10_500.out

	echo "Running: sequential, 10 runs, 1000 maps, width: 256, height: 64, fill: 45%"
	./exe/main_analyze 10 1000 256 64 45 > results/sequential/seq_10_1000.out

run_analyze_20:
	echo "Running: sequential, 20 runs, 250 maps, width: 256, height: 64, fill: 45%"
	./exe/main_analyze 20 250 256 64 45 > results/sequential/seq_20_250.out

	echo "Running: sequential, 20 runs, 500 maps, width: 256, height: 64, fill: 45%"
	./exe/main_analyze 20 500 256 64 45 > results/sequential/seq_20_500.out

	echo "Running: sequential, 20 runs, 1000 maps, width: 256, height: 64, fill: 45%"
	./exe/main_analyze 20 1000 256 64 45 > results/sequential/seq_20_1000.out

run_ca_thread_10:
	echo "Running: 1 threads, 10 runs, 250 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 1 10 250 256 64 45 > results/thread/thread_10_250_01_256_64.out
	
	echo "Running: 2 threads, 10 runs, 250 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 2 10 250 256 64 45 > results/thread/thread_10_250_02_256_64.out
	
	echo "Running: 4 threads, 10 runs, 250 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 4 10 250 256 64 45 > results/thread/thread_10_250_04_256_64.out
	
	echo "Running: 8 threads, 10 runs, 250 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 8 10 250 256 64 45 > results/thread/thread_10_250_08_256_64.out

	echo "Running: 16 threads, 10 runs, 250 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 16 10 250 256 64 45 > results/thread/thread_10_250_16_256_64.out


	echo "Running: 1 threads, 10 runs, 500 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 1 10 500 256 64 45 > results/thread/thread_10_500_01_256_64.out
	
	echo "Running: 2 threads, 10 runs, 500 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 2 10 500 256 64 45 > results/thread/thread_10_500_02_256_64.out
	
	echo "Running: 4 threads, 10 runs, 500 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 4 10 500 256 64 45 > results/thread/thread_10_500_04_256_64.out
	
	echo "Running: 8 threads, 10 runs, 500 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 8 10 500 256 64 45 > results/thread/thread_10_500_08_256_64.out

	echo "Running: 16 threads, 10 runs, 500 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 16 10 500 256 64 45 > results/thread/thread_10_500_16_256_64.out


	echo "Running: 1 threads, 10 runs, 1000 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 1 10 1000 256 64 45 > results/thread/thread_10_1000_01_256_64.out
	
	echo "Running: 2 threads, 10 runs, 1000 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 2 10 1000 256 64 45 > results/thread/thread_10_1000_02_256_64.out
	
	echo "Running: 4 threads, 10 runs, 1000 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 4 10 1000 256 64 45 > results/thread/thread_10_1000_04_256_64.out
	
	echo "Running: 8 threads, 10 runs, 1000 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 8 10 1000 256 64 45 > results/thread/thread_10_1000_08_256_64.out

	echo "Running: 16 threads, 10 runs, 1000 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 16 10 1000 256 64 45 > results/thread/thread_10_1000_16_256_64.out

run_ca_thread_20:
	echo "Running: 1 threads, 20 runs, 250 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 1 20 250 256 64 45 > results/thread/thread_20_250_01_256_64.out
	
	echo "Running: 2 threads, 20 runs, 250 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 2 20 250 256 64 45 > results/thread/thread_20_250_02_256_64.out
	
	echo "Running: 4 threads, 20 runs, 250 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 4 20 250 256 64 45 > results/thread/thread_20_250_04_256_64.out
	
	echo "Running: 8 threads, 20 runs, 250 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 8 20 250 256 64 45 > results/thread/thread_20_250_08_256_64.out

	echo "Running: 16 threads, 20 runs, 250 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 16 20 250 256 64 45 > results/thread/thread_20_250_16_256_64.out


	echo "Running: 1 threads, 20 runs, 500 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 1 20 500 256 64 45 > results/thread/thread_20_500_01_256_64.out
	
	echo "Running: 2 threads, 20 runs, 500 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 2 20 500 256 64 45 > results/thread/thread_20_500_02_256_64.out
	
	echo "Running: 4 threads, 20 runs, 500 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 4 20 500 256 64 45 > results/thread/thread_20_500_04_256_64.out
	
	echo "Running: 8 threads, 20 runs, 500 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 8 20 500 256 64 45 > results/thread/thread_20_500_08_256_64.out

	echo "Running: 16 threads, 20 runs, 500 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 16 20 500 256 64 45 > results/thread/thread_20_500_16_256_64.out


	echo "Running: 1 threads, 20 runs, 1000 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 1 20 1000 256 64 45 > results/thread/thread_20_1000_01_256_64.out
	
	echo "Running: 2 threads, 20 runs, 1000 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 2 20 1000 256 64 45 > results/thread/thread_20_1000_02_256_64.out
	
	echo "Running: 4 threads, 20 runs, 1000 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 4 20 1000 256 64 45 > results/thread/thread_20_1000_04_256_64.out
	
	echo "Running: 8 threads, 20 runs, 1000 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 8 20 1000 256 64 45 > results/thread/thread_20_1000_08_256_64.out

	echo "Running: 16 threads, 20 runs, 1000 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread 16 20 1000 256 64 45 > results/thread/thread_20_1000_16_256_64.out

run_ca_thread_barr_10:
	echo "Running: 1 threads, 10 runs, 250 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 1 10 250 256 64 45 > results/thread/thread_barr_10_250_01_256_64.out
	
	echo "Running: 2 threads, 10 runs, 250 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 2 10 250 256 64 45 > results/thread/thread_barr_10_250_02_256_64.out
	
	echo "Running: 4 threads, 10 runs, 250 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 4 10 250 256 64 45 > results/thread/thread_barr_10_250_04_256_64.out
	
	echo "Running: 8 threads, 10 runs, 250 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 8 10 250 256 64 45 > results/thread/thread_barr_10_250_08_256_64.out

	echo "Running: 16 threads, 10 runs, 250 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 16 10 250 256 64 45 > results/thread/thread_barr_10_250_16_256_64.out


	echo "Running: 1 threads, 10 runs, 500 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 1 10 500 256 64 45 > results/thread/thread_barr_10_500_01_256_64.out
	
	echo "Running: 2 threads, 10 runs, 500 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 2 10 500 256 64 45 > results/thread/thread_barr_10_500_02_256_64.out
	
	echo "Running: 4 threads, 10 runs, 500 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 4 10 500 256 64 45 > results/thread/thread_barr_10_500_04_256_64.out
	
	echo "Running: 8 threads, 10 runs, 500 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 8 10 500 256 64 45 > results/thread/thread_barr_10_500_08_256_64.out

	echo "Running: 16 threads, 10 runs, 500 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 16 10 500 256 64 45 > results/thread/thread_barr_10_500_16_256_64.out


	echo "Running: 1 threads, 10 runs, 1000 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 1 10 1000 256 64 45 > results/thread/thread_barr_10_1000_01_256_64.out
	
	echo "Running: 2 threads, 10 runs, 1000 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 2 10 1000 256 64 45 > results/thread/thread_barr_10_1000_02_256_64.out
	
	echo "Running: 4 threads, 10 runs, 1000 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 4 10 1000 256 64 45 > results/thread/thread_barr_10_1000_04_256_64.out
	
	echo "Running: 8 threads, 10 runs, 1000 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 8 10 1000 256 64 45 > results/thread/thread_barr_10_1000_08_256_64.out

	echo "Running: 16 threads, 10 runs, 1000 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 16 10 1000 256 64 45 > results/thread/thread_barr_10_1000_16_256_64.out

run_ca_thread_barr_20:
	echo "Running: 1 threads, 20 runs, 250 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 1 20 250 256 64 45 > results/thread/thread_barr_20_250_01_256_64.out
	
	echo "Running: 2 threads, 20 runs, 250 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 2 20 250 256 64 45 > results/thread/thread_barr_20_250_02_256_64.out
	
	echo "Running: 4 threads, 20 runs, 250 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 4 20 250 256 64 45 > results/thread/thread_barr_20_250_04_256_64.out
	
	echo "Running: 8 threads, 20 runs, 250 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 8 20 250 256 64 45 > results/thread/thread_barr_20_250_08_256_64.out

	echo "Running: 16 threads, 20 runs, 250 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 16 20 250 256 64 45 > results/thread/thread_barr_20_250_16_256_64.out


	echo "Running: 1 threads, 20 runs, 500 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 1 20 500 256 64 45 > results/thread/thread_barr_20_500_01_256_64.out
	
	echo "Running: 2 threads, 20 runs, 500 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 2 20 500 256 64 45 > results/thread/thread_barr_20_500_02_256_64.out
	
	echo "Running: 4 threads, 20 runs, 500 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 4 20 500 256 64 45 > results/thread/thread_barr_20_500_04_256_64.out
	
	echo "Running: 8 threads, 20 runs, 500 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 8 20 500 256 64 45 > results/thread/thread_barr_20_500_08_256_64.out

	echo "Running: 16 threads, 20 runs, 500 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 16 20 500 256 64 45 > results/thread/thread_barr_20_500_16_256_64.out


	echo "Running: 1 threads, 20 runs, 1000 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 1 20 1000 256 64 45 > results/thread/thread_barr_20_1000_01_256_64.out
	
	echo "Running: 2 threads, 20 runs, 1000 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 2 20 1000 256 64 45 > results/thread/thread_barr_20_1000_02_256_64.out
	
	echo "Running: 4 threads, 20 runs, 1000 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 4 20 1000 256 64 45 > results/thread/thread_barr_20_1000_04_256_64.out
	
	echo "Running: 8 threads, 20 runs, 1000 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 8 20 1000 256 64 45 > results/thread/thread_barr_20_1000_08_256_64.out

	echo "Running: 16 threads, 20 runs, 1000 maps, width: 256, height: 64, fill: 45%"
	./exe/main_thread_barr 16 20 1000 256 64 45 > results/thread/thread_barr_20_1000_16_256_64.out

run_ca_thread_gprof:
	./exe/main_thread_gprof
	gprof ./exe/main_thread_gprof gmon.out > analise_thread.txt

ca_thread:
	$(CC) src/main_thread.c -o exe/main_thread -Wall -lpthread

ca_thread_gprof:
	$(CC) -g -pg src/main_thread.c -o exe/main_thread_gprof -lpthread

cell_automata_analyze:
	$(CC) $(CSFLAGS) src/main_analyze.c -o exe/main_analyze

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
	
