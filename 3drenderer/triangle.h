#ifndef TRIANGLE
#define TRIANGLE

#include "vector.h"
#include <stdint.h>

typedef struct {
	uint32_t a, b, c;
}face_t;

typedef  struct {
	vect2_t points[3];
}triangle_t;
/////////////////TRIANGLE////////
vect3_t triangle_normal(vect3_t v1, vect3_t v2, vect3_t v3);
void triangle_sort(triangle_t *t);
vect2_t triangle_m_point(triangle_t t);
#endif //TRIANGLE
