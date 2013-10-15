
#include<stdio.h>

// Include for SDL stuff.
#include<SDL/SDL.h>


#include "cellular_automata.h"
#include "cellular_automata_gfx.h"


int main(void)
{

    int *grid;

    grid = create_random_initial_population(grid);

    print_grid(grid);

    int i;
    int n = 0;

    for(i=0; i<CELL_COUNT; i++)
    {
        n = count_neighbors(grid,i);
        //printf("Posicao [%d] tem %d vizinhos.\n", i, n);
    }

    show_screen();

    return 0;
}


