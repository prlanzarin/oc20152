#include <stdio.h>
#include <stdlib.h>
#include "../include/parser.h"

int main(int argc, char *argv[]) {

	printf("Hello %s \n", *argv);
	int tm[3][4];
	matrix_parse("in1.txt", 4, tm);
	return 0;
}
