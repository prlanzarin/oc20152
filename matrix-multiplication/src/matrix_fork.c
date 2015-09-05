#include <stdio.h>
#include <stdlib.h>
#include "../include/parser.h"
#include "../include/matrix.h"

int main(int argc, char *argv[]) {
	MATRIX *mat = matrix_new(3, 4);
	printf("MATRIX ALLOC TEST r %d c %d\n", mat->r, mat->c); 
	matrix_free(mat);
	FILE *file = fopen("in1.txt", "r");
	printf("Hello %s \n", *argv);
	return 0;
}
