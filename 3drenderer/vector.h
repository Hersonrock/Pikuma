#ifndef VECTOR
#define VECTOR
#include <assert.h>
#include <math.h>
typedef struct {
	float x;
	float y;
}vect2_t;

typedef struct {
	float x;
	float y;
	float z;
}vect3_t;

typedef struct {
	float x;
	float y;
	float z;
	float w;
}vect4_t;

void vect3_rotate_x(vect3_t *v, float angle);
void vect3_rotate_y(vect3_t *v, float angle);
void vect3_rotate_z(vect3_t *v, float angle);
/////////////////////VECTOR 2D//////////////////
float vect2_length(vect2_t v);
vect2_t vect2_add(vect2_t v1, vect2_t v2);
vect2_t vect2_sub(vect2_t v1, vect2_t v2);
vect2_t vect2_mult(vect2_t v, float factor);
vect2_t vect2_div(vect2_t v, float factor);
float vect2_dot(vect2_t v1, vect2_t v2);
void vect2_normalize(vect2_t *v);
void vect2_swap(vect2_t *v1, vect2_t *v2);
/////////////////////VECTOR 3D//////////////////
float vect3_length(vect3_t v);
vect3_t vect3_add(vect3_t v1, vect3_t v2);
vect3_t vect3_sub(vect3_t v1, vect3_t v2);
vect3_t vect3_mult(vect3_t v, float factor);
vect3_t vect3_div(vect3_t v, float factor);
float vect3_dot(vect3_t v1, vect3_t v2);
vect3_t vect3_cross(vect3_t v1, vect3_t v2);
void vect3_normalize(vect3_t *v);
/////////////////////VECTOR 4D//////////////////
/// Conversion
vect4_t vec4_from_vec3(vect3_t v);
vect3_t vec3_from_vec4(vect4_t v);


#endif //VECTOR
