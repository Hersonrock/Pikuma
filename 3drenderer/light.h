#ifndef LIGHT
#define LIGHT
#include <stdint.h>
#include "vector.h"
#include "triangle.h"


uint32_t light_apply_intensity(uint32_t color, float factor);
float get_light_factor(vect3_t light_vector, vect3_t *vertices);
#endif  //LIGHT

