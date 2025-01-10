#ifndef DISPLAY
#define DISPLAY
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL.h>


typedef struct rect {
	int x;
	int y;
	int w;
	int h;
}rect_t;

extern int window_width;
extern int window_height;

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* color_buffer_texture;
extern uint32_t* color_buffer;
extern rect_t rect1;


bool initialize_window(void);

void draw_pixel(int x, int y, uint32_t color);
void draw_rect(rect_t rect, uint32_t color);

void render_color_buffer(void);
void clear_color_buffer(uint32_t color);

void destroy_window(void);

#endif //DISPLAY