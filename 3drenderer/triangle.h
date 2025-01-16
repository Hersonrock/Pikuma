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
#endif //TRIANGLE