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

int window_width = 0;
int window_height = 0;
rect_t rect1 = { 0 };
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* color_buffer_texture = NULL;
is_running = false;
uint32_t* color_buffer = NULL;


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
		return 1;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer) {
		fprintf(stderr, "Failed to create Renderer.\n");
		return 1;
	}

	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	return true;
}

void setup(void) {
	color_buffer = (uint32_t*)malloc(sizeof(uint32_t) * window_width * window_height);

	if (!color_buffer) {
		fprintf(stderr, "Failed to allocate color buffer.\n");
	}

	color_buffer_texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		window_width,
		window_height
	);

	if (!color_buffer_texture) {
		fprintf(stderr, "Failed to create color buffer texture");
	}
}

void destroy_window(void) {

	free(color_buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void process_input(void) {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {

	case SDL_QUIT:
		is_running = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			is_running = false;
		}
		break;

	default:
		break;
	}

}

void draw_point(int x, int y, uint32_t color) {
	color_buffer[(window_width * y) + x] = color;
}

void draw_rect(rect_t rect, uint32_t color) {
	for (int j = 0; j <= rect.h; j++) {
		for (int i =0; i < rect.w; i++) {
			draw_point( rect.x + i , rect.y + j, color);
		}
	}
}


void render_color_buffer(void){
	SDL_UpdateTexture(
		color_buffer_texture,
		NULL,
		color_buffer, //Copy color_buffer to the texture. 
		(int)(window_width * sizeof(uint32_t))
	);
	SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}


void update(void) {

}

void clear_color_buffer(uint32_t color) {
	for(size_t i = 0; i < window_height * window_width; i++) {
		color_buffer[i] = color;
	}
}

void render(rect_t rect) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);

	draw_rect(rect,0xFFFFFFFF);

	render_color_buffer();
	clear_color_buffer(0xFF000000);

	SDL_RenderPresent(renderer);
}


int main(int argc, char* argv[]) {

	is_running = initialize_window();
	int temp = 20;
	rect_t rect1 = { .x = temp, .y = temp, .h = temp, .w = temp };

	setup();

	while (is_running) {
		process_input();
		update();
		render(rect1);
	}
	destroy_window();
	return 0;
}