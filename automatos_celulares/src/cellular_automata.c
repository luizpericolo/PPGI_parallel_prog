// Includes for random number generation.
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include "cellular_automata.h"

int* create_random_initial_population()
{

    int *grid = malloc(CELL_COUNT * sizeof(int));

	srand(time(NULL));

	int i = 0;
	
    for(i=0; i<CELL_COUNT; i++)
	{
	    grid[i] = rand() % 2;
    }

    return grid;
}


void print_grid(int *grid)
{
    /* This function iterates over the grid and prints it in a matricial fashion. */
    int i, j;
    for(i=0; i<GRID_WIDTH; i++)
    {
        for(j=0;j<GRID_HEIGHT;j++)
        {
            printf("%d", grid[(i * GRID_WIDTH) + j]);
        }
        printf("\n");
    }
}


int count_neighbors(int *grid, int x)
{
    /* This functions counts how many neighbors equal to 1 a cell has. */
    /* For now we are considering a neighborhood of 4 instead of 9. */

    int count = 0;

    // Checking for the East Neighbor.
    if(x % GRID_WIDTH != GRID_WIDTH - 1)
    {
        if(grid[x + 1] == 1)
            count++;
    }

    // Checking for the West Neighbor.
    if(x % GRID_WIDTH != 0)
    {
        if(grid[x - 1] == 1)
            count++;
    }

    // Checking for the North Neighbor.
    if(x - GRID_WIDTH > 0)
    {
        if(grid[x - GRID_WIDTH] == 1)
            count++;
    }

    // Checking for the South Neighbor.
    if(x + GRID_WIDTH > 0)
    {
        if(grid[x + GRID_WIDTH] == 1)
            count++;
    }

    return count;
}

