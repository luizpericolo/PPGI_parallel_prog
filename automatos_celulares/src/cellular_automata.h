// Defining some constants
#define GRID_WIDTH 5
#define GRID_HEIGHT 5
#define CELL_COUNT GRID_WIDTH * GRID_HEIGHT


int* create_random_initial_population();
void print_grid(int *grid);
int count_neighbors(int *grid, int x);
