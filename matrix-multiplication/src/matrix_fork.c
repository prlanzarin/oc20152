#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */
#include "../include/matrix.h" /* matrix basic operations */
#include "../include/parser.h" /* matrix parser utilities */

#define FILEIN_1 "in1.txt"
#define FILEIN_2 "in2.txt"
#define FILEOUT "out.txt"

MATRIX *MAT_ONE, *MAT_TWO, *MAT_OUT; // global matrixes to operate upon
int NOF_PROC; // number of processes passed as argument via terminal

int main(int argc, char *argv[]) {
	int i, j;
	pid_t pid;

	sscanf(argv[1], "%d", &NOF_PROC);

	if(NOF_PROC <= 0) {
		printf("ERROR: invalid number of processes\n");
		exit(-1);
	}

	MAT_ONE = MATRIX_new(parser_rows(FILEIN_1), parser_cols(FILEIN_1));
	parser_matrix(FILEIN_1, MAT_ONE);

	MAT_TWO = MATRIX_new(parser_rows(FILEIN_2), parser_cols(FILEIN_2));
	parser_matrix(FILEIN_2, MAT_TWO);

	for(i = 0; i < NOF_PROC; i++) {
		pid = fork();
		if(pid == 0) {
			/* it's a child process	*/
			printf("CHILD!\n");
		}
		else {
			/* it's a parent process */
			printf("FATHER!\n");
			printf("PARSED MATRIX: \n");
			for(i = 0; i < MAT_ONE->r; i++) {
				for(j = 0; j < MAT_ONE->c; j++)
					printf("%d ", MAT_ONE->matrix[i][j]);
				printf("\n");
			}

			printf("PARSED MATRIX (2): \n");
			for(i = 0; i < MAT_TWO->r; i++) {
				for(j = 0; j < MAT_TWO->c; j++)
					printf("%d ", MAT_TWO->matrix[i][j]);
				printf("\n"); 
			} 
		}
	}
	
	MATRIX_free(MAT_ONE);
	MATRIX_free(MAT_TWO);
	return 0;
}
