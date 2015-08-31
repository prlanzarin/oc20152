typedef struct p_matrix {
        int **matrix;
        int rows, cols;
} MATRIX;

matrix_new(int **matrix, int rows, int cols);
matrix_free(int **matrix, int rows, int cols);
matrix_multiply(int **m1, int **m2);
