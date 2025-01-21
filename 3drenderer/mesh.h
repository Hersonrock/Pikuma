#ifndef MESH
#define MESH

#include "triangle.h"
#include "array.h"
#define N_CUBE_VERTICES  8
#define N_CUBE_FACES 6 * 2

extern vect3_t cube_vertices[N_CUBE_VERTICES];
extern face_t cube_faces[N_CUBE_FACES];

extern vect3_t *obj_vertices;
extern face_t *obj_faces;

////////////////////////////
// Define a struct for dynamic size meshes.
///////////////////////////
typedef struct {
	vect3_t* vertices;   // Dynamic array of vertices
	face_t* faces;       // Dynamic array of faces
	vect3_t rotation;    // Rotation with x, y, z values
}mesh_t;

extern mesh_t mesh;

void load_cube_mesh_data(void);

void load_obj_mesh_data(vect3_t *vertices, face_t *faces);
void print_debug(void *obj, char *type);
#endif //MESH
