#ifndef DINING_SEM
#define DINING_SEM

typedef struct {
	char state;
} philosopher;

void initializeSemaphores(sem_t *forks, int numberForks);

#endif

