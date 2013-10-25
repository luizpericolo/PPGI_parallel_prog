// Defining some constants
#define GRID_WIDTH 60
#define GRID_HEIGHT 60
#define CELL_COUNT GRID_WIDTH * GRID_HEIGHT
#define FILL_PROB 45

#define CELL_WIDTH 8
#define CELL_HEIGHT 8

#define N_ITER 2

// GFX definitions
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32

// Cellular Automata functions
int* create_random_initial_population();
void print_grid(int *grid);
int count_neighbors(int *grid, int x);
int * apply_cave_generation_rule(int *grid);
int * apply_4_5_rule(int *grid);


// GFX Functions
SDL_Surface* draw_grid(int* grid, SDL_Surface *screen);
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);
void clean_up(SDL_Surface *image);

