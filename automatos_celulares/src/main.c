
#include<stdio.h>

// Include for SDL stuff.
#include<SDL/SDL.h>

// Including our lib-ish source headers.
#include "cellular_automata.h"
#include "cellular_automata_gfx.h"


int main(void)
{

    int *grid;

    // Creating the random initial population for the Cellular Automata.
    grid = create_random_initial_population(grid);

    //The surfaces
    SDL_Surface *image = NULL;
    SDL_Surface *screen = NULL;

    //Make sure the program waits for a quit
    int quit = false;

    //The event structure that will be used
    SDL_Event event;

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    SDL_WM_SetCaption("Cellular Automata", NULL);
    
    //While the user hasn't quit
    while( quit == false )
    {
        // Iterate on the grid once more.
        grid = apply_cave_generation_rule(grid);
        //grid = apply_4_5_rule(grid);

        // Print the current iteration of the grid in the console.
        print_grid(grid);

        // Paint it black!
        SDL_FillRect(screen , NULL , 0x000000);

        screen = draw_grid(grid, screen);

        SDL_Flip(screen);

        // Wait for 3.5 seconds.
        SDL_Delay(1500);

        //While there's an event to handle
        while( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }    
        }
    }

    //Free the surface and quit SDL
    clean_up(image);

    return 0;
}


