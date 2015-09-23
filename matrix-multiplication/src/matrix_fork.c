#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */
#include <sys/shm.h> /* shared memory lib */
#include <sys/stat.h> 
#include "../include/matrix.h" /* matrix basic operations */
#include "../include/parser.h" /* utilities */

#define FILEIN_1 "in1.txt"
#define FILEIN_2 "in2.txt"
#define FILEOUT "out.txt"

/* shared memory globals */
int segment_id;
char *shm_addr;
size_t SHM_SIZE; // shared memory block size

MATRIX *MAT_ONE, *MAT_TWO; // global matrixes to operate upon
int NOF_PROC; // number of processes passed as argument via terminal
int ROWS_PER_FORK; // number of rows to be multiplied by each process
pid_t *pids; // spawned processes identifiers

void child_process(void);

void parent_process(void);

int main(int argc, char *argv[]) {
	int proc_counter, row_counter;
	pid_t pid;
	MATRIX *MAT_OUT;

	/* Allocating new matrixes to be multiplied. Functions are defined
	 * in matrix.h. UTILS_parse_rows/cols are responsible for gathering
	 * matrixes sizes, defined in utils.c */ 
	MAT_ONE = MATRIX_new(parser_rows(FILEIN_1), parser_cols(FILEIN_1));
	parser_matrix(FILEIN_1, MAT_ONE);

	MAT_TWO = MATRIX_new(parser_rows(FILEIN_2), parser_cols(FILEIN_2));
	parser_matrix(FILEIN_2, MAT_TWO);
	
	if(!(MATRIX_is_multipliable(MAT_ONE, MAT_TWO))) {
		fprintf(stderr, "ERROR: invalid matrixes sizes.\n");
		exit(EXIT_FAILURE);
	}

	/* getting number of process passed as argument. Gets the lowest
	 * value between the argument and MAT_ONE number of rows as the
	 * number of process to be spawned */	
	NOF_PROC = UTILS_get_args(argc, argv);
	NOF_PROC = MIN(NOF_PROC, MAT_ONE->r);
	pids = (pid_t *)malloc(sizeof(pid_t) * NOF_PROC);	

	/* shared-memory segment creation and attachment. Read/Write */
	SHM_SIZE = (MAT_ONE->r * sizeof(int *) + 
			MAT_ONE->r * MAT_TWO->c * sizeof(int) +
			sizeof(MATRIX)); // sizeof MAT_OUT
	segment_id = shmget(IPC_PRIVATE, SHM_SIZE, S_IRUSR | S_IWUSR);
	shm_addr = shmat(segment_id, NULL, 0);
	MAT_OUT = (MATRIX *) shm_addr;
	MAT_OUT->r = MAT_ONE->r; MAT_OUT->c = MAT_TWO->c;
	
	/* spawns NOF_PROC - 1 processes (because we already have a main
	 * process running */
	for(proc_counter = 0; proc_counter < NOF_PROC - 1; proc_counter++) {
		pid = fork();

		if(pid < 0) {
			fprintf(stderr, "ERROR: unable to fork process.\n");
			exit(EXIT_FAILURE);
		}

		if(pid == 0) {
			shm_addr = shmat(segment_id, NULL, 0);
			MAT_OUT = (MATRIX *) shm_addr;
			break;	//it's a child process, we record its id
				// and prevent it from spawning more processes
		}
	
		pids[proc_counter] = pid;
	}

	for(row_counter = proc_counter; row_counter < MAT_OUT->c; row_counter += NOF_PROC) {
		MATRIX_line_multiply(MAT_OUT, MAT_ONE, MAT_TWO, row_counter);
		printf("MULTIPLIED LINE %d\n in PROCESS %d\n", row_counter, proc_counter);
	}	
	
	shmdt(MAT_OUT);

	MATRIX_free(MAT_ONE);
	MATRIX_free(MAT_TWO);
	return 0;
}
