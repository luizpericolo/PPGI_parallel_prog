
#include<stdio.h>

// Include for SDL stuff.
//#include<SDL/SDL.h>

// Including our lib-ish source headers.
#include "cellular_automata.h"
//#include "cellular_automata_gfx.h"

#include <stdio.h>
#include <sys/time.h>
#include <time.h>
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

int* create_random_initial_population()
{

    int *grid = malloc(CELL_COUNT * sizeof(int));

    srand(time(NULL));

    int i = 0;

    int count = 0;
    
    for(i=0; i<CELL_COUNT; i++)
    {
        if(rand()%100 < FILL_PROB)
        {
            grid[i] = 1;
            count++;
        }
        else
        {
            grid[i] = 0;
        }
            
    }

    //printf("Number of walls: %d\n", count);
    //printf("Number of cells: %d\n", CELL_COUNT);
    //printf("Percentage of Walls: %.2f\n", count/(CELL_COUNT * 1.0f));

    return grid;
}


void print_grid(int *grid)
{
    /* This function iterates over the grid and prints it in a matricial fashion. */
    
    int i, j;
    for(i=0; i<GRID_HEIGHT; i++)
    {
        for(j=0;j<GRID_WIDTH;j++)
        {
            if(grid[(i * GRID_WIDTH) + j] == 1)
                printf("@");
            else
                printf(" ");
        }

        printf("\n");
    }

    printf("\n");

}


int count_neighbors(int *grid, int x)
{
    /* This functions counts how many neighbors
       equal to 1 a cell has (in all 8 directions!). */

    int count = 0;

    // Checking for the East Neighbor.
    if(x % GRID_WIDTH != GRID_WIDTH - 1)
    {
        if(grid[x + 1] == 1)
        {
            count++;
        }
    }

    // Checking for the West Neighbor.
    if(x % GRID_WIDTH != 0)
    {
        if(grid[x - 1] == 1)
        {
            count++;
        }
    }

    // Checking for the North Neighbor.
    if(x - GRID_WIDTH >= 0)
    {
        if(grid[x - GRID_WIDTH] == 1)
        {
            count++;
        }

        // Checking for the Northwest Neighbor.
        if((x - GRID_WIDTH - 1) % GRID_WIDTH != GRID_WIDTH - 1  
                && x - GRID_WIDTH - 1 >= 0)
        {
            if(grid[x - GRID_WIDTH - 1] == 1)
            {
                count++;
            }
                
        }

        // Checking for the Northeast Neighbor.
        if((x - GRID_WIDTH + 1) % GRID_WIDTH != 0)
        {
            if(grid[x - GRID_WIDTH + 1] == 1)
            {
                count++;
            }
                
        }
    }

    // Checking for the South Neighbor.
    if(x + GRID_WIDTH < CELL_COUNT)
    {
        if(grid[x + GRID_WIDTH] == 1)
        {
            count++;
        }
            
        // Checking for the Southwest Neighbor.
        if((x + GRID_WIDTH - 1) % GRID_WIDTH != GRID_WIDTH - 1)
        {
            if(grid[x + GRID_WIDTH - 1])
            {
                count++;
            }
                
        }

        // Checking for the Southeast Neighbor.
        if((x + GRID_WIDTH + 1) % GRID_WIDTH != 0 
                && x + GRID_WIDTH + 1 < CELL_COUNT)
        {
            if(grid[x + GRID_WIDTH + 1])
            {
                count++;
            }
                
        }
    }
    return count;
}

int * apply_cave_generation_rule(int *grid)
{
    int* next_gen = malloc (CELL_COUNT * sizeof(int));

    int i;

    int n_count = 0;

    for(i=0; i<CELL_COUNT; i++)
    {
        n_count = count_neighbors(grid, i);

        
        // Applying the B678 rule.
        if(grid[i] == 0)
        {
            if((n_count == 6) || (n_count == 7) || (n_count == 8))
                next_gen[i] = 1;
            else
                next_gen[i] = grid[i];
        }

        // Applying the S345678
        if(grid[i] == 1)
        {
            if((n_count == 0) || (n_count == 1) || (n_count == 2))
                next_gen[i] = 0;
            else
                next_gen[i] = grid[i];
        }
    }

    return next_gen;
}
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

    gettimeofday(&inicio, NULL);
    RDTSC(tsc1); 

    grid = create_random_initial_population(grid);

    for(i=0; i<N_ITER;i++)
    {
        
        // Creating the random initial population for the Cellular Automata.

        //for(n=0; n<5; n++)
        //{
            grid = apply_cave_generation_rule(grid);
            //print_grid(grid);
        //}

    
    }

    RDTSC(tsc2);
    gettimeofday(&fim, NULL);

    tempo = (fim.tv_sec - inicio.tv_sec) * 1000 + (fim.tv_sec - inicio.tv_sec)/1000;
    printf("Tempo: %.2lf\n", tempo);

    clock = tsc2.int64 - tsc1.int64;
    printf("Tempo: %.2lf(ms) Clocks: %.2e\n", tempo/N_ITER, (double)clock/N_ITER);
    printf("Clock/tempo: %.2e\n\n", clock/tempo);

    print_grid(grid);
        
    
    return 0;
}


