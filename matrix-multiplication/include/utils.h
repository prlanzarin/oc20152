#ifndef __parser__
#define __parser__

#define FILEIN_1 "in1.txt"
#define FILEIN_2 "in2.txt"
#define FILEOUT "out.txt"
#define NOF_ARGS 2

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int UTILS_parse_rows(char *filename);
int UTILS_parse_cols(char *filename); 
int UTILS_parse_matrix(char *filename, MATRIX *matrix); 
int UTILS_get_args(int argc, char **argv);
int UTILS_write_matrix(char *filename, MATRIX *mat);

#endif
