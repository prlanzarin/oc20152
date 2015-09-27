#include <stdio.h>
#include <stdlib.h>
#include <time.h> // rand subroutine
#include "../include/matrix.h"
#include "../include/utils.h"

void fill_matrix(MATRIX *m1);

int main(int argc, char *argv[]) {
	MATRIX *m1, *m2;
	int ra, ca, rb, cb;

	srand(time(NULL));

	if(argc < 5)
		exit(EXIT_FAILURE);
	sscanf(argv[1], "%d", &ra);
	sscanf(argv[2], "%d", &ca);
	sscanf(argv[3], "%d", &rb);
	sscanf(argv[4], "%d", &cb);

	m1 = MATRIX_new(ra, ca);
	m2 = MATRIX_new(rb, cb);
	// MATRIX 1 generation
	fill_matrix(m1);
	// MATRIX 2 generation
	fill_matrix(m2);
	// writing to files in1.txt, in2.txt
	int UTILS_write_matrix(char *filename, MATRIX *mat);
	UTILS_write_matrix(FILEIN_1, m1);
	UTILS_write_matrix(FILEIN_2, m2);
	MATRIX_free(m1);
	MATRIX_free(m2);
	return 0;
}

void fill_matrix(MATRIX *m1) {
	int i, j;
	for(i = 0; i < m1->r; i++) {
		for(j = 0; j < m1->c; j++)
			m1->matrix[i][j] = rand() % 100;
	}
}
