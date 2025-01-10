#include "display.h"

is_running = false;

int window_width = 0;
int window_height = 0;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* color_buffer_texture = NULL;
uint32_t* color_buffer = NULL;
rect_t rect1 = { 0 };

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

void update(void) {

}

void render(rect_t rect) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);

	draw_rect(rect, 0xFFFFFFFF);

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