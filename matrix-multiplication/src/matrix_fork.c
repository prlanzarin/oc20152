#include <stdio.h>
#include <stdlib.h>
#include "../include/matrix.h"
#include "../include/parser.h"

int main(int argc, char *argv[]) {
	FILE *file = fopen("in1.txt", "r");
	int r = parser_rows(file);
	int c = parser_rows(file);
	printf("R %d C %d \n", r, c);
	MATRIX *mat1 = MATRIX_new(r, c);
	printf("MATRIX ALLOC TEST r %d c %d\n", mat1->r, mat1->c); 
	parser_matrix(file, mat1);
	MATRIX_free(mat1);
	return 0;
}
