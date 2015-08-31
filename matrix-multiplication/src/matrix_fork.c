#include <stdio.h>
#include <stdlib.h>
#include "../include/parser.h"

int main(int argc, char *argv[]) {
	FILE *file = fopen("in1.txt", "r");
	printf("Hello %s \n", *argv);
	int tm[3][4];
	parser_matrix(file, 4, tm);
	return 0;
}
