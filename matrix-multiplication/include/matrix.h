#ifndef __matrix__
#define __matrix__

typedef struct p_matrix {
        int **matrix;
        int r, c;
} MATRIX;

MATRIX *MATRIX_new(int rows, int cols);

void MATRIX_free(MATRIX *matrix);

#endif
