#include <stdio.h>
#include <platform_sdl.h>
#include <wf_common.h>
#include <math.h>
#include <c_renderer.h>
#include <c_rasterizer.h>
#include <m_type.h>
#include <string.h>
#include <m_util.h>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stdout, "%s running without loaded object", argv[0]);
	}

	wf_platform_t *platform = NULL;

	if (!wf_platform_init(&platform, WF_INTERNAL_WIDTH, WF_INTERNAL_HEIGHT,
			      WF_WINDOW_SCALE)) {
		fprintf(stderr, "Failed to initialize WarpFrame platform.\n");
		return 1;
	}

	wf_input_t input = { 0 };
	float time = 0.0f;

	c_renderer_t *renderer;
	c_renderer_init(&renderer);

	// Cube vertices
	// Coordinate convention:
	// x: screen x
	// y: screen y
	// z: depth

	static c_rasterizer_vertex_t cube_vertices[] = {
		// front face, near
		{ 100, 60, 50 }, // 0 front top-left
		{ 180, 60, 50 }, // 1 front top-right
		{ 180, 140, 50 }, // 2 front bottom-right
		{ 100, 140, 50 }, // 3 front bottom-left

		// back face, far
		{ 130, 30, 150 }, // 4 back top-left
		{ 210, 30, 150 }, // 5 back top-right
		{ 210, 110, 150 }, // 6 back bottom-right
		{ 130, 110, 150 }, // 7 back bottom-left
	};

	static int cube_indices[][3] = {
		// front face
		{ 0, 1, 2 },
		{ 0, 2, 3 },

		// back face
		{ 5, 4, 7 },
		{ 5, 7, 6 },

		// left face
		{ 4, 0, 3 },
		{ 4, 3, 7 },

		// right face
		{ 1, 5, 6 },
		{ 1, 6, 2 },

		// top face
		{ 4, 5, 1 },
		{ 4, 1, 0 },

		// bottom face
		{ 3, 2, 6 },
		{ 3, 6, 7 },
	};

	int cube_triangle_count =
		sizeof(cube_indices) / sizeof(cube_indices[0]);

	mat4i_t *mat1 = m_mat4i_create();
	m_mat4i_destroy(mat1);

	int counter = 0;

	while (!input.quit) {
		c_renderer_clean(renderer);
		wf_platform_poll_input(&input);
		float dt = wf_platform_get_delta_time(platform);
		time += dt;
		//fprintf(stdout, "Delta Time: %f\n", time);

		//		wf_platform_clear(platform, r, g, b);

		for (int i = 0; i < cube_triangle_count; i++) {
			int i0 = cube_indices[i][0];
			int i1 = cube_indices[i][1];
			int i2 = cube_indices[i][2];

			c_rasterizer_triangle_t tri = { cube_vertices[i0],
							cube_vertices[i1],
							cube_vertices[i2], 0 };

			c_rasterizer_draw_triangle_solid(renderer, tri,
							 0xFF0000);
		}

#ifdef WF_DEBUG
		c_rasterizer_put_pixel(renderer, cube_vertices[0].x,
				       cube_vertices[0].y, 0xFF0000);
		c_rasterizer_put_pixel(renderer, cube_vertices[1].x,
				       cube_vertices[1].y, 0xFF0000);
		c_rasterizer_put_pixel(renderer, cube_vertices[2].x,
				       cube_vertices[2].y, 0xFF0000);
		c_rasterizer_put_pixel(renderer, cube_vertices[3].x,
				       cube_vertices[3].y, 0xFF0000);
#endif

		wf_platform_present(platform, renderer->color_buffer);

		counter += 1;
	}

	wf_platform_shutdown(platform);

	return 0;
}
