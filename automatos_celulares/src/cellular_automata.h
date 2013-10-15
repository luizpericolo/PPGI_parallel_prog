// Defining some constants
#define GRID_WIDTH 30
#define GRID_HEIGHT 30
#define CELL_COUNT GRID_WIDTH * GRID_HEIGHT
#define FILL_PROB 45


int* create_random_initial_population();
void print_grid(int *grid);
int count_neighbors(int *grid, int x);
int * apply_cave_generation_rule(int *grid);
int * apply_4_5_rule(int *grid);
