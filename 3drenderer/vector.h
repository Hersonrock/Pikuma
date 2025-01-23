#ifndef VECTOR
#define VECTOR

typedef struct {
	float x;
	float y;
}vect2_t;

typedef struct {
	float x;
	float y;
	float z;
}vect3_t;

vect3_t vec3_rotate_x(vect3_t v, float angle);
vect3_t vec3_rotate_y(vect3_t v, float angle);
vect3_t vec3_rotate_z(vect3_t v, float angle);
/////////////////////VECTOR 2D//////////////////
float vect2_lenght(vect2_t v);
vect2_t vect2_add(vect2_t v1, vect2_t v2);
/////////////////////VECTOR 3D//////////////////
float vect3_lenght(vect3_t v);
vect3_t vect3_add(vect3_t v1, vect3_t v2);

#endif //VECTOR
