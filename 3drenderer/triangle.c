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

       if(v0.y > v1.y){
               vect2_swap(&v0,&v1);
       }
       if(v1.y > v2.y){
               vect2_swap(&v1, &v2);
       }
       if(v0.y > v1.y){
               vect2_swap(&v0,&v1);
       }
       t->points[0] = v0;
       t->points[1] = v1;
       t->points[2] = v2;
       
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
void fill_flat_bottom_triangle(triangle_t t, vect2_t mid, uint32_t color){
        float inv_slope1;
        float inv_slope2;
        inv_slope1 = (float)(t.points[1].x - t.points[0].x) / 
                (t.points[1].y - t.points[0].y);
        inv_slope2 = (float)(mid.x - t.points[0].x) / 
                (mid.y - t.points[0].y);
        float x_start = t.points[0].x;
        float x_end = t.points[0].x;
        for(int y = t.points[0].y; y <= mid.y; y++){
                draw_line(x_start, y, x_end, y, color); 
                x_start += inv_slope1;
                x_end += inv_slope2;
        }
}

void fill_flat_top_triangle(triangle_t t, vect2_t mid, uint32_t color){
        float inv_slope1;
        float inv_slope2;
        inv_slope1 = (float)(t.points[1].x - t.points[2].x) / 
                (t.points[1].y - t.points[2].y);
        inv_slope2 = (float)(mid.x - t.points[2].x) / 
                (mid.y - t.points[2].y);
        float x_start = t.points[2].x;
        float x_end = t.points[2].x;
        for(int y = t.points[2].y; y >= mid.y; y--){
                draw_line(x_start, y, x_end, y, color); 
                x_start -= inv_slope1;
                x_end -= inv_slope2;
        }

}
void draw_filled_triangle(triangle_t triangle, uint32_t color){
        triangle_t t = triangle;

        triangle_sort(&t);

        vect2_t m_point = triangle_m_point(t);
        fill_flat_bottom_triangle(t, m_point, color);
        fill_flat_top_triangle(t, m_point, color);
}
