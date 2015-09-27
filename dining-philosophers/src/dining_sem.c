#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> //sleep
#include "../include/dining_sem.h"

int numberPhilosophers;
sem_t *forks;
sem_t *lock;
pthread_t *threads; //Philosophers are modelled as threads
philosopher_t *philosophers;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

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

        //There are N forks for N philosophers -> allocate the forks' semaphore
        forks = malloc (sizeof(sem_t) * numberPhilosophers);

	//Allocate the structure to store the philosophers' state
	philosophers = malloc (sizeof(philosopher_t) * numberPhilosophers);

	//Allocate corresponding threads
	threads = malloc(sizeof(pthread_t)*numberPhilosophers);	

	//This semaphore will ensure no more than (numberPhilosophers-1) philosophers are trying to acquire the forks
        lock = malloc (sizeof(sem_t));

	initializeSemaphores();
	startThreads();

	for(k = 0; k < numberPhilosophers; k++) {
		pthread_join(threads[k], NULL);
	}
	
	return 0;
}

void initializeSemaphores()
{
	int k; 
	for (k = 0; k < numberPhilosophers; k++) //N forks for N philosophers
		sem_init (&forks[k], 0, 1); //0 means the semaphore shared between threads. 1 because it is a binary semaphore
	sem_init(lock, 0, (numberPhilosophers-1));
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

void *dinnerTime(void *params)
{
	int i;
	params_t self = *(params_t *)params;
	while(1)
	{
		for(i = 0; i < 3; i++) {
			thinking(self.id);
			sem_wait(lock); //No more than (numberPhilosophers-1) may pass this semaphore
			hungry(self.id);
			sem_wait(&forks[self.id]); //Checking both forks
			sem_wait(&forks[(self.id + 1) % numberPhilosophers]);
			eating(self.id);
			pthread_mutex_lock(&mutex);
			sem_post(&forks[self.id]);
			sem_post(&forks[(self.id + 1) % numberPhilosophers]);
			sem_post(lock);
			philosophers[self.id].state = 'T';
			printStates();
			pthread_mutex_unlock(&mutex);
		}
	}
}

void thinking(int nThread) //Philosopher is now thinking, meaning he doesn't want to acquire the forks
{
	int thinkingTime = (rand() % 10) + 1;

	pthread_mutex_lock (&mutex); //Now entering critical section
	philosophers[nThread].state = 'T';
	printStates();
	pthread_mutex_unlock (&mutex);
	sleep (thinkingTime); //Wait for a random interval between 1 and 10 seconds
}

void eating(int nThread)
{
	int eatingTime = (rand() % 10) + 1;

	pthread_mutex_lock (&mutex); //Now entering critical section
	philosophers[nThread].state = 'E';
	printStates();
	pthread_mutex_unlock (&mutex);
	sleep (eatingTime); //Wait for a random interval between 1 and 10 seconds
}

void hungry(int nThread) //Philosopher with id == nThread is now hungry (trying to acquire the forks)
{
	pthread_mutex_lock (&mutex); //Now entering critical section
	philosophers[nThread].state = 'H';
	printStates();
	pthread_mutex_unlock (&mutex);
}

void printStates()
{
	int k;
	for (k = 0; k < numberPhilosophers; k++)
	{
		printf ("%c ", philosophers[k].state);
		if (k == (numberPhilosophers - 1) )
			printf ("\n");
	}
}
