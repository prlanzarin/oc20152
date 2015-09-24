#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int segment_id; // allocated shm segment id
int **shm_mat; // pointer to 2D array representing a MATRIX->matrix
char *shm_addr; // pointer to start of shm block
size_t SHM_SIZE; // shm block size

MATRIX *MAT_ONE, *MAT_TWO, *MAT_OUT; // global matrixes to operate upon
int NOF_PROC; // number of processes passed as argument via terminal
pid_t *pids; // spawned processes identifiers

void terminate(void);

int main(int argc, char *argv[]) {
	int proc_counter, row_counter, status, i;
	pid_t pid;

	/* Allocating new matrixes to be multiplied. Functions are defined
	 * in matrix.h. UTILS_parse_rows/cols are responsible for gathering
	 * matrixes sizes, defined in utils.c */ 
	MAT_ONE = MATRIX_new(parser_rows(FILEIN_1), parser_cols(FILEIN_1));
	parser_matrix(FILEIN_1, MAT_ONE);

	MAT_TWO = MATRIX_new(parser_rows(FILEIN_2), parser_cols(FILEIN_2));
	parser_matrix(FILEIN_2, MAT_TWO);
	
	MAT_OUT = MATRIX_new(MAT_ONE->r, MAT_TWO->c);

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
	SHM_SIZE = (MAT_ONE->r * MAT_TWO->c * sizeof(int)); // sizeof MAT_OUT
	segment_id = shmget(IPC_PRIVATE, SHM_SIZE, S_IRUSR | S_IWUSR);
	shm_mat = (int **)shmat(segment_id, (void *) 0, 0);
	
	/* spawns NOF_PROC - 1 processes (because we already have a main
	 * process running */
	for(proc_counter = 0; proc_counter < NOF_PROC - 1; proc_counter++) {
		pid = fork();
		if(pid < 0) {
			fprintf(stderr, "ERROR: unable to fork process.\n");
			exit(EXIT_FAILURE);
		}
		if(pid == 0) {
			shm_mat = (int **)shmat(segment_id, NULL, 0);
			break;	//it's a child process, we record its id
				// and prevent it from spawning more processes
		}
		pids[proc_counter] = pid;
	}

	for(row_counter = proc_counter; row_counter < MAT_OUT->r; row_counter += NOF_PROC) {
		MATRIX_line_multiply(MAT_OUT, MAT_ONE, MAT_TWO, row_counter);
		/* Copying multiplied lines to shared memory 2d array */
		memcpy(&shm_mat[row_counter * MAT_OUT->c],
			       	&MAT_OUT->matrix[row_counter][0],
				(sizeof(int) * MAT_OUT->c));
	}

	if(proc_counter != NOF_PROC - 1) {
		terminate(); // it's a child process; after multiplication
		return 0;	// we should terminate it
	}
	else
		for(i = 0; i < NOF_PROC - 1; i++) // it's a parent processs
			waitpid(pids[i], &status, 0); // wait for children
	/* recopying shm 2D array to MATRIX pointer */
	for(i = 0; i < MAT_OUT->r; i++) 
		memcpy(&MAT_OUT->matrix[i][0],
				&shm_mat[i * MAT_OUT->c], 
				sizeof(int) * MAT_OUT->c);
	/* write to file and we're done */
	UTILS_write_matrix(FILEOUT, MAT_OUT);
	terminate();
	return 0;
}

void terminate(void) {
	shmdt(shm_mat);
	shmctl(segment_id, IPC_RMID, NULL);
	MATRIX_free(MAT_ONE);
	MATRIX_free(MAT_TWO);
	MATRIX_free(MAT_OUT);
}
