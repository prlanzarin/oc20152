#ifndef DINING_SEM
#define DINING_SEM

#define AVAILABLE 0 
#define BUSY 1

typedef struct {
	char state;
} philosopher_t;

typedef struct {
	int id;
} params_t;

void initializeCVars();
void startThreads ();
void *dinnerTime (void *params);
void thinking (int nThread);
void eating (int nThread);
void hungry (int nThread);
void printStates();

#endif

