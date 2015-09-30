#ifndef DINING_SEM
#define DINING_SEM

typedef struct {
	char state;
        int prio;
} philosopher_t;

typedef struct {
	int id;
} params_t;

void initializeSemaphores();
void startThreads ();
void *dinnerTime (void *params);
void thinking (int nThread);
void eating (int nThread);
void hungry (int nThread);
void printStates();

#endif

