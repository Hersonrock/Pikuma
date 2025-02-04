#ifndef DISPLAY
#define DISPLAY
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL.h>

/// COLORS
typedef enum{
        RED = 0xFFFF0000,
        GREEN = 0xFF00FF00,
        BLUE = 0xFF0000FF,
        GREY = 0xFFC0C0C0,
        BLACK = 0xFF000000,
        WHITE = 0xFFFFFFFF
}color_t;

typedef struct rect {
	uint32_t x;
	uint32_t y;
	uint32_t w;
	uint32_t h;
}rect_t;

extern uint32_t window_width;
extern uint32_t window_height;

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* color_buffer_texture;
extern uint32_t* color_buffer;

bool initialize_window(void);

void draw_pixel(uint32_t x, uint32_t y, uint32_t color);
void draw_line(int x0, int y0, int x1, int y1, uint32_t color);
void draw_rect(rect_t rect, uint32_t color);
void draw_triangle(int x0, int y0,
				   int x1, int y1,
	               int x2, int y2,
	               uint32_t color
                   );

void render_color_buffer(void);
void clear_color_buffer(uint32_t color);

void destroy_window(void);

#endif //DISPLAY
