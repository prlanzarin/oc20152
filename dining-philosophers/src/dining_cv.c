#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h> // sleep
#include "../include/dining_cv.h"

int numberPhilosophers;
int philosophersSitting;
int *forkStatus;

pthread_t *threads; //Philosophers are modelled as threads
philosopher_t *philosophers;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexPrint = PTHREAD_MUTEX_INITIALIZER;
//Condition variables
pthread_cond_t seatsAvailable;
pthread_cond_t *forksAvailable;

int main(int argc, char *argv[])
{
	int k;

	if (argc < 2) 
	{
		fprintf (stderr, "call -number_of_philosophers\n");
		exit(-1);
	}
	
	numberPhilosophers = atoi(strtok(argv[1],"-")); //Removes the "-" character included in the call command
	printf ("n=%d\n",numberPhilosophers);

	
	//Allocate one fork for each of the numberPhilosopher philosophers
        forkStatus = malloc(sizeof(int) * numberPhilosophers);
	for (k = 0; k < numberPhilosophers; k++)
	{
		forkStatus[k] = AVAILABLE;
	}

	//Allocate the structure to store the philosophers' state
	philosophers = malloc (sizeof(philosopher_t) * numberPhilosophers);

	//Allocate corresponding threads
	threads = malloc(sizeof(pthread_t)*numberPhilosophers);	

	initializeCVars();
	startThreads();

	for(k = 0; k < numberPhilosophers; k++) {
		pthread_join(threads[k], NULL);
	}

	return 0;
}

void initializeCVars()
{
	int k; 
	forksAvailable = malloc(sizeof(pthread_cond_t) * numberPhilosophers);
	for (k = 0; k < numberPhilosophers; k++) 
		pthread_cond_init (&forksAvailable[k], NULL); 

	pthread_cond_init (&seatsAvailable, NULL);
}

void startThreads ()
{
	int k;
	for(k = 0; k < numberPhilosophers; k++) 
	{
		params_t *param = malloc(sizeof(params_t));
		param->id = k;
		pthread_create(&threads[k], NULL, dinnerTime, (void *)param);
	}
}

int canEat(int id) {
	
	int previous, next;	
	if (id == 0)
		previous = numberPhilosophers - 1;
	else
		previous = id - 1;

	next = (id + 1) % numberPhilosophers;

	if (philosophers[previous].prio < philosophers[id].prio || philosophers[next].prio < philosophers[id].prio) 
		return 0;
	else
		return 1;
}

void *dinnerTime(void *params)
{
	params_t self = *(params_t *)params;
	while(1)
	{		
		thinking(self.id);

		pthread_mutex_lock (&mutex);
		while(philosophersSitting == (numberPhilosophers-1)) //If the number of philosophers is equal to (n-1),
			pthread_cond_wait(&seatsAvailable, &mutex);  //the philosopher must wait until one seat is freed
		philosophersSitting++;
		pthread_mutex_unlock (&mutex);

		thinking (self.id); 
		hungry(self.id);

		if (!canEat(self.id))
		{
			philosophersSitting--;
			pthread_cond_signal (&seatsAvailable);	
		}
		else
		{		
			//The philosopher is already at the table, and is now hungry
			pthread_mutex_lock (&mutex2);			
			while(forkStatus[self.id] == BUSY) //Retest it everytime
				pthread_cond_wait (&forksAvailable[self.id], &mutex2);
			forkStatus[self.id] = BUSY;		
			
			while(forkStatus[(self.id+1)%numberPhilosophers] == BUSY) //Retest it everytime
				pthread_cond_wait (&forksAvailable[(self.id+1)%numberPhilosophers], &mutex2);
			forkStatus[(self.id+1)%numberPhilosophers] = BUSY;

			pthread_mutex_unlock (&mutex2);

			//At this point, the philosophers has acquired the two forks. It's time to eat
			eating (self.id);

			//Releasing the forks
			pthread_mutex_lock (&mutex2);
			pthread_mutex_lock (&mutex);
			forkStatus[self.id] = AVAILABLE;
			pthread_cond_signal (&forksAvailable[self.id]);	
			forkStatus[(self.id+1)%numberPhilosophers] = AVAILABLE;
			pthread_cond_signal (&forksAvailable[(self.id+1)%numberPhilosophers]);	
			philosophersSitting--;
			pthread_cond_signal (&seatsAvailable);	
			thinking (self.id);
		
			pthread_mutex_unlock (&mutex);
			pthread_mutex_unlock (&mutex2);
		}

	}
}

void thinking(int nThread) //Philosopher is now thinking, meaning he doesn't want to acquire the forks
{
	int thinkingTime = (rand() % 2) + 1;
	
	philosophers[nThread].state = 'T';
	printStates();
	usleep (thinkingTime); //Wait for a random interval between 1 and 10 seconds
}

void eating(int nThread)
{
	int eatingTime = (rand() % 2) + 1;

	philosophers[nThread].state = 'E';
	philosophers[nThread].prio++;
	printStates();

	usleep (eatingTime); //Wait for a random interval between 1 and 10 seconds
}

void hungry(int nThread) //Philosopher with id == nThread is now hungry (trying to acquire the forks)
{
	//Now entering critical section
	philosophers[nThread].state = 'H';
	printStates();
}

void printStates()
{
	int k;
	pthread_mutex_lock (&mutexPrint); 
	for (k = 0; k < numberPhilosophers; k++)
	{
		printf ("%c ", philosophers[k].state);
		if (k == (numberPhilosophers - 1) )
			printf ("\n");
	}

	pthread_mutex_unlock (&mutexPrint);

}
