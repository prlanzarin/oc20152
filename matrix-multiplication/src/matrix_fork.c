#include <stdio.h>
#include <stdlib.h>
#include "../include/matrix.h"
#include "../include/parser.h"

int main(int argc, char *argv[]) {
	int r = parser_rows("in1.txt");
	int c = parser_cols("in1.txt");

	if(r == -1 || c == -1)
		exit(-1);
	MATRIX *mat1 = MATRIX_new(r, c);
//	parser_matrix("in1.txt", mat1);
	MATRIX_free(mat1);
	return 0;
}
