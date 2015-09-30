#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/matrix.h"
#include "../include/utils.h"

MATRIX *MAT_ONE, *MAT_TWO, *MAT_OUT; // global matrixes to operate upon
int NOF_THREADS; // number of processes passed as argument via terminal
pthread_t * threads;
int *t_ids;

void *multiplica(void *t_id) {
	int i, start_row = *(int *)t_id; // thread ID

	for(i = start_row; i < MAT_ONE->r; i += NOF_THREADS) 
		MATRIX_line_multiply(MAT_OUT, MAT_ONE, MAT_TWO, i);
	
	pthread_exit(0);
}

int main(int argc, char *argv[]) {

	int i,flag;

	NOF_THREADS = UTILS_get_args(argc, argv);

	MAT_ONE = MATRIX_new(UTILS_parse_rows(FILEIN_1), UTILS_parse_cols(FILEIN_1));
	UTILS_parse_matrix(FILEIN_1, MAT_ONE);

	MAT_TWO = MATRIX_new(UTILS_parse_rows(FILEIN_2), UTILS_parse_cols(FILEIN_2));
	UTILS_parse_matrix(FILEIN_2, MAT_TWO);

	if(!(MATRIX_is_multipliable(MAT_ONE, MAT_TWO))) {
		fprintf(stderr, "ERROR: invalid matrixes sizes.\n");
		exit(EXIT_FAILURE);
	}

	MAT_OUT = MATRIX_new(MAT_ONE->r, MAT_TWO->c);

	NOF_THREADS = MIN(NOF_THREADS, MAT_ONE->r);

	threads = (pthread_t *) malloc(sizeof(pthread_t) * NOF_THREADS);
	t_ids = (int *) malloc(sizeof(int) * NOF_THREADS);
	pthread_attr_t atributos;
	pthread_attr_init(&atributos);
	pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);
	pthread_attr_setscope(&atributos,PTHREAD_SCOPE_SYSTEM);

	//Distributing the work.
	for (i = 0; i < NOF_THREADS; i++){
		t_ids[i] = i; // thread ID like in fork version to fetch start row
		flag = pthread_create(&threads[i], NULL, 
				(void *(*) (void *)) multiplica, (void *)&t_ids[i]);
		if (flag)
			exit(-1);
	}

	//join all threads
	for (i = 0; i < NOF_THREADS; i++)
		pthread_join(threads[i], NULL);

	//write the matrix
	UTILS_write_matrix(FILEOUT, MAT_OUT);
	//free all matrix
	MATRIX_free(MAT_ONE);
	MATRIX_free(MAT_TWO);
	MATRIX_free(MAT_OUT);

	return 0;
}
