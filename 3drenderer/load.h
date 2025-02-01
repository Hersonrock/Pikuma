#ifndef FILEIO
#define FILEIO
#include <stdio.h>
#define MAX_LINE_SIZE 265
#define FACTOR 1 

int load_obj(const char *obj_path);
FILE *open_file(const char *file_path,char *mode);
int read_file(FILE *obj_file);
#endif //FILEIO
