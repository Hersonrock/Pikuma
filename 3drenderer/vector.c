#include "vector.h"

void vect3_rotate_x(vect3_t *v, float angle){
        float y = v->y;
        float z = v->z;

        v->y = y * cos(angle) - z * sin(angle);
        v->z = y * sin(angle) + z * cos(angle);
}
void vect3_rotate_y(vect3_t *v, float angle) {
        float x = v->x;
        float z = v->z;

        v->x = x * cos(angle) - z * sin(angle);
        v->z = x * sin(angle) + z * cos(angle);
}
void vect3_rotate_z(vect3_t *v, float angle) {
        float x = v->x;
        float y = v->y;

        v->x = x * cos(angle) - y * sin(angle);
        v->y = x * sin(angle) + y * cos(angle);
}


/////////////////////VECTOR 2D//////////////////
float vect2_length(vect2_t v){
        float length = v.x * v.x + v.y * v.y;
        length = sqrt(length);
        return length;
}

vect2_t vect2_add(vect2_t v1, vect2_t v2){
        vect2_t result;
        result.x = v1.x + v2.x;
        result.y = v1.y + v2.y;

        return result;
}
vect2_t vect2_sub(vect2_t v1, vect2_t v2){
        vect2_t result;
        result.x = v1.x - v2.x;
        result.y = v1.y - v2.y;

        return result;
}
vect2_t vect2_mult(vect2_t v, float factor){
        vect2_t result;
        result.x = v.x * factor;
        result.y = v.y * factor;

        return result;
}
vect2_t vect2_div(vect2_t v, float factor){
        vect2_t result;
        assert(factor != 0);
        float factor_div = 1 / factor;
        result.x = v.x * factor_div;
        result.y = v.y * factor_div;

        return result;
}
float vect2_dot(vect2_t v1, vect2_t v2){
        float result;
        result = v1.x * v2.x + v1.y * v2.y;
        return result;
}
void vect2_normalize(vect2_t *v){
        *v = vect2_div(*v, vect2_length(*v));
}
void vect2_swap(vect2_t *v1, vect2_t *v2){
       
        vect2_t temp = *v1;
        v1->x = v2->x;
        v1->y = v2->y;
        v2->x = temp.x;
        v2->y = temp.y;
}
/////////////////////VECTOR 3D//////////////////
float vect3_length(vect3_t v){
        float length = v.x * v.x + v.y * v.y + v.z * v.z;
        length = sqrt(length);
        return length;
}
vect3_t vect3_add(vect3_t v1, vect3_t v2){
        vect3_t result;
        result.x = v1.x + v2.x;
        result.y = v1.y + v2.y;
        result.z = v1.z + v2.z;

        return result;
}
vect3_t vect3_sub(vect3_t v1, vect3_t v2){
        vect3_t result;
        result.x = v1.x - v2.x;
        result.y = v1.y - v2.y;
        result.z = v1.z - v2.z;

        return result;
}
vect3_t vect3_mult(vect3_t v, float factor){
        vect3_t result;
        result.x = v.x * factor;
        result.y = v.y * factor;
        result.z = v.z * factor;

        return result;
}
vect3_t vect3_div(vect3_t v, float factor){
        vect3_t result = {0};
        assert(factor != 0);
        float factor_div = 1 / factor;
        result.x = v.x * factor_div;
        result.y = v.y * factor_div;
        result.z = v.z * factor_div;

        return result;
}
float vect3_dot(vect3_t v1, vect3_t v2){
        float result;
        result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
        return result;
}
vect3_t vect3_cross(vect3_t v1, vect3_t v2){
        vect3_t result;
        result.x = v1.y * v2.z - v2.y * v1.z;
        result.y = v2.x * v1.z - v1.x * v2.z;
        result.z = v1.x * v2.y - v2.x * v1.y;

        return result;
}
void vect3_normalize(vect3_t *v){
        *v = vect3_div(*v, vect3_length(*v));
}
vect4_t vec4_from_vec3(vect3_t v){
        vect4_t out;

        out.x = v.x;
        out.y = v.y;
        out.z = v.z;
        out.w = 1;

        return out;
}
vect3_t vec3_from_vec4(vect4_t v){
        vect3_t out;
        out.x = v.x;
        out.y = v.y;
        out.z = v.z;

        return out;
}
