#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <cuda.h>
#include <curand_kernel.h>

__global__ void generate_map(curandState* devState, int n_maps, int* grid, int width, int height);
__global__ void setup_rnd_kernel (curandState* state, unsigned long seed);

__device__ void apply_cave_generation_rule();
__device__ void create_random_initial_population(curandState* devState, int* grid, int width, int height, int fill_percent);
__device__ int rand(curandState* localRand, int max);

__device__ void pretty_print_map(int* map, int width, int height);

__global__ void generate_map(curandState* devState, int n_maps, int* grid, int width, int height)
{
	int i;

	/* Literature says so... */
	int n_iterations = 5;

	/*
		This is the kernel function
	*/

	create_random_initial_population(devState, grid, width, height, 45);

	pretty_print_map(grid, width, height);

	/*pthread_params *params = (pthread_params*) thread_params;

	int n_elements = CELL_COUNT / N_THREADS;

	int start = n_elements * (params->id);
	int end = start + n_elements;

	apply_cave_generation_rule(current_gen, start, end);
	
	free(params);

	pthread_exit(NULL);*/

	

	

//	printf("[BlockId]: %d, [ThreadId]: %d\n", blockIdx.x, threadIdx.x);

}

__global__ void setup_rnd_kernel (curandState* state, unsigned long seed)
{
    int id = blockIdx.x*blockDim.x + threadIdx.x;
    curand_init ( seed, id, 0, &state[id] );
} 


__device__ void apply_cave_generation_rule()
{
   /* int i;

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
    }*/
}

__device__ void create_random_initial_population(curandState* devState, int* grid, int width, int height, int fill_percent)
{
	/* This function creates a grid with a random distribution of 1 and 0 cells given width, height and a fill_percentage. */
    int i = 0;

    int count = 0;

    int cell_count = width * height;

    for(i=0; i<cell_count; i++)
    {
        if(rand(devState, 100) < fill_percent)
        {
            grid[i] = 1;
            count++;
        }
        else
        {
            grid[i] = 0;
        }
            
    }

}

__device__ int rand(curandState* localRand, int max) 
{
    int ind = threadIdx.x;
    curandState localState = localRand[ind];
    float rnd = curand_uniform( &localState );
    localRand[ind] = localState;
    
    return int(rnd * max);
}

__device__ void pretty_print_map(int* map, int width, int height)
{
	int i;

	for(i=0; i<width*height; i++)
	{
		if(i%width == 0)
			printf("\n");
		
		if(map[i] == 0)
			printf(".");

		if(map[i] == 1)
			printf("@");
	}

	printf("\n");
}

int main(int argc, char* argv[])
{
	
	int *cudaGrid, *grid;
	curandState* devStates;

    srand(time(NULL));
	
	/*int i, n, t, s;

	struct timeval inicio, fim;
    tsc_counter tsc1, tsc2;
    long long unsigned int clock;
    double tempo, tempo_total;*/

    int N_THREADS, N_BLOCKS;

    N_THREADS = 1;
    N_BLOCKS = 1;

    int n_maps = 5;

    int width, height;

    width = 10;
    height = 10;

    cudaMalloc(&devStates, N_THREADS * N_BLOCKS * sizeof( curandState ));
  	setup_rnd_kernel <<<N_THREADS, N_BLOCKS>>> ( devStates, time(NULL) );


	if (cudaMalloc (&cudaGrid, sizeof(int) * width * height) != cudaSuccess) 
		{ printf("Erro cudaMalloc\n"); return -1; }

	grid = (int*) malloc(width * height * sizeof(int));

    generate_map <<<N_THREADS, N_BLOCKS>>>(devStates, n_maps, cudaGrid, width, height);
    cudaDeviceSynchronize();

    if (cudaMemcpy(grid, cudaGrid, sizeof(int) * width*height, cudaMemcpyDeviceToHost) != cudaSuccess) 
       { printf("Erro cudaMemcpy\n"); return -1; }

    printf("Depois de chamar!\n");

    int i;
    for(i=0; i<width*height; i++)
	{
		if(i%width == 0)
			printf("\n");
		
		if(grid[i] == 0)
			printf(".");

		if(grid[i] == 1)
			printf("@");
	}

	printf("\n");

    /*for(s=0; s<N_SIM; s++)
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
	
	pthread_exit(NULL);*/

	return 0;
}