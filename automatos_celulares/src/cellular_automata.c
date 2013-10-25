// Includes for random number generation.
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "cellular_automata.h"

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

    printf("Number of walls: %d\n", count);
    printf("Number of cells: %d\n", CELL_COUNT);
    printf("Percentage of Walls: %.2f\n", count/(CELL_COUNT * 1.0f));

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

    printf("\n");

}


int count_neighbors(int *grid, int x)
{
    /* This functions counts how many neighbors equal to 1 a cell has (in all 8 directions!). */

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
        if((x - GRID_WIDTH - 1) % GRID_WIDTH != GRID_WIDTH - 1  && x - GRID_WIDTH - 1 >= 0)
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
        if((x + GRID_WIDTH + 1) % GRID_WIDTH != 0 && x + GRID_WIDTH + 1 < CELL_COUNT)
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

int * apply_4_5_rule(int *grid)
{
    /* B5678/S45678 */
    int* next_gen = malloc (CELL_COUNT * sizeof(int));

    int i;

    int n_count = 0;

    for(i=0; i<CELL_COUNT; i++)
    {
        n_count = count_neighbors(grid, i);

        // Applying the B5678 rule.
        if(grid[i] == 0)
        {
            if((n_count == 5) || (n_count == 6) || (n_count == 7) || (n_count == 8))
                next_gen[i] = 1;
            else
                next_gen[i] = grid[i];
        }

        // Applying the S45678
        if(grid[i] == 1)
        {
            if((n_count == 0) || (n_count == 1) || (n_count == 2) || (n_count == 3))
                next_gen[i] = 0;
            else
                next_gen[i] = grid[i];
        }
    }

    return next_gen;   
}

// GFX functions
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "cellular_automata.h"
#include "cellular_automata_gfx.h"

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
    //Temporary rectangle to hold the offsets
    SDL_Rect dest;
    SDL_Rect src;

    src.x = 0;
    src.y = 0;
    src.w = CELL_WIDTH;
    src.h = CELL_HEIGHT;


    //Set the destination
    dest.x = x;
    dest.y = y;
    
    //Blit the surface
    SDL_BlitSurface(source, &src, destination, &dest);
}


void clean_up(SDL_Surface *image)
{
    //Free the image
    SDL_FreeSurface( image );
    
    //Quit SDL
    SDL_Quit();    
}


SDL_Surface* draw_grid(int* grid, SDL_Surface *screen)
{
    /* Draws the grid passed as a parameter and fills the borders afterwards. */
    SDL_Surface *cell;

    cell = SDL_LoadBMP("img/cell.bmp");

    int x, y;
    int i;

    for(i=0; i<CELL_COUNT; i++)
    {
        if(grid[i] == 1)
        {

            x = ((i % GRID_WIDTH) * CELL_WIDTH) + 1;
            y = ((i / GRID_WIDTH) * CELL_WIDTH) + 1;

            apply_surface(x, y, cell, screen);
        }

        // Adding the top border.
        if(i / GRID_WIDTH == 0)
        {
            x = ((i % GRID_WIDTH) * CELL_WIDTH) + 1;
            y = ((i / GRID_WIDTH) * CELL_WIDTH) + 1;

            apply_surface(x, y, cell, screen);
        }

        // Adding the left border.
        if(i % GRID_WIDTH == 0)
        {
            x = ((i % GRID_WIDTH) * CELL_WIDTH) + 1;
            y = ((i / GRID_WIDTH) * CELL_WIDTH) + 1;

            apply_surface(x, y, cell, screen);
        }

        // Adding the right border.
        if(i % GRID_WIDTH == GRID_WIDTH - 1)
        {
            x = ((i % GRID_WIDTH) * CELL_WIDTH) + 1;
            y = ((i / GRID_WIDTH) * CELL_WIDTH) + 1;

            apply_surface(x, y, cell, screen);
        }

        // Adding the bottom border.
        if(i / GRID_WIDTH == GRID_WIDTH - 1)
        {
            x = ((i % GRID_WIDTH) * CELL_WIDTH) + 1;
            y = ((i / GRID_WIDTH) * CELL_WIDTH) + 1;

            apply_surface(x, y, cell, screen);
        }
        
    }

    return screen;
}