#ifndef FILEIO
#define FILEIO
#include <stdio.h>
#define MAX_LINE_SIZE 265
#define FACTOR 5 

int load_obj(const char *obj_path);
FILE *open_file(const char *file_path,char *mode);
int read_file(FILE *obj_file);
void print_debug(void *obj, char *type);
void print_debug(void *obj, char *type);
#endif //FILEIO
