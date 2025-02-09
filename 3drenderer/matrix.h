#ifndef MATRIX_H
#define MATRIX_H
#include "vector.h"
#include "math.h"
typedef struct {
        float m[4][4];
} mat4_t;

mat4_t mat4_identity(void);
mat4_t mat4_make_scale(float sx, float sy, float sz);
mat4_t mat4_make_translation(float tx, float ty, float tz);
vect4_t mat4_mul_vec4(mat4_t m, vect4_t v);
mat4_t mat4_make_rotation_z(float angle);
mat4_t mat4_make_rotation_x(float angle);
mat4_t mat4_make_rotation_y(float angle);
#endif //MATRIX_H
