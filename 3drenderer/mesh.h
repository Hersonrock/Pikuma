#ifndef MESH
#define MESH

#include "triangle.h"
#include "array.h"
#include <stdio.h>

////////////////////////////
// Define a struct for dynamic size meshes.
///////////////////////////
typedef struct {
	vect3_t* vertices;   // Dynamic array of vertices
	face_t* faces;       // Dynamic array of faces
	vect3_t rotation;    // Rotation with x, y, z values
        vect3_t scale;        // scale with x, y and z values
        vect3_t translation;
}mesh_t;

extern vect3_t *obj_vertices;
extern face_t *obj_faces;
extern mesh_t mesh;

void load_obj_mesh_data(vect3_t *vertices, face_t *faces);
#endif //MESH
