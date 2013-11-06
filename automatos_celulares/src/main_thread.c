#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N_THREADS 1

#define N_ITER 5

#define GRID_WIDTH 8
#define GRID_HEIGHT 8
#define CELL_COUNT GRID_WIDTH * GRID_HEIGHT
#define FILL_PROB 45

typedef struct pthread_params {
	int id;
	int *born;
	int n_born;
	int *survive;
	int n_survive;
} pthread_params;

void print_grid(int *grid);
void *PrintSomething(void *threadid);
int* create_random_initial_population();
void print_name(int tid);

int *current_gen;
int *next_gen;

void print_name(int tid)
{
	printf("Hi! I'm a thread and my name is %d\n", tid);
}

void *transition_cells(void *thread_params)
{
	pthread_params *params = (pthread_params*) thread_params;

	int n_elements = CELL_COUNT / N_THREADS;

	int start = n_elements * (params->id);
	int end = start + n_elements;

	print_name(params->id);
	int i;

	next_gen = current_gen;

	for(i=start; i<end; i++)
	{
	}

	printf("--Thread %d terminou.\n", params->id);
	
	free(params);

	pthread_exit(NULL);
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
    return grid;
}


int main(void)
{
	/* 
		This implementation creates N_THREADS threads for each iteration of the algorithm.
		This works as a 'default' barrier implementation. We wait for all threads to exit before we start
		the next iteration of the algorithm, so we can say that the algorithm implements a natural synchronization.
	 */
	pthread_t tid[N_THREADS];
	int t;

	current_gen = create_random_initial_population();
	next_gen = malloc(CELL_COUNT * sizeof(int));
	printf("First Generation: \n");
	print_grid(current_gen);

	int n;
	for(n=0; n<N_ITER; n++)
	{

		for(t=0; t<N_THREADS; t++)
		{
			pthread_params *params;
			params = malloc(sizeof(pthread_params));
			params->id = t;
			//B678
			params->n_born = 3;
			params->born = malloc(3 * sizeof(int));
			params->born[0] = 6;
			params->born[1] = 7;
			params->born[2] = 8;
			
			///S345678
			params->n_survive = 6;
			params->survive = malloc(4 * sizeof(int));
			params->survive[0] = 3;
			params->survive[1] = 4;
			params->survive[2] = 5;
			params->survive[3] = 6;
			params->survive[4] = 7;
			params->survive[5] = 8;
			
			pthread_create(&tid[t], NULL, transition_cells, (void*) params);
		}

		for(t=0; t<N_THREADS; t++)
		{
			pthread_join(tid[t], NULL);
		}

		// Using the last iteration's result as input for the next iteration.
		current_gen = next_gen;

		print_grid(current_gen);
	}

	pthread_exit(NULL);
}