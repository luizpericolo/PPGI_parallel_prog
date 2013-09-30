#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct _Transform2D Transform2D;
typedef struct _Dancer Dancer;
struct _Transform2D
{
	int x;
	int y;
};

struct _Dancer
{
	int id;
	Transform2D position;
	//Dancer partner;
	//Dancer enemy;
};


int random_range(int min, int max);
Dancer choose_random_dance(int dancer_id);

/* The number of dancers that will be taking part in the dance.  */
int N_DANCERS = 10;

/* The number of iterations (steps) that will be run to produce data output.  */
int N_ITERATIONS = 5;

Dancer *dancers;

int main(void)
{
	/* Initializing random seed.  */
	srand(time(NULL));
	
	dancers = malloc(N_DANCERS * sizeof(Dancer));

	Dancer aux_dancer;

	int i;
	for(i = 0; i < N_DANCERS; i++)
	{
		aux_dancer.position.x = random_range(1, 10);
		aux_dancer.position.y = random_range(1, 10);
		aux_dancer.id = i;

		printf("Dancer %d created![X: %d, Y: %d]\n", aux_dancer.id, aux_dancer.position.x, aux_dancer.position.y);
		dancers[i] = aux_dancer;
	}


	return 1;
}

Dancer choose_random_dance(int dancer_id)
{
	/* This function chooses a random dancer from the dancefloor excluding the dancer whose id is passed as an argument. */

	int rnd_index = dancer_id;

	while(rnd_index == dancer_id)
	{
		rnd_index = random_range(0, N_DANCERS);
	}

	return dancers[rnd_index];

}

int random_range(int min, int max)
{
	return (int)rand() % max + min;
}
