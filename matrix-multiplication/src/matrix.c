#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/matrix.h"

MATRIX *MATRIX_new(int rows, int cols) { 
	int i;

	MATRIX *new_mat = (MATRIX *)malloc(sizeof(MATRIX));
	new_mat->r = rows;
	new_mat->c = cols;
	if((new_mat->matrix = malloc(rows * sizeof(int *))) == NULL)
		return NULL;
	for(i = 0; i < rows; i++) {
		if((new_mat->matrix[i] = malloc(cols * sizeof(int))) == NULL)
			return NULL;
	}

	return new_mat;
}

void MATRIX_free(MATRIX *matrix) {
	int i;
	for(i = 0; i < matrix->r; i++)
			free((void *) matrix->matrix[i]);
	free((void *) matrix->matrix);
	free((void *) matrix);
}

int matrix_multiply(MATRIX *m1, MATRIX *m2) {
	return -1;
}
