#include "triangle.h"
/////////////////TRIANGLE////////
vect3_t triangle_normal(vect3_t v1, vect3_t v2, vect3_t v3){
        vect3_t base1 = vect3_sub(v2, v1);
        vect3_t base2 = vect3_sub(v3, v1);
        vect3_t normal = vect3_cross(base1,base2);
        vect3_normalize(&normal);
        
        return normal;
}
void triangle_sort(triangle_t *t){
       vect2_t v0, v1, v2;

       v0 = t->points[0];
       v1 = t->points[1];
       v2 = t->points[2];

       if(t->points[0].y < t->points[1].y && t->points[0].y < t->points[2].y){
                if(t->points[1].y < t->points[2].y){
                        t->points[0] = v2;
                        t->points[1] = v1;
                        t->points[2] = v0;
                } else {
                        t->points[0] = v1;
                        t->points[1] = v2;
                        t->points[2] = v0;
                }
       }
       else if(t->points[1].y < t->points[0].y && t->points[1].y < t->points[2].y){
                if(t->points[0].y < t->points[2].y){
                        t->points[0] = v2;
                        t->points[1] = v0;
                        t->points[2] = v1;
                } else {
                        t->points[0] = v0;
                        t->points[1] = v2;
                        t->points[2] = v1;
                }
       }
       else if(t->points[2].y < t->points[0].y && t->points[2].y < t->points[1].y){
                if(t->points[0].y < t->points[1].y){
                        t->points[0] = v1;
                        t->points[1] = v0;
                        t->points[2] = v2;
                } else {
                        t->points[0] = v0;
                        t->points[1] = v1;
                        t->points[2] = v2;
                }
       }
}


vect2_t triangle_m_point(triangle_t t){
        vect2_t m;
        m.y = t.points[1].y;
        m.x = ((t.points[2].x - t.points[0].x)  *
               (t.points[1].y - t.points[0].y)) /
               (t.points[2].y - t.points[0].y)  +
               t.points[0].x;

        return m;
}

