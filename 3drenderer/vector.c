#include "vector.h"
#include <math.h>

vect3_t vec3_rotate_x(vect3_t v, float angle){
	vect3_t rotated_vector = {
		.x = v.x,
		.y = v.y * cos(angle) - v.z * sin(angle),
		.z = v.y * sin(angle) + v.z * cos(angle)
	};

	return rotated_vector;
}
vect3_t vec3_rotate_y(vect3_t v, float angle) {
	vect3_t rotated_vector = {
		.x = v.x * cos(angle) - v.z * sin(angle),
		.y = v.y,
		.z = v.x * sin(angle) + v.z * cos(angle)
	};

	return rotated_vector;
}
vect3_t vec3_rotate_z(vect3_t v, float angle) {
	vect3_t rotated_vector = {
		.x = v.x * cos(angle) - v.y * sin(angle),
		.y = v.x * sin(angle) + v.y * cos(angle),
		.z = v.z
	};

	return rotated_vector;
}


/////////////////////VECTOR 2D//////////////////
float vect2_lenght(vect2_t v){
        float lenght = v.x * v.x + v.y * v.y;
        lenght = sqrt(lenght);
        return lenght;
}

vect2_t vect2_add(vect2_t v1, vect2_t v2){
        vect2_t result;
        result.x = v1.x + v2.x;
        result.y = v1.y + v2.y;

        return result;
}
/////////////////////VECTOR 3D//////////////////
float vect3_lenght(vect3_t v){
        float lenght = v.x * v.x + v.y * v.y + v.z * v.z;
        lenght = sqrt(lenght);
        return lenght;
}
vect3_t vect3_add(vect3_t v1, vect3_t v2){
        vect3_t result;
        result.x = v1.x + v2.x;
        result.y = v1.y + v2.y;
        result.z = v1.z + v2.z;

        return result;
}
