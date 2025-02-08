#ifndef FILEIO
#define FILEIO
#include <stdio.h>
#include "errno.h"
#include "mesh.h"
#include "array.h"
#include "string.h"
#include "vector.h"
#include "display.h"
#define MAX_LINE_SIZE 265
#define FACTOR 5 

int load_obj(const char *obj_path, vect3_t **in_vertices, face_t **in_faces);
FILE *open_file(const char *file_path,char *mode);
int read_file(FILE *obj_file, vect3_t **in_vertices, face_t **in_faces);
void print_debug(void *obj, char *type);
#endif //FILEIO
