#include <stdio.h>
#include <stdlib.h>
#include "../include/matrix.h"
#include "../include/utils.h"
#include <string.h>

int row_parse(char *buffer, MATRIX *matrix, int row);

/* Parse terminal arguments as desired (an integer meaning number of processes
 * or threads to be spawned)
 */
int UTILS_get_args(int argc, char **argv) {
	int arg;
	if(argc == NOF_ARGS) {
		if(!sscanf(argv[1], "%d", &arg)) {
			fprintf(stderr, 
				"ERROR: argument could not be parsed.\n");
			exit(EXIT_FAILURE);
		}
		if(arg <= 0) {
			fprintf(stderr, "ERROR: invalid number of processes.\n");
			exit(EXIT_FAILURE);
		}
	}
	else {
		fprintf(stderr,
			"ERROR: invalid number of arguments. EXPECTS n : integer.\n");
		exit(EXIT_FAILURE);
	}
	return arg;
}
/* Parse the number of rows that the matrix in 'filename' has */
int UTILS_parse_rows(char *filename) {
	int rows;
	FILE *file;
	if((file = fopen(filename,"r")) == NULL) {
		fprintf(stderr, "ERROR: could not open %s\n", filename);
		exit(EXIT_FAILURE);
	}

	if(fscanf(file, "LINHAS = %d\n", &rows)) {
		fclose(file);
		return rows;
	}
	else {
		fclose(file);
		return -1;
	}
}
/* Parse the number of columns that the matrix in 'filename' has */
int UTILS_parse_cols(char *filename) {
	int cols;
	FILE *file;
	char buffer[256];
	if((file = fopen(filename,"r")) == NULL) {
		fprintf(stderr, "ERROR: could not open %s\n", filename);
		exit(EXIT_FAILURE);
	}

	fgets(buffer, sizeof(buffer), file);
	
	if(fscanf(file, "COLUNAS = %d\n", &cols)) {
		fclose(file);
		return cols;
	}
	else {
		fclose(file);
		return -1;
	}
}
/* Parser the matrix from 'filename' to 'matrix' of type MATRIX */
int UTILS_parse_matrix(char *filename, MATRIX *matrix) {
	int row_count = 0;
	char *buffer, line[256];
	FILE *file;
	size_t line_size = sizeof(int) * (2 * matrix->c) + 1;

	if((file = fopen(filename,"r")) == NULL){
		fprintf(stderr, "ERROR: could not open %s\n", filename);
		exit(EXIT_FAILURE);
	}

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
/* Writes matrix 'mat' (of type MATRIX) to file 'filename' */
int UTILS_write_matrix(char *filename, MATRIX *mat) {
	int i, j;
	FILE *file;

	if((file = fopen(filename, "w+")) == NULL) {
		fprintf(stderr, "ERROR: could not open %s\n", filename);
		exit(EXIT_FAILURE);
	}

	fprintf(file, "LINHAS = %d\nCOLUNAS = %d\n", mat->r, mat->c);
	for(i = 0; i < mat->r; i++) {
		for(j = 0; j < mat->c; j++) {
			fprintf(file, "%d", mat->matrix[i][j]);
			if(j < mat->c - 1) // last column checking, no spaces
				fprintf(file, " ");
		}
		if(i < mat->r - 1) // last row checking, no line end
			fprintf(file, "\n");
	}
	return 0;
}

int UTILS_write_arr_mat(char *filename, int *matrix, int r, int c) {
	int i, j;
	FILE *file;

	if((file = fopen(filename, "w+")) == NULL) {
		fprintf(stderr, "ERROR: could not open %s\n", filename);
		exit(EXIT_FAILURE);
	}

	fprintf(file, "LINHAS = %d\nCOLUNAS = %d\n", r, c);
	for(i = 0; i < r; i++) {
		for(j = 0; j < c; j++) {
			fprintf(file, "%d", matrix[i*c + j]);
			if(j < c - 1) // last column checking, no spaces
				fprintf(file, " ");
		}
		if(i < r - 1) // last row checking, no line end
			fprintf(file, "\n");
	}
	return 0;
}
/* Auxiliary subroutine to parse a 'row' of 'matrix' in a safe way */
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
