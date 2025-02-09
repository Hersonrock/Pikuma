#include "matrix.h"

//typedef struct {
//        float m[4][4];
//} mat4_t;

mat4_t mat4_identity(void){
        // | 1 0 0 0|
        // | 0 1 0 0|
        // | 0 0 1 0|
        // | 0 0 0 1|
        mat4_t m = {{
                {1, 0, 0, 0},
                {0, 1, 0, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 1}
        }};
        return m;
}
mat4_t mat4_make_scale(float sx, float sy, float sz){
        //| sx 0 0 0|
        //| 0 sy 0 0|
        //| 0 0 sz 0|
        //| 0 0 0 1 |

        mat4_t m = mat4_identity();
        m.m[0][0] = sx;
        m.m[1][1] = sy;
        m.m[2][2] = sz;
        return m;
}
vect4_t mat4_mul_vec4(mat4_t m, vect4_t v){
        vect4_t out;

        out.x = m.m[0][0] * v.x + m.m[0][1] * v.y +
                m.m[0][2] * v.z + m.m[0][3] * v.w;
        out.y = m.m[1][0] * v.x + m.m[1][1] * v.y +
                m.m[1][2] * v.z + m.m[1][3] * v.w;
        out.z = m.m[2][0] * v.x + m.m[2][1] * v.y +
                m.m[2][2] * v.z + m.m[2][3] * v.w;
        out.w = m.m[3][0] * v.x + m.m[3][1] * v.y +
                m.m[3][2] * v.z + m.m[3][3] * v.w;

        return out;
}
mat4_t  mat4_multiply(mat4_t m1, mat4_t m2){
        mat4_t out;

        out.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] +
                      m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
        out.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] +
                      m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
        out.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] +
                      m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
        out.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] +
                      m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];

        out.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] +
                      m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
        out.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] +
                      m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
        out.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] +
                      m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
        out.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] +
                      m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];

        out.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] +
                      m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
        out.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] +
                      m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
        out.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] +
                      m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
        out.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] +
                      m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];

        out.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] +
                      m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];
        out.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] +
                      m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];
        out.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] +
                      m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];
        out.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] +
                      m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];
        return out;
}
mat4_t mat4_make_translation(float tx, float ty, float tz){
        // | 1 0 0 tx|
        // | 0 1 0 ty|
        // | 0 0 1 tz|
        // | 0 0 0  1|
        
        mat4_t m = mat4_identity();
        m.m[0][3] = tx;
        m.m[1][3] = ty;
        m.m[2][3] = tz;

        return m;
}
mat4_t mat4_make_rotation_z(float angle){
        float c = cos(angle);
        float s = sin(angle);

        mat4_t m = mat4_identity();
        m.m[0][0] = c;
        m.m[0][1] = -s;
        m.m[1][0] = s;
        m.m[1][1] = c;

        return m;
}
mat4_t mat4_make_rotation_x(float angle){
        float c = cos(angle);
        float s = sin(angle);

        mat4_t m = mat4_identity();
        m.m[1][1] = c;
        m.m[1][2] = -s;
        m.m[2][1] = s;
        m.m[2][2] = c;

        return m;
}
mat4_t mat4_make_rotation_y(float angle){
        float c = cos(angle);
        float s = sin(angle);

        mat4_t m = mat4_identity();
        m.m[0][0] = c;
        m.m[0][2] = s;
        m.m[2][0] = -s;
        m.m[2][2] = c;

        return m;
}
