#include "display.h"
#include "vector.h" 
#include "mesh.h"
#include "array.h"
#include "load.h"
#include "test.h"

/// Object(.obj) files
const char *obj1 = "cube.obj";
const char *obj2 = "f22.obj";
const char *obj3 = "WPveil.obj";
const char *obj4 = "WPABinder.obj";

/// TIME
#define FPS 120
#define FRAME_TARGET_TIME (1000 / FPS)
uint32_t previous_frame_time = 0;

//RENDER MODES CONTROL
bool wireframe_mode1 = true;
bool wireframe_mode2 = false;
bool fill_mode = false;
bool fill_wireframe_mode = false;
bool face_culling_mode = false;

/// GAME LOOP
bool is_running = false;

/// TRIANGLE , ROTATION &  PROJECTION
triangle_t* triangles_to_render = NULL; 
vect3_t camera_position = { .x = 0, .y = 0, .z = 0};
float fov_factor = 320;

/// DISPLAY & BUFFER
int32_t window_width = 0;
uint32_t window_height = 0;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* color_buffer_texture = NULL;
uint32_t* color_buffer = NULL;

void setup(void) {
	color_buffer = (uint32_t*)malloc(sizeof(uint32_t) *
                                             window_width *
                                             window_height);

	if (!color_buffer) {
		fprintf(stderr, "Failed to allocate color buffer.\n");
                is_running = false;
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
                is_running = false;
	}

        if(load_obj(obj4)){
                is_running = false;
        }
        load_obj_mesh_data(obj_vertices, obj_faces);
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
			mesh.rotation.y += 0.1f;
		}
		if (event.key.keysym.sym == SDLK_LEFT) {
			mesh.rotation.y -= 0.1f;
		}
		if (event.key.keysym.sym == SDLK_UP) {
			mesh.rotation.x += 0.1f;
		}
		if (event.key.keysym.sym == SDLK_DOWN) {
			mesh.rotation.x -= 0.1f;
		}
		if (event.key.keysym.sym == SDLK_KP_MULTIPLY) {
			mesh.rotation.z += 0.1f;
		}
		if (event.key.keysym.sym == SDLK_KP_DIVIDE) {
			mesh.rotation.z -= 0.1f;
		}
                if(event.key.keysym.sym == SDLK_1){
                        wireframe_mode1 = true;
                        wireframe_mode2 = false;
                        fill_mode = false;
                        fill_wireframe_mode = false;
                }
                if(event.key.keysym.sym == SDLK_2){
                        wireframe_mode1 = false;
                        wireframe_mode2 = true;
                        fill_mode = false;
                        fill_wireframe_mode = false;
                }
                if(event.key.keysym.sym == SDLK_3){
                        wireframe_mode1 = false;
                        wireframe_mode2 = false;
                        fill_mode = true;
                        fill_wireframe_mode = false;
                }
                if(event.key.keysym.sym == SDLK_4){
                        wireframe_mode1 = false;
                        wireframe_mode2 = false;
                        fill_mode = false;
                        fill_wireframe_mode = true;
                }
                if(event.key.keysym.sym == SDLK_c){
                        face_culling_mode = !face_culling_mode;
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
	uint32_t time_to_wait = FRAME_TARGET_TIME -
                                  (SDL_GetTicks() - 
                                previous_frame_time);

	if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
		SDL_Delay(time_to_wait);
	}

	previous_frame_time = SDL_GetTicks();

	//RE-Initalize triangles to render.
	triangles_to_render = NULL;
	uint32_t num_faces = array_length(mesh.faces);
	for (size_t i = 0; i < num_faces; i++) {
		face_t mesh_face = mesh.faces[i];
		vect3_t face_vertices[3];
		face_vertices[0] = mesh.vertices[mesh_face.a - 1];
		face_vertices[1] = mesh.vertices[mesh_face.b - 1];
		face_vertices[2] = mesh.vertices[mesh_face.c - 1];

                vect3_t transformed_vertex[3];
                for (size_t j = 0; j < 3; j++) {
                        transformed_vertex[j] = face_vertices[j];
                        transformed_vertex[j] = vec3_rotate_x(
                                                      transformed_vertex[j],
                                                      mesh.rotation.x);
                        transformed_vertex[j] = vec3_rotate_y(
                                                      transformed_vertex[j],
                                                      mesh.rotation.y);
                        transformed_vertex[j] = vec3_rotate_z(
                                                      transformed_vertex[j],
                                                      mesh.rotation.z);

                        transformed_vertex[j].z += 5;
                }
                //Face culling
                if(face_culling_mode){
                        vect3_t normal = triangle_normal(transformed_vertex[0],
                                        transformed_vertex[1],
                                        transformed_vertex[2]);
                        vect3_t camera_ray = vect3_sub(camera_position,
                                        transformed_vertex[0]);

                        if(vect3_dot(normal, camera_ray) < 0) continue;
                }

                vect2_t projected_point[3];

                for (size_t j = 0; j < 3; j++) {
			projected_point[j] = project_point(
                                                        transformed_vertex[j]);
			
			projected_point[j].x += (window_width / 2);
			projected_point[j].y += (window_height / 2);
		}

                float avg_depth;
                avg_depth = (transformed_vertex[0].z +
                            transformed_vertex[1].z +
                            transformed_vertex[2].z) / 3;

                triangle_t projected_triangle = {
                        .points = {
                                {projected_point[0].x, projected_point[0].y},
                                {projected_point[1].x, projected_point[1].y},
                                {projected_point[2].x, projected_point[2].y},
                        },
                        .color = mesh_face.color,
                        .avg_depth = avg_depth
                };

		array_push(triangles_to_render, projected_triangle);
	}
        triangle_depth_sort(triangles_to_render);
}

void render() {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);

	rect_t rect = { 0 };
	uint32_t num_triangles = array_length(triangles_to_render);
	for (size_t i = 0; i < num_triangles; i++) {
		triangle_t triangle = triangles_to_render[i];
                if(wireframe_mode1){
                        for(int j = 0; j < 3; j++){
                                rect.x = (uint32_t)triangle.points[j].x;
                                rect.y = (uint32_t)triangle.points[j].y;
                                rect.w = 3;
                                rect.h = 3;
                                draw_rect(rect, RED);
                        }
                }
                if(wireframe_mode1 || wireframe_mode2 || fill_wireframe_mode){
                        draw_triangle(
                                        (uint32_t)triangle.points[0].x,
                                        (uint32_t)triangle.points[0].y,
                                        (uint32_t)triangle.points[1].x,
                                        (uint32_t)triangle.points[1].y,
                                        (uint32_t)triangle.points[2].x,
                                        (uint32_t)triangle.points[2].y,
                                        GREEN
                                     );
                }

                 if(fill_mode || fill_wireframe_mode){
                         draw_filled_triangle(triangle, triangle.color);
                 }
	}

	array_free(triangles_to_render);

	render_color_buffer();
	clear_color_buffer(BLACK);

	SDL_RenderPresent(renderer);
}

void free_resources(void) {
	free(color_buffer);
	array_free(mesh.faces);
	array_free(mesh.vertices);
}

#ifdef RUN_TESTS
int main(int argc, char* argv[]) {
        printf("Running tests...\n");

        run_all_tests();
        return 0;
}
#else
int main(int argc, char* argv[]) {

	is_running = initialize_window();

        setup();

	while (is_running) {
		process_input();
		update();
		render();
	}
	destroy_window();
	free_resources();

	return 0;
}
#endif //RUN_TESTS
