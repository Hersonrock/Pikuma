#ifndef TRIANGLE
#define TRIANGLE

#include "vector.h"
#include "display.h"
#include <stdint.h>
#include <stdio.h>

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

void fill_flat_bottom_triangle(triangle_t t, vect2_t mid, uint32_t color);
void fill_flat_top_triangle(triangle_t t, vect2_t mid, uint32_t color);
void draw_filled_triangle(triangle_t triangle, uint32_t color);
#endif //TRIANGLE
