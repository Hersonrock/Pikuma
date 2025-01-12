#include "display.h"
#include "vector.h" 

#define N_POINTS  9 * 9 * 9 
vect3_t cube_points[N_POINTS];
vect2_t projected_points[N_POINTS];

float fov_factor = 128;

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

	int point_count = 0;

	for (float x = -1; x <= 1; x += 0.25f) {
		for (float y = -1; y <= 1; y += 0.25f) {
			for (float z = -1; z <= 1; z += 0.25f) {
				vect3_t new_point = { x, y, z};
				cube_points[point_count++] = new_point;
			}
		}
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

vect2_t project_point(vect3_t point) {
	vect2_t projected_point = {
		.x = point.x * fov_factor,
		.y = point.y * fov_factor
	};

	return projected_point;
}


void update(void) {
	for (int i = 0; i < N_POINTS; i++) {
		vect3_t point = cube_points[i];

		vect2_t projected_point = project_point(point);
		projected_points[i] = projected_point;
	}
}



void render(rect_t rect) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);


	//draw_rect(rect, 0xFFFFFFFF);
	for (int i = 0; i < N_POINTS; i++) {
		rect_t rect = {
			.x = projected_points[i].x + window_width / 2,
			.y = projected_points[i].y + window_height / 2,
			.h = 5,
			.w = 5,
		};
		draw_rect(rect, 0xFFFFFFFF);
	}

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