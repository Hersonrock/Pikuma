#include "load.h"

int load_obj(const char *obj_path, vect3_t **in_vertices, face_t **in_faces){
        FILE* obj_file;
        obj_file = open_file(obj_path,"r"); 
        if(obj_file != NULL){
        } else {
                return 1;
        }
        read_file(obj_file, in_vertices, in_faces);
        fclose(obj_file);
        return 0;
}
FILE *open_file(const char *file_path,char *mode){
        FILE *fd = fopen(file_path, mode);

        if(!fd){
                fprintf(stderr, "Could not open file on path:\n\t%s\n", file_path);
                perror("Failed to open file");
        }
        else{
                printf("%s File opened\n", file_path);
        }
        
        return fd;
}
int read_file(FILE *obj_file, vect3_t **in_vertices, face_t **in_faces){
        char buffer[MAX_LINE_SIZE];
        int color_set = 0;

        printf("reading file...\n");
        while(fgets(buffer, sizeof(buffer), obj_file)){
                // remove trailing newline and carriage return
                buffer[strcspn(buffer, "\r\n")] = '\0';
                if (buffer[0] == '\0') {
                        continue;
                }
                if(strncmp(buffer, "v ", 2) == 0){
                        vect3_t vertex;
                        sscanf_s(buffer, "v %f %f %f", &vertex.x,
                                                  &vertex.y,
                                                  &vertex.z);

                        //Workaround for model sizes. Better solution Pending
                        vertex = vect3_div(vertex, FACTOR);
                        //Correcting for handness choseen
                        array_push(*in_vertices, vertex);
                        continue;
                }

                if(strncmp(buffer, "f ", 2) == 0){
                        face_t faces;
                        int vertex_indices[3];
                        int texture_indices[3];
                        int normal_indices[3];
                        sscanf_s(buffer, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                                                &vertex_indices[0],
                                                &texture_indices[0],
                                                &normal_indices[0],
                                                &vertex_indices[1],
                                                &texture_indices[1],
                                                &normal_indices[1],
                                                &vertex_indices[2],
                                                &texture_indices[2],
                                                &normal_indices[2]);
                        faces.a = vertex_indices[0];
                        faces.b = vertex_indices[1];
                        faces.c = vertex_indices[2];
                        switch(color_set++){
                                case 0:
                                        //faces.color = RED;
                                        faces.color = WHITE;
                                        break;
                                case 1:
                                        //faces.color = GREEN;
                                        faces.color = WHITE;
                                        break;
                                case 2:
                                        //faces.color = BLUE;
                                        faces.color = WHITE;
                                        break;
                        }

                        if(color_set > 2) color_set = 0;

                        array_push(*in_faces, faces);
                        continue;
                }
        }
        
        return 0;
}
void print_debug(void *obj, char *type) {
    if (strcmp(type, "face_t") == 0) {
        face_t face = *(face_t *)obj; // Dereference the casted pointer
        printf("[%d, %d, %d]\n", face.a, face.b, face.c);
    } else if (strcmp(type, "vect3_t") == 0) {
        vect3_t vect3 = *(vect3_t *)obj; // Similar handling for vect3_t

        printf("[%f, %f, %f]\n", vect3.x, vect3.y, vect3.z);
    } else {
        printf("Unknown type: %s\n", type);
    }
}

