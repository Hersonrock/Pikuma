#include "load.h"
#include "errno.h"

int load_obj(const char *obj_path){
        FILE* obj_file;
        obj_file = open_file(obj_path,"r"); 
        if(obj_file != NULL){
                return 0;
        } else {
                return 1;
        }
}
FILE *open_file(const char *file_path,char *mode){
        FILE *fd = fopen(file_path, mode);

        if(!fd){
                fprintf(stderr, "Could not open file on path:\n\t%s\n", file_path);
                perror("Failed to open file");
        }
        
        return fd;
}
