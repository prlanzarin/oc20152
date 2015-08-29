#include <stdio.h>
#include <parser.h>

int **matrix_alloc(int rows, int cols, int **matrix);

int **matrix_parse(char *filename, int **matrix);

int **matrix_parse(char *filename, int **matrix) {
	int rows, cols, i;
	FILE *file;
	char *buffer;
	file = fopen(filename, r);
		


}
int main(int argc, char *argv[]) {

	printf("Hello %s \n", *argv);

	return 0;
}
