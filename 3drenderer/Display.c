#include "display.h"

bool initialize_window(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initializing window.\n");
		return false;
	}
	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);
	window_width = display_mode.w;
	window_height = display_mode.h;

	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		window_width,
		window_height,
		SDL_WINDOW_BORDERLESS
	);

	if (!window) {
		fprintf(stderr, "Failed to create Window.\n");
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer) {
		fprintf(stderr, "Failed to create Renderer.\n");
		return false;
	}

	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	return true;
}

void draw_pixel(uint32_t x, uint32_t y, uint32_t color) {
	if (x < window_width && y < window_height){
		color_buffer[(window_width * y) + x] = color;
	}
}

void draw_line(int x0, int y0, int x1, int y1, uint32_t color) {
	int delta_x = (x1 - x0);
	int delta_y = (y1 - y0);

	int side_lenght = abs(delta_x) >= abs(delta_y) ? abs(delta_x) : abs(delta_y);

	float x_inc = delta_x / (float)side_lenght;
	float y_inc = delta_y / (float)side_lenght;

	float current_x = x0;
	float current_y = y0;

	for (size_t i = 0; i <= side_lenght; i++) {
		draw_pixel(round(current_x), round(current_y), color);
		current_x += x_inc;
		current_y += y_inc;
	}
}

void draw_rect(rect_t rect, uint32_t color) {
	for (size_t j = 0; j <= rect.h; j++) {
		for (size_t i = 0; i < rect.w; i++) {
			draw_pixel(rect.x + i, rect.y + j, color);
		}
	}
}

void draw_triangle(int x0, int y0,
	int x1, int y1,
	int x2, int y2,
	uint32_t color) {
	draw_line(x0, y0, x1, y1, color);
	draw_line(x1, y1, x2, y2, color);
	draw_line(x2, y2, x0, y0, color);
}

void render_color_buffer(void) {
	SDL_UpdateTexture(
		color_buffer_texture,
		NULL,
		color_buffer, //Copy color_buffer to the texture. 
		(int)(window_width * sizeof(uint32_t))
	);
	SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void clear_color_buffer(uint32_t color) {
	for (size_t i = 0; i < window_height * window_width; i++) {
		color_buffer[i] = color;
	}
}


void destroy_window(void) {

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}