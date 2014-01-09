#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define FILL_PROB 45

int* create_random_initial_population(int width, int height);
void print_grid(int *grid, int width, int height);
int count_neighbors(int *grid, int x, int width, int height);
int * apply_cave_generation_rule(int *grid, int width, int height);
void fill_borders(int *grid, int width, int height);

int main(int argc, char* argv[])
{
	int rank, size;
	int dimensions[2] = {64, 32};
	int *grid;

	grid = malloc(dimensions[0] * dimensions[1] * sizeof(int));

	MPI_Status status;


	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	/* Generating different seeds for each process! */
	srand(time(NULL)+rank);

	if(size < 2)
	{
		printf("Please run with a least 2 processes. Terminating...\n");
		MPI_Finalize();
		return 1;
	}

	if(rank == 0)
	{
	
		/* Master of MPI Puppets */
		int i;

		for(i=1; i<size; i++)
			MPI_Send(dimensions, 2, MPI_INT, i, 123, MPI_COMM_WORLD);

		for(i=1; i<size; i++)
		{
			MPI_Recv(grid, dimensions[0] * dimensions[1], MPI_INT, i, 123, MPI_COMM_WORLD, &status);
			printf("Mapa #%d:\n", i);
			print_grid(grid, dimensions[0], dimensions[1]);
		}
		free(grid);
			
	}
	else
	{
		/* I'm pulling your MPI strings */
		int i;
		MPI_Recv(dimensions, 2, MPI_INT, 0, 123, MPI_COMM_WORLD, &status);
		
		grid = create_random_initial_population(dimensions[0], dimensions[1]);
		
		for(i=0; i<5; i++)
		{
			grid = apply_cave_generation_rule(grid, dimensions[0], dimensions[1]);
			fill_borders(grid, dimensions[0], dimensions[1]);
		}

		//print_grid(grid, dimensions[0], dimensions[1]);
		//printf("\n");

		//MPI_Barrier(MPI_COMM_WORLD);
		MPI_Send(grid, dimensions[0] * dimensions[1], MPI_INT, 0, 123, MPI_COMM_WORLD);

		free(grid);
	}

	MPI_Finalize();
	return 0;
}

int* create_random_initial_population(int width, int height)
{

    int *grid = malloc(width * height * sizeof(int));

    int i = 0;

    int count = 0;
    
    for(i=0; i<width * height; i++)
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

    return grid;
}

void print_grid(int *grid, int width, int height)
{
    /* This function iterates over the grid and prints it in a matricial fashion. */
    
    int i, j;
    for(i=0; i<height; i++)
    {
        for(j=0;j<width;j++)
        {
            if(grid[(i * width) + j] == 1)
                printf("@");
            else
                printf(" ");
        }

        printf("\n");
    }

    printf("\n");

}

int count_neighbors(int *grid, int x, int width, int height)
{
    /* This functions counts how many neighbors
       equal to 1 a cell has (in all 8 directions!). */

    int count = 0;

    // Checking for the East Neighbor.
    if(x % width != width - 1)
    {
        if(grid[x + 1] == 1)
        {
            count++;
        }
    }

    // Checking for the West Neighbor.
    if(x % width != 0)
    {
        if(grid[x - 1] == 1)
        {
            count++;
        }
    }

    // Checking for the North Neighbor.
    if(x - width >= 0)
    {
        if(grid[x - width] == 1)
        {
            count++;
        }

        // Checking for the Northwest Neighbor.
        if((x - width - 1) % width != width - 1  
                && x - width - 1 >= 0)
        {
            if(grid[x - width - 1] == 1)
            {
                count++;
            }
                
        }

        // Checking for the Northeast Neighbor.
        if((x - width + 1) % width != 0)
        {
            if(grid[x - width + 1] == 1)
            {
                count++;
            }
                
        }
    }

    // Checking for the South Neighbor.
    if(x + width < (width * height))
    {
        if(grid[x + width] == 1)
        {
            count++;
        }
            
        // Checking for the Southwest Neighbor.
        if((x + width - 1) % width != width - 1)
        {
            if(grid[x + width - 1])
            {
                count++;
            }
                
        }

        // Checking for the Southeast Neighbor.
        if((x + width + 1) % width != 0 
                && x + width + 1 < (width * height))
        {
            if(grid[x + width + 1])
            {
                count++;
            }
                
        }
    }
    return count;
}

int * apply_cave_generation_rule(int *grid, int width, int height)
{
    int* next_gen = malloc ((width * height) * sizeof(int));

    int i;

    int n_count = 0;

    for(i=0; i<(width * height); i++)
    {
        n_count = count_neighbors(grid, i, width, height);

        
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
    free(grid);
    return next_gen;
}

void fill_borders(int *grid, int width, int height)
{
	int i;
	int x, y;

	for(i=0; i < (width * height); i++)
	{
		x = i % width;
        y = i / width;

        if(x == 0 || x == width-1)
			grid[i] = 1;

		if(y == 0 || y == height-1)
			grid[i] = 1;
	}
}
