#include "test.h"

///////////////ALL_TESTS//////////////////
void run_all_tests(){
        printf("Running vect2_t tests...\n");
        test_vect2_length();
        test_vect2_add();
        test_vect2_sub();
        test_vect2_mult();
        test_vect2_div();
        test_vect2_dot();
        test_vect2_swap();

        printf("Running vect3_t tests...\n");
        test_vect3_length();
        test_vect3_add();
        test_vect3_sub();
        test_vect3_mult();
        test_vect3_div();
        test_vect3_dot();
        test_vect3_cross();
        test_mat4_multiply();
}
///////VECTOR 2D TESTS/////
void test_vect2_length(){
        vect2_t v1 = { .x = 3, .y = 4 };
        float norm = vect2_length(v1);
        assert(fabsf(norm - 5) < TOLERANCE);
        printf("\ttest_vect2_length passed!\n");
}
void test_vect2_add(){
        vect2_t v1 = { .x = 6, .y = 7};
        vect2_t v2 = { .x = 8, .y = 2};
        vect2_t sum = vect2_add(v1, v2);
        assert(fabsf(sum.x - 14) < TOLERANCE);
        assert(fabsf(sum.y - 9) < TOLERANCE);
        printf("\ttest_vect2_add passed!\n");
}
void test_vect2_sub(){
        vect2_t v1 = { .x = 2, .y = 1};
        vect2_t v2 = { .x = 5, .y = 6};
        vect2_t sub = vect2_sub(v1, v2);
        assert(fabsf(sub.x - (-3)) < TOLERANCE);
        assert(fabsf(sub.y - (-5)) < TOLERANCE);
        printf("\ttest_vect2_sub passed!\n");
}
void test_vect2_mult(){
        vect2_t v1 = { .x = 2, .y = 1};
        float factor = -4;
        vect2_t mult = vect2_mult(v1, factor);
        assert(fabsf(mult.x - (-8)) < TOLERANCE);
        assert(fabsf(mult.y - (-4)) < TOLERANCE);
        printf("\ttest_vect2_mult passed!\n");
}
void test_vect2_div(){
        vect2_t v1 = { .x = 3, .y = 5};
        float factor = 6;
        vect2_t mult = vect2_div(v1, factor);
        assert(fabsf(mult.x - 0.5f) < TOLERANCE);
        assert(fabsf(mult.y - 0.833f) < TOLERANCE);
        printf("\ttest_vect2_div passed!\n");
}
void test_vect2_dot(){
        
        vect2_t v1 = { .x = 4, .y = 5};
        vect2_t v2 = { .x = 2, .y = 2};
        float dot = vect2_dot(v1, v2);
        assert(fabsf(dot - 18) < TOLERANCE);
        printf("\ttest_vect2_dot passed!\n");
}
void test_vect2_swap(){
        vect2_t v1 = { .x = 4, .y = 5};
        vect2_t v2 = { .x = 3, .y = 2};
        //printf("v1 =[%.2f,%.2f], v2 =[%.2f,%.2f]\n", v1.x, v1.y, v2.x, v2.y);
        vect2_swap(&v1, &v2);
        //printf("v1 =[%.2f,%.2f], v2 =[%.2f,%.2f]\n", v1.x, v1.y, v2.x, v2.y);
        assert(fabsf(v1.x - 3) < TOLERANCE);
        assert(fabsf(v1.y - 2) < TOLERANCE);
        assert(fabsf(v2.x - 4) < TOLERANCE);
        assert(fabsf(v2.y - 5) < TOLERANCE);
        printf("\ttest_vect2_swap passed!\n");
}
///////VECTOR 3D TESTS/////
void test_vect3_length(){
        vect3_t v1 = { .x = 3, .y = 4, .z = 6};
        float norm = vect3_length(v1);
        float expected = 7.81f;
        assert(fabsf(norm - expected) < TOLERANCE);
        printf("\ttest_vect3_length passed!\n");
}
void test_vect3_add(){
        vect3_t v1 = { .x = 6, .y = 7, .z = 3};
        vect3_t v2 = { .x = 8, .y = 2, .z = 1};
        vect3_t sum = vect3_add(v1, v2);
        assert(fabsf(sum.x - 14) < TOLERANCE);
        assert(fabsf(sum.y - 9) < TOLERANCE);
        assert(fabsf(sum.z - 4) < TOLERANCE);
        printf("\ttest_vect3_add passed!\n");
}
void test_vect3_sub(){
        vect3_t v1 = { .x = 8, .y = 3, .z = 9};
        vect3_t v2 = { .x = 5, .y = 2, .z = 4};
        vect3_t sub = vect3_sub(v1, v2);
        assert(fabsf(sub.x - 3) < TOLERANCE);
        assert(fabsf(sub.y - 1) < TOLERANCE);
        assert(fabsf(sub.z - 5) < TOLERANCE);
        printf("\ttest_vect3_sub passed!\n");
}
void test_vect3_mult(){
        vect3_t v1 = { .x = 2, .y = 1, .z = 3};
        float factor = 6;
        vect3_t mult = vect3_mult(v1, factor);
        assert(fabsf(mult.x - 12) < TOLERANCE);
        assert(fabsf(mult.y - 6) < TOLERANCE);
        assert(fabsf(mult.z - 18) < TOLERANCE);
        printf("\ttest_vect3_mult passed!\n");
}
void test_vect3_div(){
        vect3_t v1 = { .x = 3, .y = 5, .z = 2};
        float factor = 6;
        vect3_t mult = vect3_div(v1, factor);
        assert(fabsf(mult.x - 0.5f) < TOLERANCE);
        assert(fabsf(mult.y - 0.833f) < TOLERANCE);
        assert(fabsf(mult.z - 0.333f) < TOLERANCE);
        printf("\ttest_vect3_div passed!\n");
}
void test_vect3_dot(){
        vect3_t v1 = { .x = 4, .y = 5, .z = 2};
        vect3_t v2 = { .x = 2, .y = 2, .z = 3};
        float dot = vect3_dot(v1, v2);
        assert(fabsf(dot - 24) < TOLERANCE);
        printf("\ttest_vect3_dot passed!\n");
}
void test_vect3_cross(){
        vect3_t v1 = { .x = 4, .y = -2, .z = -2};
        vect3_t v2 = { .x = -1, .y = -3, .z = 3};
        vect3_t cross = vect3_cross(v1, v2);
        assert(fabsf(cross.x - (-12)) < TOLERANCE);
        assert(fabsf(cross.y - (-10)) < TOLERANCE);
        assert(fabsf(cross.z - (-14)) < TOLERANCE);
        printf("\ttest_vect3_cross passed!\n");
}
////MATRIX 
void test_mat4_multiply(){
        mat4_t a = {
                .m[0][0] = 9, .m[0][1] = 4, .m[0][2] = 2, .m[0][3] = 8,
                .m[1][0] = 2, .m[1][1] = 2, .m[1][2] = 0, .m[1][3] = 7,
                .m[2][0] = 5, .m[2][1] = 8, .m[2][2] = 5, .m[2][3] = 7,
                .m[3][0] = 9, .m[3][1] = 4, .m[3][2] = 8, .m[3][3] = 9
        };
        mat4_t b = {
                .m[0][0] = 1, .m[0][1] = 9, .m[0][2] = 2, .m[0][3] = 3,
                .m[1][0] = 9, .m[1][1] = 1, .m[1][2] = 4, .m[1][3] = 0,
                .m[2][0] = 2, .m[2][1] = 2, .m[2][2] = 3, .m[2][3] = 0,
                .m[3][0] = 0, .m[3][1] = 6, .m[3][2] = 6, .m[3][3] = 0
        };

        mat4_t c = mat4_multiply(a, b);
        assert(c.m[0][0] == 49);
        assert(c.m[0][1] == 137);
        assert(c.m[0][2] == 88);
        assert(c.m[0][3] == 27);

        assert(c.m[1][0] == 20);
        assert(c.m[1][1] == 62);
        assert(c.m[1][2] == 54);
        assert(c.m[1][3] == 6);

        assert(c.m[2][0] == 87);
        assert(c.m[2][1] == 105);
        assert(c.m[2][2] == 99);
        assert(c.m[2][3] == 15);

        assert(c.m[3][0] == 61);
        assert(c.m[3][1] == 155);
        assert(c.m[3][2] == 112);
        assert(c.m[3][3] == 27);
        printf("\ttest_mat4_multiply passed!\n");

}
