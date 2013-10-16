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
