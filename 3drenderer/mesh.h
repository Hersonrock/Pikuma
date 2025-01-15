#ifndef MESH
#define MESH

#include "vector.h"
#include "triangle.h"
#define N_MESH_VERTICES  8

vect3_t mesh_vertices[8];

#define N_MESH_FACES 6 * 2
face_t mesh_faces[N_MESH_FACES];

#endif //MESH