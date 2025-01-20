#ifndef MESH
#define MESH

#include "triangle.h"
#include "array.h"
#define N_CUBE_VERTICES  8
#define N_CUBE_FACES 6 * 2

extern vect3_t cube_vertices[N_CUBE_VERTICES];
extern face_t cube_faces[N_CUBE_FACES];


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

#endif //MESH