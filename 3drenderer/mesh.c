#include "mesh.h"

vect3_t *obj_vertices = NULL;
face_t *obj_faces = NULL;

mesh_t mesh = {
    .vertices = NULL,
    .faces = NULL,
    .rotation = {0, 0, 0}
};

void load_obj_mesh_data(vect3_t *vertices, face_t *faces){
        for (int i = 0; i < array_length(vertices); i++) {
                vect3_t cube_vertex = vertices[i];
                array_push(mesh.vertices, cube_vertex);
        }

        for (int i = 0; i < array_length(faces); i++) {
                face_t cube_face = faces[i];
                array_push(mesh.faces, cube_face);
        }
}
