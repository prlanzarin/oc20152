#ifndef __matrix__
#define __matrix__

typedef struct p_matrix {
        int **matrix;
        int r, c;
} MATRIX;

MATRIX *MATRIX_new(int rows, int cols);

void MATRIX_free(MATRIX *matrix);

MATRIX *MATRIX_sequential_multiply(MATRIX *m1, MATRIX *m2);

void MATRIX_line_multiply(MATRIX *mout, MATRIX *m1, MATRIX *m2, int row);

int MATRIX_is_multipliable(MATRIX *m1, MATRIX *m2);

int MATRIX_is_equal(MATRIX *m1, MATRIX  *m2); 
#endif
