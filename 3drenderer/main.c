#include "display.h"
#include "vector.h" 

//#define N_POINTS  9 * 9 * 9 
#define N_POINTS  8
#define FPS 120
#define FRAME_TARGET_TIME (1000 / FPS)

// Array if Vertices
vect3_t cube_vertices[8] = {
	{.x =  1, .y =  1, .z =  1},
	{.x = -1, .y =  1, .z =  1},
	{.x = -1, .y =  1, .z = -1},
	{.x =  1, .y =  1, .z = -1},
	{.x =  1, .y = -1, .z =  1},
	{.x = -1, .y = -1, .z =  1},
	{.x = -1, .y = -1, .z = -1},
	{.x =  1, .y = -1, .z = -1},
};


vect3_t cube_points[N_POINTS];
vect2_t projected_points[N_POINTS];
vect3_t camera_position = { .x = 0, .y = 0, .z = -5};

vect3_t cube_rotation = { .x = 0, .y = 0, .z = 0 };

float fov_factor = 320;

is_running = false;
uint32_t previous_frame_time = 0;

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

	//for (float x = -1; x <= 1; x += 0.25f) {
	//	for (float y = -1; y <= 1; y += 0.25f) {
	//		for (float z = -1; z <= 1; z += 0.25f) {
	//			vect3_t new_point = { x, y, z};
	//			cube_points[point_count++] = new_point;
	//		}
	//	}
	//}
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
		if (event.key.keysym.sym == SDLK_KP_PLUS) {
			fov_factor += 20;
		}
		if (event.key.keysym.sym == SDLK_KP_MINUS) {
			fov_factor -= 20;
		}
		if (event.key.keysym.sym == SDLK_RIGHT) {
			cube_rotation.y += 0.1f;
		}
		if (event.key.keysym.sym == SDLK_LEFT) {
			cube_rotation.y -= 0.1f;
		}
		if (event.key.keysym.sym == SDLK_UP) {
			cube_rotation.x += 0.1f;
		}
		if (event.key.keysym.sym == SDLK_DOWN) {
			cube_rotation.x -= 0.1f;
		}
		if (event.key.keysym.sym == SDLK_KP_MULTIPLY) {
			cube_rotation.z += 0.1f;
		}
		if (event.key.keysym.sym == SDLK_KP_DIVIDE) {
			cube_rotation.z -= 0.1f;
		}

		break;

	default:
		break;
	}
}

vect2_t project_point(vect3_t point) {
	vect2_t projected_point = {
		.x = (point.x * fov_factor) / (point.z),
		.y = (point.y * fov_factor) / (point.z)
	};

	return projected_point;
}


void update(void) {

	uint32_t time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

	if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
		SDL_Delay(time_to_wait);
	}


	previous_frame_time = SDL_GetTicks();

	for (int i = 0; i < N_POINTS; i++) {
		//vect3_t point = cube_points[i];
		vect3_t point = cube_vertices[i];

		vect3_t transformed_point;
		transformed_point = vec3_rotate_y(point, cube_rotation.y);
		transformed_point = vec3_rotate_x(transformed_point, cube_rotation.x);
		transformed_point = vec3_rotate_z(transformed_point, cube_rotation.z);


		//Move points away from camera.
		transformed_point.z -= camera_position.z;

		vect2_t projected_point = project_point(transformed_point);
		projected_points[i] = projected_point;
	}
}



void render() {
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

	setup();

	while (is_running) {
		process_input();
		update();
		render();
	}
	destroy_window();
	return 0;
}