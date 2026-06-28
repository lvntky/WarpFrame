#include <stdio.h>
#include <platform_sdl.h>
#include <wf_common.h>
#include <math.h>
#include <c_renderer.h>
#include <c_rasterizer.h>
#include <m_type.h>
#include <string.h>
#include <m_util.h>
#include <wf_obj_parser.h>
#include <stdlib.h>
#include <wf_e_orientation.h>

/*
  temp code start
 */
static uint32_t random_color(void)
{
	uint8_t r = 64 + rand() % 192;
	uint8_t g = 64 + rand() % 192;
	uint8_t b = 64 + rand() % 192;

	return ((uint32_t)r << 16) | ((uint32_t)g << 8) | ((uint32_t)b);
}

/*
  temp code end
 */

void object_to_screen(vec4f_t *normalized_obj_vertices, int *faces,
		      int vertex_count, int face_count, int *out_count,
		      float angle, c_rasterizer_triangle_t *triangle_list)
{
	vec4f_t view_vertex_list[vertex_count];
	c_renderer_projected_vertex_t projected_vertex_list[vertex_count];
	c_rasterizer_vertex_t screen_vertex_list[vertex_count];

	// Model Matrix
	mat4f_t model_rotation = m_mat4f_rotate(angle, ROTATE_Y);
	mat4f_t model_translation =
		m_mat4f_transform((vec4f_t){ 0.0f, 0.05f, 0.7f, 1.0f });

	// View Matrix
	// the camrera at the origin = identity matrix
	mat4f_t view = m_mat4f_identity();

	for (int i = 0; i < vertex_count; i++) {
		vec4f_t local = normalized_obj_vertices[i];
		local.w = 1.0f;

		// model -> local to world
		// rotate than transfor on screen
		vec4f_t world = m_mat4f_mul_vec4f(model_rotation, local);
		world = m_mat4f_mul_vec4f(model_translation, world);

		// world to view/screen
		vec4f_t view_space = m_mat4f_mul_vec4f(view, world);

		view_vertex_list[i] = view_space;
	}

	/*
	  PROJECTION:
	  view space -> projected/NDC 
	*/
	for (int i = 0; i < vertex_count; i++) {
		c_renderer_create_projected_vertex(view_vertex_list[i],
						   &projected_vertex_list[i]);
	}

	/*
	  VIEWPORT:
	  projected -> screen
	*/
	for (int i = 0; i < vertex_count; i++) {
		screen_vertex_list[i] = c_renderer_create_viewport_vertex(
			projected_vertex_list[i]);
	}

	int triangle_count = 0;

	for (int f = 0; f < face_count; f++) {
		int i0 = faces[f * 3 + 0];
		int i1 = faces[f * 3 + 1];
		int i2 = faces[f * 3 + 2];

		c_rasterizer_vertex_t a = screen_vertex_list[i0];
		c_rasterizer_vertex_t b = screen_vertex_list[i1];
		c_rasterizer_vertex_t c = screen_vertex_list[i2];

		if (!c_renderer_backface_area(a, b, c)) {
			triangle_list[triangle_count++] =
				(c_rasterizer_triangle_t){ a, b, c,
							   random_color() };
		}
	}

	*out_count = triangle_count;
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stdout, "%s running without loaded object", argv[0]);
		goto exit;
	}

	const wf_obj_parsed_t *obj = wf_obj_parse(argv[1]);

	wf_platform_t *platform = NULL;

	if (!wf_platform_init(&platform, WF_INTERNAL_WIDTH, WF_INTERNAL_HEIGHT,
			      WF_WINDOW_SCALE)) {
		fprintf(stderr, "Failed to initialize WarpFrame platform.\n");
		return 1;
	}

	wf_input_t input = { 0 };

	c_renderer_t *renderer;
	c_renderer_init(&renderer);

	int triangle_count = 0;
	vec4f_t *normalized_obj_vertices = wf_obj_normalize(obj);
	int vertex_count = obj->vertex_count;
	int face_count = obj->face_count;
	int *faces = obj->faces;
	float rotation_angle = 0.0f;

	c_rasterizer_triangle_t *tri =
		malloc(face_count * sizeof(c_rasterizer_triangle_t));

	while (!input.quit) {
		c_renderer_clean(renderer);
		wf_platform_poll_input(&input);

		object_to_screen(normalized_obj_vertices, faces, vertex_count,
				 face_count, &triangle_count, rotation_angle,
				 tri);

		for (int i = 0; i < triangle_count; i++) {
			c_rasterizer_draw_triangle_solid(renderer, tri[i]);
		}

		wf_platform_present(platform, renderer->color_buffer);

		rotation_angle += 0.05f;
	}

	wf_platform_shutdown(platform);
exit:
	return 0;
}
