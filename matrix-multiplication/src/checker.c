#include <stdio.h>
#include <stdlib.h>
#include "../include/matrix.h"
#include "../include/utils.h"

MATRIX *m1, *m2, *mout, *result;

void final(void) {
	MATRIX_free(m1);
	MATRIX_free(m2);
	MATRIX_free(mout);
	MATRIX_free(result);
}

int main(int argc, char *argv[]) {

	m1 = MATRIX_new(UTILS_parse_rows(FILEIN_1), UTILS_parse_cols(FILEIN_1));
	UTILS_parse_matrix(FILEIN_1, m1);

	m2 = MATRIX_new(UTILS_parse_rows(FILEIN_2), UTILS_parse_cols(FILEIN_2));
	UTILS_parse_matrix(FILEIN_2, m2);
	
	mout = MATRIX_new(UTILS_parse_rows(FILEOUT), UTILS_parse_cols(FILEOUT));
	UTILS_parse_matrix(FILEOUT, mout);

	result = MATRIX_sequential_multiply(m1, m2);
	if(result == NULL || m1 == NULL || m2 == NULL || mout == NULL) {
		final();
		exit(EXIT_FAILURE);
	}

	if(MATRIX_is_equal(result, mout)) {
		final();
		printf("EQUAL\n");
		return 0;
	}
	else {
		final();
		printf("NOT EQUAL\n");
		return -1;
	}
}
