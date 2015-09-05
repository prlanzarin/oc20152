/*
 * int **matrix: matrix pointer
 * int r: rows (linhas)
 * int c: columns (colunas)
 */

typedef struct p_matrix {
        int **matrix;
        int r, c;
} MATRIX;

MATRIX *matrix_new(int rows, int cols);
void matrix_free(MATRIX *matrix);
int matrix_multiply(MATRIX *m1, MATRIX *m2);
