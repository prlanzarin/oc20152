#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */
#include <sys/shm.h> /* shared memory lib */
#include <sys/stat.h> 
#include "../include/matrix.h" /* matrix basic operations */
#include "../include/parser.h" /* matrix parser utilities */

#define FILEIN_1 "in1.txt"
#define FILEIN_2 "in2.txt"
#define FILEOUT "out.txt"
#define NOF_ARGS 2

/* shared memory globals */
int segment_id;
int *shared_memory;
const size_t SHM_SIZE = 4096; // shared memory block size

MATRIX *MAT_ONE, *MAT_TWO, *MAT_OUT; // global matrixes to operate upon
int NOF_PROC; // number of processes passed as argument via terminal
int ROWS_PER_FORK; // number of rows to be multiplied by each process

void child_process(void);

void parent_process(void);

int main(int argc, char *argv[]) {
	int i;
	pid_t pid;

	if(argc == NOF_ARGS) {
		sscanf(argv[1], "%d", &NOF_PROC);
		if(NOF_PROC < 0) {
			fprintf(stderr, "ERROR: invalid number of processes.\n");
			exit(EXIT_FAILURE);
		}
	}
	else {
		fprintf(stderr,
			"ERROR: invalid number of arguments. EXPECTS n : integer.\n");
		exit(EXIT_FAILURE);
	}

	MAT_ONE = MATRIX_new(parser_rows(FILEIN_1), parser_cols(FILEIN_1));
	parser_matrix(FILEIN_1, MAT_ONE);

	MAT_TWO = MATRIX_new(parser_rows(FILEIN_2), parser_cols(FILEIN_2));
	parser_matrix(FILEIN_2, MAT_TWO);
	
	if(!(MATRIX_is_multipliable(MAT_ONE, MAT_TWO))) {
		fprintf(stderr, "ERROR: invalid matrixes sizes.\n");
		exit(EXIT_FAILURE);
	}

	MAT_OUT = MATRIX_new(MAT_ONE->r, MAT_TWO->c);

	/* shared-memory segment creation. Read/Write */
	segment_id = shmget(IPC_PRIVATE, SHM_SIZE, S_IRUSR | S_IWUSR);

	for(i = 0; i < NOF_PROC; i++) {
		pid = fork();

		if(pid < 0) {
			fprintf(stderr, "ERROR: unable to fork process.\n");
			exit(EXIT_FAILURE);
		}

		if(pid == 0)
			child_process(); //it's a child process
		else 
			parent_process(); //it's a parent process
	}
	
	MATRIX_free(MAT_ONE);
	MATRIX_free(MAT_TWO);
	return 0;
}

void child_process(void) {
	printf("CHILD!\n");
	shared_memory = (int *) shmat(segment_id, NULL, 0);
}

void parent_process(void) {
	printf("FATHER!\n");
	shared_memory = (int *) shmat(segment_id, NULL, 0);
}
