#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N_THREADS 4

#define GRID_WIDTH 8
#define GRID_HEIGHT 8
#define CELL_COUNT GRID_WIDTH * GRID_HEIGHT
#define FILL_PROB 45


void print_grid(int *grid);
void *PrintSomething(void *threadid);
int* create_random_initial_population();
void print_name(int tid);

int * current_gen;

void print_name(int tid)
{
	printf("Hi! I'm a thread and my name is %d\n", tid);
}

/* TO-DO: Passar uma struct aqui. */
void *PrintSomething(void *threadid)
{
	int *tid = (int*) threadid;

	int n_elements = CELL_COUNT / N_THREADS;

	int start = n_elements * (*tid);
	int end = start + n_elements;

	print_name(*tid);
	int i;
	for(i=start; i<end; i++)
	{
		printf("grid[%d]: %d\n", i, current_gen[i]);
	}

	printf("--Thread %d terminou.\n", *tid);
	
	free(tid);
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
	pthread_t tid[N_THREADS];
	int t;

	current_gen = create_random_initial_population();

	print_grid(current_gen);

	for(t=0; t<N_THREADS; t++)
	{
		int *id;
		id = malloc(sizeof(int));
		*id = t;
		pthread_create(&tid[t], NULL, PrintSomething, (void*) id);
	}

	for(t=0; t<N_THREADS; t++)
	{
		pthread_join(tid[t], NULL);
	}

	printf("--Thread principal terminou.\n");
	pthread_exit(NULL);
}