#ifndef FILEIO
#define FILEIO
#include <stdio.h>

int load_obj(const char *obj_path);
FILE *open_file(const char *file_path,char *mode);
#endif //FILEIO
