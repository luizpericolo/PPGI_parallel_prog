#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32

#define true 1
#define false 0


SDL_Surface* draw_grid(int* grid, SDL_Surface *screen);
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);
void clean_up(SDL_Surface *image);


