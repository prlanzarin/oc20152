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
int parser_rows(char *filename) {
	int rows;
	FILE *file;
	if((file = fopen(filename,"r")) == NULL)
		return -1;

	if(fscanf(file, "LINHAS = %d\n", &rows))
		return rows;
	else
		return -1;
}

int parser_cols(char *filename) {
	int cols;
	FILE *file;
	char buffer[256];
	if((file = fopen(filename,"r")) == NULL)
		return -1;

	fgets(buffer, sizeof(buffer), file);
	
	if(fscanf(file, "COLUNAS = %d\n", &cols))
		return cols;
	else	
		return -1;
}

int parser_matrix(char *filename, MATRIX *matrix) {
	int row_count = 0;
	char *buffer, line[256];
	FILE *file;
	size_t line_size = sizeof(int) * (2 * matrix->c) + 1;

	if((file = fopen(filename,"r")) == NULL)
		return -1;

	fgets(line, sizeof(line), file);
	fgets(line, sizeof(line), file);

	buffer = (char *) malloc(line_size);
	
	while((fgets(buffer, line_size, file)) != NULL) {
		/* buffer processing */
		row_parse(buffer, matrix, row_count);
		row_count++;
	}

	fclose(file);
	return 0;
}
