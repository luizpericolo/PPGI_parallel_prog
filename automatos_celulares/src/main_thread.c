#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N_THREADS 8

#define N_ITER 5

#define GRID_WIDTH 110
#define GRID_HEIGHT 32
#define CELL_COUNT GRID_WIDTH * GRID_HEIGHT
#define FILL_PROB 45

#include <sys/time.h>
#include <time.h>

typedef union{
    unsigned long long int64;
    struct{
        unsigned int lo, hi;
    } int32;
} tsc_counter;

#define RDTSC(cpu_c)             \
__asm__ __volatile__("rdtsc" : \
    "=a" ((cpu_c).int32.lo),  \
    "=d"((cpu_c).int32.hi) )

typedef struct pthread_params {
	int id;
	/*
	int *born;
	int n_born;
	int *survive;
	int n_survive;
	*/
} pthread_params;

void print_grid(int *grid);
void simple_print_grid(int *grid);
void *transition_cells(void *thread_params);
int count_neighbors(int *grid, int x);
int* create_random_initial_population();
void print_name(int tid);
void apply_cave_generation_rule(int *grid, int startPos, int endPos);
void fill_borders(int *grid);

int *current_gen;
int *next_gen;
int n_changes;

void print_name(int tid)
{
	printf("Hi! I'm a thread and my name is %d\n", tid);
}

int count_neighbors(int *grid, int x)
{
    /* This functions counts how many neighbors equal to 1 a cell has (in all 8 directions!). */

    int count = 0;

    // Checking for the East Neighbor.
    if(x % GRID_WIDTH != GRID_WIDTH - 1)
    {
        
        if(grid[x + 1] == 1)
        {
            count++;
        }
    }

    // Checking for the West Neighbor.
    if(x % GRID_WIDTH != 0)
    {
        
        if(grid[x - 1] == 1)
        {
            count++;
        }
    }

    // Checking for the North Neighbor.
    if(x - GRID_WIDTH >= 0)
    {
        
        if(grid[x - GRID_WIDTH] == 1)
        {
            count++;
        }

        // Checking for the Northwest Neighbor.
        if((x - GRID_WIDTH - 1) % GRID_WIDTH != GRID_WIDTH - 1  && x - GRID_WIDTH - 1 >= 0)
        {
            
            if(grid[x - GRID_WIDTH - 1] == 1)
            {
                count++;
            }
                
        }

        // Checking for the Northeast Neighbor.
        if((x - GRID_WIDTH + 1) % GRID_WIDTH != 0)
        {
            
            if(grid[x - GRID_WIDTH + 1] == 1)
            {
                count++;
            }
                
        }
    }

    // Checking for the South Neighbor.
    if(x + GRID_WIDTH < CELL_COUNT)
    {
        
        if(grid[x + GRID_WIDTH] == 1)
        {
            count++;
        }
            

        // Checking for the Southwest Neighbor.
        if((x + GRID_WIDTH - 1) % GRID_WIDTH != GRID_WIDTH - 1)
        {
            
            if(grid[x + GRID_WIDTH - 1])
            {
                count++;
            }
                
        }

        // Checking for the Southeast Neighbor.
        if((x + GRID_WIDTH + 1) % GRID_WIDTH != 0 && x + GRID_WIDTH + 1 < CELL_COUNT)
        {
            
            if(grid[x + GRID_WIDTH + 1])
            {
                count++;
            }
                
        }
    }
    return count;
}

void fill_borders(int *grid)
{
	int i;
	int x, y;

	for(i=0; i < CELL_COUNT; i++)
	{
		x = i % GRID_WIDTH;
        y = i / GRID_WIDTH;

        if(x == 0 || x == GRID_WIDTH-1)
			grid[i] = 1;

		if(y == 0 || y == GRID_HEIGHT-1)
			grid[i] = 1;
	}
}

void *transition_cells(void *thread_params)
{
	pthread_params *params = (pthread_params*) thread_params;

	int n_elements = CELL_COUNT / N_THREADS;

	int start = n_elements * (params->id);
	int end = start + n_elements;

	apply_cave_generation_rule(current_gen, start, end);
	
	free(params);

	pthread_exit(NULL);
}

void apply_cave_generation_rule(int *grid, int startPos, int endPos)
{

    int i;

    int n_count = 0;

    for(i=startPos; i<endPos; i++)
    {
        n_count = count_neighbors(grid, i);

        // Applying the B678 rule.
        if(grid[i] == 0)
        {
            if((n_count == 6) || (n_count == 7) || (n_count == 8))
                next_gen[i] = 1;
				n_changes++;
            else
                next_gen[i] = grid[i];
        }

        // Applying the S345678
        if(grid[i] == 1)
        {
            if((n_count == 0) || (n_count == 1) || (n_count == 2))
                next_gen[i] = 0;
				n_changes++;
            else
                next_gen[i] = grid[i];
        }
    }
}

void print_grid(int *grid)
{
    /* This function iterates over the grid and prints it in a matricial fashion. */
    
    int i, j;
    for(i=0; i<GRID_HEIGHT; i++)
    {
        for(j=0;j<GRID_WIDTH;j++)
        {
        	if(grid[(i * GRID_WIDTH) + j] == 1)
            	printf("@");
           	else
           		printf(".");
        }

        printf("\n");
    }

    printf("\n");

}

void simple_print_grid(int *grid)
{
    /* This function iterates over the grid and prints it in a vectorial fashion. */
    int i;

    for(i=0; i<CELL_COUNT; i++)
    {
    	printf("%d", grid[i]);
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
	int n_iter = 0;
	struct timeval inicio, fim;
    tsc_counter tsc1, tsc2;
    long long unsigned int clock;
    double tempo;

    printf("(%d, %d, %d)\n\n", N_ITER, GRID_WIDTH, GRID_HEIGHT);

    /*
    gettimeofday(&inicio, NULL);
    RDTSC(tsc1); 
    */

	current_gen = create_random_initial_population();
	next_gen = malloc(CELL_COUNT * sizeof(int));
	fill_borders(current_gen);
	//print_grid(current_gen);	

	int n;
	//for(n=0; n<N_ITER; n++)
	// Setando um valor != 0 pra nao falhar logo no primeiro loop do while.
	n_changes = -1;
	while(n_changes != 0)
	{
        n_changes = 0;
		n_iter++;
		for(t=0; t<N_THREADS; t++)
		{
			pthread_params *params;
			params = malloc(sizeof(pthread_params));
			params->id = t;
			/*
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
			*/
			
			pthread_create(&tid[t], NULL, transition_cells, (void*) params);
		}

		for(t=0; t<N_THREADS; t++)
		{
			pthread_join(tid[t], NULL);

        }

		current_gen = next_gen;
		fill_borders(current_gen);
        print_grid(current_gen);
		
	}

	/*
    RDTSC(tsc2);
	gettimeofday(&fim, NULL);

 	tempo = (fim.tv_sec - inicio.tv_sec) * 1000 + (fim.tv_sec - inicio.tv_sec)/1000;
    printf("Tempo: %.2lf\n", tempo);

    clock = tsc2.int64 - tsc1.int64;
    printf("Tempo: %.2lf(ms) Clocks: %.2e\n", tempo/N_ITER, (double)clock/N_ITER);
    printf("Clock/tempo: %.2e\n\n", clock/tempo);

    print_grid(current_gen);
    */
	
	print ("Number of Iterations until stop: %d", n_iter);
	pthread_exit(NULL);
}
