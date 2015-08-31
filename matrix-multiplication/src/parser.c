#include <stdio.h>
#include <stdlib.h>
#include "../include/parser.h"
#include <string.h>

int row_parse(char *buffer, int ncols, int matrix[][ncols], int row) {
	char *delim = " ";
	char *tok_buf;
	int col_count = 0;

	tok_buf = strtok(buffer, delim);
	while (tok_buf != NULL) {
		matrix[row][col_count++] = atoi(tok_buf);
		tok_buf = strtok(NULL, delim);
	}
	return 0;
}

int parser_matrix_size(FILE *file, int *cols, int *rows) {
	if(fscanf(file, "LINHAS = %d\n", rows))
		printf("r %d\n", *rows);		
	else 
		return -1;

	if(fscanf(file, "COLUNAS = %d\n", cols))
		printf("c %d\n", *cols);
	else
		return -1;
	
	return 0;
}

int parser_matrix(FILE *file, int cols, int matrix[][cols]) {
	int row_count = 0;
	char *buffer;

	buffer = (char *) malloc(sizeof(char) * 2*cols);
	
	while(!feof(file)) {
		fgets(buffer, 2*cols-1, file);
		/* buffer processing */
		row_parse(buffer, cols, matrix, row_count++);
	}

	return 0;
}
