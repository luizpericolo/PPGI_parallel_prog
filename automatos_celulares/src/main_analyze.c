
#include<stdio.h>

// Include for SDL stuff.
//#include<SDL/SDL.h>

// Including our lib-ish source headers.
#include "cellular_automata.h"
//#include "cellular_automata_gfx.h"

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

typedef union{
    unsigned long long int64;
    struct{
        unsigned int lo, hi;
    } int32;
} tsc_counter;

#define RDTSC(cpu_c)             \
__asm__ __volatile__("rdtsc" : \
    "=a" ((cpu_c).int32.lo),  \
    "=d"((cpu_c).int32.hi) )


int main(void)
{

    struct timeval inicio, fim;
    tsc_counter tsc1, tsc2;
    long long unsigned int clock;
    double tempo;

    int *grid;
    //print_grid(grid);

    int i;
    int n;
    for(i=0; i<N_ITER;i++)
    {
        gettimeofday(&inicio, NULL);
        RDTSC(tsc1); 
        // Creating the random initial population for the Cellular Automata.
        grid = create_random_initial_population(grid);

        for(n=0; n<5; n++)
        {
            grid = apply_cave_generation_rule(grid);
            print_grid(grid);
        }

        RDTSC(tsc2);
        gettimeofday(&fim, NULL);

        tempo = (fim.tv_sec - inicio.tv_sec) * 1000 + (fim.tv_sec - inicio.tv_sec)/1000;
        printf("Tempo: %.2lf\n", tempo);

        clock = tsc2.int64 - tsc1.int64;
        printf("Tempo: %.2lf(ms) Clocks: %.2e\n", tempo/N_ITER, (double)clock/N_ITER);
        printf("Clock/tempo: %.2e\n\n", clock/tempo);
    }
        
    
    return 0;
}


