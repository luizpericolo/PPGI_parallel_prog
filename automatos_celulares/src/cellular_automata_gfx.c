#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "cellular_automata_gfx.h"

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    //Temporary rectangle to hold the offsets
    SDL_Rect offset;
    
    //Get the offsets
    offset.x = x;
    offset.y = y;
    
    //Blit the surface
    SDL_BlitSurface(source, NULL, destination, &offset);
}

int init(SDL_Surface *screen)
{
	int ret = 0;
    //Initialize all SDL subsystems
	ret = SDL_Init(SDL_INIT_EVERYTHING);

    if(ret == -1)
    {
        return false;    
    }
    
    //Set up the screen
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    
    //If there was an error in setting up the screen
    if(screen == NULL)
    {
        return false;    
    }
    
    //Set the window caption
    SDL_WM_SetCaption("Cellular Automata", NULL);
    
    //If everything initialized fine
    return true;
}


void clean_up(SDL_Surface *image)
{
    //Free the image
    SDL_FreeSurface( image );
    
    //Quit SDL
    SDL_Quit();    
}


int show_screen()
{

	//The surfaces
	SDL_Surface *image = NULL;
	SDL_Surface *screen = NULL;

	int x = 0;
	int y = 0;


    //Make sure the program waits for a quit
    int quit = false;

    int status = true;

    //The event structure that will be used
	SDL_Event event;

    
   	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    image = SDL_LoadBMP("sdl_test.bmp");
    SDL_BlitSurface(image, NULL, screen, NULL);
    
    //Apply the surface to the screen
    apply_surface(x, y, image, screen);
    
    //Update the Screen
    SDL_Flip(screen);
    
    //While the user hasn't quit
    while( quit == false )
    {
    	SDL_FillRect(screen , NULL , 0x221122);
    	x += 1;
    	y += 1;
    	apply_surface(x, y, image, screen);
    	SDL_Flip(screen);

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
