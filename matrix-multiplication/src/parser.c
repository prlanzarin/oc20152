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
int size_parse(char *filename, int *cols, int *rows) {
	FILE *file;

	if((file = fopen(filename, "r")) == NULL)
		return -1;
	if(fscanf(file, "LINHAS = %d\n", rows))
		printf("r %d\n", *rows);		
	if(fscanf(file, "COLUNAS = %d\n", cols))
		printf("c %d\n", *cols);
	fclose(file);
	
	return 0;
}
int matrix_parse(char *filename, int cols, int matrix[][cols]) {
	int row_count = 0;
	FILE *file;
	char *buffer;

	if((file = fopen(filename, "r")) == NULL)
		return -1;

	buffer = (char *) malloc(sizeof(char) * 2*cols);
	
	while(!feof(file)) {
		fgets(buffer, 2*cols-1, file);
		/* buffer processing */
		row_parse(buffer, cols, matrix, row_count++);
	}

	return 0;
}
