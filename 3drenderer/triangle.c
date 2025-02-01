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
        float x0 = t.points[0].x;
        float y0 = t.points[0].y;
        float x1 = t.points[1].x;
        float y1 = t.points[1].y;

        inv_slope1 = (x1 - x0) / (y1 - y0);
        inv_slope2 = (mid.x - x0) / (mid.y - y0);
        printf("Slopes [%.2f][%.2f]\n", inv_slope1, inv_slope2);
        float x_start = x0;
        float x_end = x0;

        for(int y = y0; y <= mid.y; y++){
                draw_line(x_start, y, x_end, y, color); 
                x_start += inv_slope1;
                x_end += inv_slope2;
        }
}

void fill_flat_top_triangle(triangle_t t, vect2_t mid, uint32_t color){
        float inv_slope1;
        float inv_slope2;
        float x1 = t.points[1].x;
        float y1 = t.points[1].y;
        float x2 = t.points[2].x;
        float y2 = t.points[2].y;

        inv_slope1 = (x1 - x2) / (y1 - y2);
        inv_slope2 = (mid.x - x2) / (mid.y - y2);
        printf("Slopes [%.2f][%.2f]\n", inv_slope1, inv_slope2);
        float x_start = x2;
        float x_end = x2;

        for(int y = y2; y >= mid.y; y--){
                draw_line(x_start, y, x_end, y, color); 
                x_start -= inv_slope1;
                x_end -= inv_slope2;
        }

}
void draw_filled_triangle(triangle_t triangle, uint32_t color){
        triangle_t t = triangle;

        triangle_sort(&t);
        printf("[%.2f,%.2f][%.2f,%.2f][%.2f,%.2f]\n", t.points[0].x,
                                                      t.points[0].y,
                                                      t.points[1].x,
                                                      t.points[1].y,
                                                      t.points[2].x,
                                                      t.points[2].y
                                                      );

        if(t.points[0].y == t.points[1].y){
                printf("Flat top recognized\n");
                fill_flat_top_triangle(t, t.points[1], color);
        }else if(t.points[2].y == t.points[1].y){
                printf("Flat bottom recognized\n");
                fill_flat_bottom_triangle(t, t.points[1], color);
        }else {
                printf("Whole triangle recognized\n");
                vect2_t m_point = triangle_m_point(t);
                printf("m_point = [%.2f,%.2f]\n", m_point.x, m_point.y);
                fill_flat_bottom_triangle(t, m_point, color);
                fill_flat_top_triangle(t, m_point, color);
        }
}
