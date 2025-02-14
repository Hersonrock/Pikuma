#include "light.h"



uint32_t light_apply_intensity(uint32_t color, float factor){
                uint32_t base_color = color;
                uint8_t a = (base_color >> 24) & 0xFF;
                uint8_t r = (base_color >> 16) & 0xFF;
                uint8_t g = (base_color >> 8) & 0xFF;
                uint8_t b = base_color & 0xFF;

                r = (uint8_t)(r * factor);
                g = (uint8_t)(g * factor);
                b = (uint8_t)(b * factor);

                uint32_t shaded_color = (a << 24) | (r << 16) | (g << 8) | b;
                printf("shaded_color= %x\n", shaded_color); 
                return shaded_color;
}
float get_light_factor(vect3_t light_vector, vect3_t *vertices){
                vect3_t normal = triangle_normal(vertices[0],
                                                 vertices[1],
                                                 vertices[2]);
                vect3_normalize(&normal);

                vect3_t light_ray = vect3_sub(light_vector, vertices[0]);
                vect3_normalize(&light_ray);

                float light_factor = vect3_dot(normal, light_ray);
                printf("light_factor %.2f\n", light_factor);

                return  light_factor;

}
