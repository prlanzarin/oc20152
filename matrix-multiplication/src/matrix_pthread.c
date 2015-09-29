#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/matrix.h"
#include "../include/utils.h"

MATRIX *MAT_ONE, *MAT_TWO, *MAT_OUT; // global matrixes to operate upon
int NOF_PROC, currentRow=0; // number of processes passed as argument via terminal
pthread_t * threads;

/* Mutex for the currentRow. */
pthread_mutex_t mutex_Row = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t count_threshold_cv = PTHREAD_COND_INITIALIZER;

void *multiplica() {
	int myRow;
	while (1) {
		//Locking....
		pthread_mutex_lock(&mutex_Row);
		if (currentRow >= MAT_ONE->r) {
			pthread_mutex_unlock(&mutex_Row);
			//Unlocking.No more work to do
			pthread_exit(0);
		}
		//Row to do
		myRow = currentRow;
		currentRow++;
		// Thread No "ID" have work

		pthread_mutex_unlock(&mutex_Row);
		//unlock - thread No "id" is going to operate on row "myRow"
		MATRIX_line_multiply(MAT_OUT, MAT_ONE, MAT_TWO, myRow);
	}
}

int main(int argc, char *argv[]) {

	int i,flag;

	NOF_PROC = UTILS_get_args(argc, argv);

	MAT_ONE = MATRIX_new(UTILS_parse_rows(FILEIN_1), UTILS_parse_cols(FILEIN_1));
	UTILS_parse_matrix(FILEIN_1, MAT_ONE);

	MAT_TWO = MATRIX_new(UTILS_parse_rows(FILEIN_2), UTILS_parse_cols(FILEIN_2));
	UTILS_parse_matrix(FILEIN_2, MAT_TWO);

	if(!(MATRIX_is_multipliable(MAT_ONE, MAT_TWO))) {
		fprintf(stderr, "ERROR: invalid matrixes sizes.\n");
		exit(EXIT_FAILURE);
	}

	MAT_OUT = MATRIX_new(MAT_ONE->r, MAT_TWO->c);

	NOF_PROC = MIN(NOF_PROC, MAT_ONE->r);

	threads = (pthread_t *) malloc(sizeof(pthread_t) * NOF_PROC);
	//pthread_t threads[NOF_PROC];
	pthread_attr_t atributos;
	pthread_attr_init(&atributos);
	pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);
	pthread_attr_setscope(&atributos,PTHREAD_SCOPE_SYSTEM);


	//Distributing the work.
	currentRow = 0;
	for (i = 0; i < NOF_PROC; i++){
		flag = pthread_create(&threads[i], NULL, (void *(*) (void *)) multiplica, NULL);
		if (flag)
			exit(-1);
	}

	//join all threads
	for (i = 0; i < NOF_PROC; i++)
		pthread_join(threads[i], NULL);

	//write the matrix
	UTILS_write_matrix(FILEOUT, MAT_OUT);
	//free all matrix
	MATRIX_free(MAT_ONE);
	MATRIX_free(MAT_TWO);
	MATRIX_free(MAT_OUT);

	return 0;
}
