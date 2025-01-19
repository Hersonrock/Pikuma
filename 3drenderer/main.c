#include "display.h"
#include "vector.h" 
#include "mesh.h"

/// TIME
#define FPS 120
#define FRAME_TARGET_TIME (1000 / FPS)
uint32_t previous_frame_time = 0;
/// 

/// GAME LOOP
bool is_running = false;
///

/// TRIANGLE , ROTATION &  PROJECTION
triangle_t triangles_to_render[N_MESH_FACES]; 
vect3_t cube_rotation = {0};  
vect3_t camera_position = { .x = 0, .y = 0, .z = -5};
float fov_factor = 320;
/// 

/// DISPLAY & BUFFER
uint32_t window_width = 0;
uint32_t window_height = 0;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* color_buffer_texture = NULL;
uint32_t* color_buffer = NULL;
/// 

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

	for (size_t i = 0; i < N_MESH_FACES; i++) {

		face_t mesh_face = mesh_faces[i];

		vect3_t face_vertices[3];
		face_vertices[0] = mesh_vertices[mesh_face.a - 1];
		face_vertices[1] = mesh_vertices[mesh_face.b - 1];
		face_vertices[2] = mesh_vertices[mesh_face.c - 1];

		triangle_t projected_triangle;

		for (size_t j = 0; j < 3; j++) {
			vect3_t transformed_vertex = face_vertices[j];
			transformed_vertex = vec3_rotate_x(transformed_vertex, cube_rotation.x);
			transformed_vertex = vec3_rotate_y(transformed_vertex, cube_rotation.y);
			transformed_vertex = vec3_rotate_z(transformed_vertex, cube_rotation.z);

			transformed_vertex.z -= camera_position.z;
			
			vect2_t projected_point = project_point(transformed_vertex);
			
			projected_point.x += (window_width / 2);
			projected_point.y += (window_height / 2);


			projected_triangle.points[j] = projected_point;
		}
		triangles_to_render[i] = projected_triangle;

	}
}

void render() {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);

	rect_t rect = { 0 };

	draw_line(100, 200, 300, 50, 0xFFFFFFFF);

	for (size_t i = 0; i < N_MESH_FACES; i++) {
		triangle_t triangle = triangles_to_render[i];

		for (size_t j = 0; j < 3; j++) {
			rect.x = triangle.points[j].x;
			rect.y = triangle.points[j].y;
			rect.w = 3;
			rect.h = 3;

			draw_rect(rect, 0xFFFFFFFF);
		}

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