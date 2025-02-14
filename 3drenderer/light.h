#ifndef LIGHT
#define LIGHT
#include <stdint.h>
#include "vector.h"
#include "triangle.h"

typedef struct{
        vect3_t direction;
}light_t;

extern light_t light;


uint32_t light_apply_intensity(uint32_t color, float factor);
float get_light_factor(vect3_t light_vector, vect3_t *vertices);
#endif  //LIGHT

