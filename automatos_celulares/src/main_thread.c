#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

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

/* Simulation Variables: */
int N_THREADS;// 8

int N_ITER; //5
int N_MAPS;// 500

int GRID_WIDTH;// 110
int GRID_HEIGHT;// 32
int CELL_COUNT;// GRID_WIDTH * GRID_HEIGHT
int FILL_PROB;// 45
int N_SIM;

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


int main(int argc, char* argv[])
{
	/* 
		This implementation creates N_THREADS threads for each iteration of the algorithm.
		This works as a 'default' barrier implementation. We wait for all threads to exit before we start
		the next iteration of the algorithm, so we can say that the algorithm implements a natural synchronization.
	 */

    if(argc < 7)
    {
        printf("[Error]\n");
        printf("Useage: %s <n_threads> <n_sim> <n_maps> <grid_width> <grid_height> <fill_prob>\n", argv[0]);
        return 1;
    }
    else
    {
        N_THREADS = atoi(argv[1]);
        N_SIM = atoi(argv[2]);
        N_MAPS = atoi(argv[3]);
        GRID_WIDTH = atoi(argv[4]);
        GRID_HEIGHT = atoi(argv[5]);
        FILL_PROB = atoi(argv[6]);

        CELL_COUNT = GRID_WIDTH * GRID_HEIGHT;

        // Literature says so...
        N_ITER = 5;
    }


    srand(time(NULL));
	pthread_t tid[N_THREADS];
	int i, n, t, s;
	struct timeval inicio, fim;
    tsc_counter tsc1, tsc2;
    long long unsigned int clock;
    double tempo, tempo_total;

    printf("(%d, %d, %d)\n\n", N_ITER, GRID_WIDTH, GRID_HEIGHT);

    for(s=0; s<N_SIM; s++)
    {
        gettimeofday(&inicio, NULL);
        RDTSC(tsc1); 

        for(i=0; i<N_MAPS; i++)
        {
            current_gen = create_random_initial_population();
        	next_gen = malloc(CELL_COUNT * sizeof(int));
        	fill_borders(current_gen);

        	for(n=0; n<N_ITER; n++)
        	{
        		for(t=0; t<N_THREADS; t++)
        		{
        			pthread_params *params;
        			params = malloc(sizeof(pthread_params));
        			params->id = t;

        			pthread_create(&tid[t], NULL,
                        transition_cells, (void*) params);
        		}

        		for(t=0; t<N_THREADS; t++)
        		{
        			pthread_join(tid[t], NULL);

                }

        		current_gen = next_gen;
        		fill_borders(current_gen);
                //print_grid(current_gen);
        		
        	}

            //printf("Mapa #%d:\n", i+1);
            //print_grid(current_gen);
            free(current_gen);
            //free(next_gen);
        }

        RDTSC(tsc2);
        gettimeofday(&fim, NULL);

        printf("Run #%d\n", s);
        tempo = (fim.tv_sec - inicio.tv_sec) * 1000 + (fim.tv_sec - inicio.tv_sec)/1000;
        tempo_total += tempo;
        printf("Tempo: %.2lf\n", tempo);

        clock = tsc2.int64 - tsc1.int64;
        printf("Tempo: %.2lf(ms) Clocks: %.2e\n", tempo/N_MAPS, (double)clock/N_ITER);
        printf("Clock/tempo: %.2e\n\n", clock/tempo);
    }

    printf("Tempo Total: %.2lf\n", tempo_total);
    printf("Tempo médio: %.2lf\n", (double) tempo_total/N_SIM);
	
	pthread_exit(NULL);
}
