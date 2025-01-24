#include "test.h"

void test_vect2_lenght(){
        vect2_t v1 = { .x = 3, .y = 4 };
        float norm = vect2_lenght(v1);
        assert(fabs(norm - 5) < TOLERANCE);
        printf("test_vect2_lenght passed!\n");
}
void test_vect3_lenght(){
        vect3_t v1 = { .x = 3, .y = 4, .z = 6};
        float norm = vect3_lenght(v1);
        float expected = 7.81f;
        assert(fabs(norm - expected) < TOLERANCE);
        printf("test_vect3_lenght passed!\n");
}
//TODO functions to tests 
