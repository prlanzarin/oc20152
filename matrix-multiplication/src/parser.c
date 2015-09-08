#include <stdio.h>
#include <stdlib.h>
#include "../include/matrix.h"
#include "../include/parser.h"
#include <string.h>

int row_parse(char *buffer, MATRIX *matrix, int row) {
	char *delim = " ";
	char *tok_buf;
	int col_count = 0;

	tok_buf = strtok(buffer, delim);
	while (tok_buf != NULL) {
		matrix->matrix[row][col_count] = atoi(tok_buf);
		col_count++;
		tok_buf = strtok(NULL, delim);
	}
	return 0;
}
int parser_rows(FILE *file) {
	int rows;
	if(fscanf(file, "LINHAS = %d\n", &rows))
		return rows;
	else
		return -1;
}

int parser_cols(FILE *file) {
	int cols;
	if(fscanf(file, "COLUNAS = %d\n", &cols)) {
		printf("COLS P : %d \n", cols);
		return cols;
	}
	else {	
		printf("COLS P WRONG: %d \n", cols);
		return -1;
	}
}

int parser_matrix(FILE *file, MATRIX *matrix) {
	int row_count = 0;
	char *buffer;

	buffer = (char *) malloc(sizeof(char) * (2 * matrix->c));
	
	while(!feof(file)) {
		fgets(buffer, 2 * (matrix->c) - 1, file);
		/* buffer processing */
		row_parse(buffer, matrix, row_count);
		row_count++;
	}

	return 0;
}
