#ifndef __parser__
#define __parser__

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int parser_rows(char *filename);
int parser_cols(char *filename); 
int parser_matrix(char *filename, MATRIX *matrix); 
int UTILS_get_args(int argc, char **argv);
int UTILS_write_matrix(char *filename, MATRIX *mat);

#endif
