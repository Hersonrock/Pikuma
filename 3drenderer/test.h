#include <assert.h>
#include <float.h>
#include <math.h>
#include "vector.h"
#include "matrix.h"

#define TOLERANCE  0.001

//TODO: Functions protoypes for tests
void run_all_tests();

void test_vect2_length();
void test_vect2_add();
void test_vect2_sub();
void test_vect2_mult();
void test_vect2_div();
void test_vect2_dot();
void test_vect2_swap();

void test_vect3_length();
void test_vect3_add();
void test_vect3_sub();
void test_vect3_mult();
void test_vect3_div();
void test_vect3_dot();
void test_vect3_cross();

void test_mat4_multiply();
