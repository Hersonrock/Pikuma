#include "load.h"
#include "errno.h"
#include "mesh.h"
#include "array.h"
#include "string.h"

int load_obj(const char *obj_path){
        FILE* obj_file;
        obj_file = open_file(obj_path,"r"); 
        if(obj_file != NULL){
                return 0;
        } else {
                return 1;
        }
        read_file(obj_file);
        fclose(obj_file);
}
FILE *open_file(const char *file_path,char *mode){
        FILE *fd = fopen(file_path, mode);

        if(!fd){
                fprintf(stderr, "Could not open file on path:\n\t%s\n", file_path);
                perror("Failed to open file");
        }
        
        return fd;
}
int read_file(FILE *obj_file){
        char buffer[MAX_LINE_SIZE];
        
        while(fgets(buffer, sizeof(buffer), obj_file)){
                buffer[strcspn(buffer, '\n')] = '\0';
                if(strncmp(buffer, "v ", 2) == 0){
                        vect3_t vertex;
                        sscanf_s(buffer, "v %f %f %f", &vertex.x,
                                                  &vertex.y,
                                                  &vertex.z);
                        print_debug((void *)&vertex, "vect3_t");
                        array_push(obj_vertices, vertex);
                }

                if(strncmp(buffer, "f ", 2) == 0){
                        face_t faces;
                        buffer[strcspn(buffer, '/')] = ' ';
                        sscanf_s(buffer, "f %d * * %d * * %d * *", &faces.a,
                                                  &faces.b,
                                                  &faces.c);
                        print_debug((void *)&faces, "face_t");
                        array_push(obj_faces, faces);
                }
        }
        
        return 0;
}

void print_debug(void *obj, char *type) {
    if (strcmp(type, "face_t") == 0) {
        face_t face = *(face_t *)obj; // Dereference the casted pointer
        printf("face = [%d, %d, %d]\n", face.a, face.b, face.c);
    } else if (strcmp(type, "vect3_t") == 0) {
        vect3_t vect3 = *(vect3_t *)obj; // Similar handling for vect3_t

        printf("vertex = [%d, %d, %d]\n", vect3.x, vect3.y, vect3.z);
    } else {
        printf("Unknown type: %s\n", type);
    }
}

