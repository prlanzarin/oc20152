#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	int i, j, mat, n;
	float temp = 0, sum = 0;
	FILE *op, *ot, *rp, *rt;
	if((rp = fopen("rprocess.txt","r")) == NULL) {
		fprintf(stderr, "ERROR: could not open\n");
		exit(EXIT_FAILURE);
	}
	if((rt = fopen("rthread.txt","r")) == NULL) {
		fprintf(stderr, "ERROR: could not open");
		exit(EXIT_FAILURE);
	}

	if((op = fopen("op.txt", "w+")) == NULL) {
		fprintf(stderr, "ERROR: could not open"); 
		exit(EXIT_FAILURE);
	}
	if((ot = fopen("ot.txt", "w+")) == NULL) {
		fprintf(stderr, "ERROR: could not open"); 
		exit(EXIT_FAILURE);
	}
	j = 0;
	while(feof(rp) == 0) {
		for(i = 0; i < 11; i++) {
			if(fscanf(rp, "%f MAT %d N %d\n", &temp, &mat, &n) == 3) {
				sum += temp;
				j = 1;
			}
			else {j = 0; break;}
		}
		if(j)
			fprintf(op, "%f %d %d\n", (sum/11), mat, n);
		sum = 0;
		temp = 0;
	}
	j = 0;	
	sum = 0;
	temp = 0;
	while(!feof(rt)) {
		for(i = 0; i < 11; i++) {
			if(fscanf(rt, "%f MAT %d N %d\n", &temp, &mat, &n) == 3) {
				sum += temp;
				j = 1;
			}
			else { j = 0; break; }

		}
		if(j)
			fprintf(ot, "%f %d %d\n", (sum/11), mat, n);
		sum = 0;
		temp = 0;
	}
	fclose(rp);
	fclose(rt);
	fclose(op);
	fclose(ot);
	return 0;

}
