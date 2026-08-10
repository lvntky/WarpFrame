#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <SDL2/SDL.h>

#include <platform_sdl.h>
#include <wf_common.h>
#include <c_renderer.h>
#include <c_rasterizer.h>
#include <m_type.h>
#include <m_util.h>
#include <wf_obj_parser.h>
#include <wf_e_orientation.h>
#include <wf_texture.h>
#include <wf_control.h>
#include <wf_tile_manager.h>
#include <microui.h>
#include <font8x8_basic.h>

typedef struct {
	SDL_Texture *glyphs[128];
} wf_font_t;

static wf_font_t g_font;

static void wf_font_build(SDL_Renderer *ren)
{
	for (int c = 0; c < 128; c++) {
		uint32_t pixels[8 * 8];
		for (int y = 0; y < 8; y++) {
			uint8_t row = font8x8_basic[c][y];
			for (int x = 0; x < 8; x++) {
				int bit = (row >> x) & 1;
				pixels[y * 8 + x] = bit ? 0xFFFFFFFF :
							  0x00000000;
			}
		}
		SDL_Texture *tex =
			SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA32,
					  SDL_TEXTUREACCESS_STATIC, 8, 8);
		SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
		SDL_UpdateTexture(tex, NULL, pixels, 8 * (int)sizeof(uint32_t));
		g_font.glyphs[c] = tex;
	}
}

static void wf_font_destroy(void)
{
	for (int c = 0; c < 128; c++)
		if (g_font.glyphs[c])
			SDL_DestroyTexture(g_font.glyphs[c]);
}

static void wf_font_draw_text(SDL_Renderer *ren, const char *text, int x, int y,
			      mu_Color color)
{
	for (const unsigned char *p = (const unsigned char *)text; *p; p++) {
		if (*p >= 128) {
			x += 8;
			continue;
		}
		SDL_Texture *g = g_font.glyphs[*p];
		SDL_SetTextureColorMod(g, color.r, color.g, color.b);
		SDL_SetTextureAlphaMod(g, color.a);
		SDL_Rect dst = { x, y, 8, 8 };
		SDL_RenderCopy(ren, g, NULL, &dst);
		x += 8;
	}
}

static int text_width(mu_Font font, const char *text, int len)
{
	(void)font;
	if (len == -1)
		len = (int)strlen(text);
	return len * 8;
}

static int text_height(mu_Font font)
{
	(void)font;
	return 16;
}

static int text_width_cb(mu_Font f, const char *s, int l)
{
	return text_width(f, s, l);
}

static int text_height_cb(mu_Font f)
{
	return text_height(f);
}

static uint32_t random_color(void)
{
	uint8_t r = 64 + rand() % 192;
	uint8_t g = 64 + rand() % 192;
	uint8_t b = 64 + rand() % 192;

	return ((uint32_t)r << 16) | ((uint32_t)g << 8) | ((uint32_t)b);
}

static void mu_render_commands(SDL_Renderer *ren, mu_Context *ctx)
{
	mu_Command *cmd = NULL;
	while (mu_next_command(ctx, &cmd)) {
		switch (cmd->type) {
		case MU_COMMAND_CLIP: {
			SDL_Rect r = { cmd->clip.rect.x, cmd->clip.rect.y,
				       cmd->clip.rect.w, cmd->clip.rect.h };
			SDL_RenderSetClipRect(ren, &r);
			break;
		}
		case MU_COMMAND_RECT: {
			mu_Color c = cmd->rect.color;
			SDL_SetRenderDrawColor(ren, c.r, c.g, c.b, c.a);
			SDL_Rect r = { cmd->rect.rect.x, cmd->rect.rect.y,
				       cmd->rect.rect.w, cmd->rect.rect.h };
			SDL_RenderFillRect(ren, &r);
			break;
		}
		case MU_COMMAND_TEXT: {
			wf_font_draw_text(ren, cmd->text.str, cmd->text.pos.x,
					  cmd->text.pos.y, cmd->text.color);
			break;
		}
		}
	}
}

static int mu_map_mouse_button(uint8_t sdl_button)
{
	switch (sdl_button) {
	case SDL_BUTTON_LEFT:
		return MU_MOUSE_LEFT;
	case SDL_BUTTON_RIGHT:
		return MU_MOUSE_RIGHT;
	case SDL_BUTTON_MIDDLE:
		return MU_MOUSE_MIDDLE;
	default:
		return 0;
	}
}

static void poll_all_input(wf_input_t *input, mu_Context *ctx)
{
	input->key_up = false;
	input->key_down = false;
	input->key_left = false;
	input->key_right = false;
	input->key_escape = false;

	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			input->quit = true;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				input->quit = true;
				input->key_escape = true;
			}
			break;
		case SDL_MOUSEMOTION:
			mu_input_mousemove(ctx, event.motion.x, event.motion.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			mu_input_mousedown(
				ctx, event.button.x, event.button.y,
				mu_map_mouse_button(event.button.button));
			break;
		case SDL_MOUSEBUTTONUP:
			mu_input_mouseup(
				ctx, event.button.x, event.button.y,
				mu_map_mouse_button(event.button.button));
			break;
		case SDL_MOUSEWHEEL:
			mu_input_scroll(ctx, 0, event.wheel.y * -30);
			break;
		case SDL_TEXTINPUT:
			mu_input_text(ctx, event.text.text);
			break;
		}
	}

	const uint8_t *keyboard = SDL_GetKeyboardState(NULL);

	input->key_up = keyboard[SDL_SCANCODE_W] || keyboard[SDL_SCANCODE_UP];
	input->key_down = keyboard[SDL_SCANCODE_S] ||
			  keyboard[SDL_SCANCODE_DOWN];
	input->key_left = keyboard[SDL_SCANCODE_A] ||
			  keyboard[SDL_SCANCODE_LEFT];
	input->key_right = keyboard[SDL_SCANCODE_D] ||
			   keyboard[SDL_SCANCODE_RIGHT];
}

static void wf_control_fill_background(c_renderer_t *renderer,
				       wf_control_color_t color)
{
	uint32_t packed = ((uint32_t)color.r << 16) | ((uint32_t)color.g << 8) |
			  (uint32_t)color.b;
	for (size_t i = 0; i < renderer->data_len; i++)
		renderer->color_buffer[i] = packed;
}

void object_to_screen(vec4f_t *normalized_obj_vertices, wf_face_t *faces,
		      vec2f_t *uvs, int vertex_count, int face_count,
		      int *out_count, float angle, float distance,
		      c_rasterizer_triangle_t *triangle_list)
{
	vec4f_t view_vertex_list[vertex_count];
	c_renderer_projected_vertex_t projected_vertex_list[vertex_count];
	c_rasterizer_vertex_t screen_vertex_list[vertex_count];

	mat4f_t model_rotation = m_mat4f_rotate(angle, ROTATE_Y);

	mat4f_t model_translation =
		m_mat4f_transform((vec4f_t){ 0.0f, 0.00f, distance, 1.0f });

	mat4f_t view = m_mat4f_identity();

	for (int i = 0; i < vertex_count; i++) {
		vec4f_t local = normalized_obj_vertices[i];
		local.w = 1.0f;

		vec4f_t world = m_mat4f_mul_vec4f(model_rotation, local);
		world = m_mat4f_mul_vec4f(model_translation, world);

		vec4f_t view_space = m_mat4f_mul_vec4f(view, world);

		view_vertex_list[i] = view_space;
	}

	for (int i = 0; i < vertex_count; i++) {
		c_renderer_create_projected_vertex(view_vertex_list[i],
						   &projected_vertex_list[i]);
	}

	for (int i = 0; i < vertex_count; i++) {
		screen_vertex_list[i] = c_renderer_create_viewport_vertex(
			projected_vertex_list[i]);
	}

	int triangle_count = 0;

	for (int f = 0; f < face_count; f++) {
		wf_face_t face = faces[f];

		int i0 = face.v[0];
		int i1 = face.v[1];
		int i2 = face.v[2];

		int uv0 = face.uv[0];
		int uv1 = face.uv[1];
		int uv2 = face.uv[2];

		c_rasterizer_vertex_t a = screen_vertex_list[i0];
		c_rasterizer_vertex_t b = screen_vertex_list[i1];
		c_rasterizer_vertex_t c = screen_vertex_list[i2];

		a.u = uvs[uv0].x;
		a.v = uvs[uv0].y;

		b.u = uvs[uv1].x;
		b.v = uvs[uv1].y;

		c.u = uvs[uv2].x;
		c.v = uvs[uv2].y;

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
		return 0;
	}

	const wf_obj_parsed_t obj = wf_obj_parse(argv[1]);

	const wf_texture_t *tex = load_texture(argv[2]);

	if (tex == NULL) {
#ifdef WF_DEBUG
		tex = wf_texture_create_checkerboard();
#endif
	}

	wf_platform_t *platform = NULL;

	if (!wf_platform_init(&platform, WF_INTERNAL_WIDTH, WF_INTERNAL_HEIGHT,
			      WF_WINDOW_SCALE)) {
		fprintf(stderr, "Failed to initialize WarpFrame platform.\n");
		return 1;
	}

	SDL_Renderer *sdl_renderer = wf_platform_get_renderer(platform);
	wf_font_build(sdl_renderer);

	wf_input_t input = { 0 };

	c_renderer_t *renderer;
	c_renderer_init(&renderer);

	int triangle_count = 0;

	vec4f_t *normalized_obj_vertices = wf_obj_normalize(&obj);

	int vertex_count = obj.vertex_count;
	int face_count = obj.face_count;

	wf_face_t *faces = obj.faces;
	vec2f_t *uvs = obj.uvs;

	c_rasterizer_triangle_t *tri =
		malloc(face_count * sizeof(c_rasterizer_triangle_t));

	mu_Context *ctx = wf_control_initialize();
	ctx->text_width = text_width_cb;
	ctx->text_height = text_height_cb;

	wf_control_state_t control_state;
	wf_control_reset_state(&control_state);

	Uint32 last_ticks = SDL_GetTicks();
	Uint32 frame_accum = 0;
	int frame_count = 0;

	while (!input.quit) {
		Uint32 now = SDL_GetTicks();
		Uint32 delta = now - last_ticks;
		last_ticks = now;
		frame_accum += delta;
		frame_count++;
		if (frame_accum >= 500) {
			control_state.fps = (float)frame_count * 1000.0f /
					    (float)frame_accum;
			frame_accum = 0;
			frame_count = 0;
		}

		c_renderer_clean(renderer);
		wf_control_fill_background(renderer, control_state.bg_color);

		object_to_screen(normalized_obj_vertices, faces, uvs,
				 vertex_count, face_count, &triangle_count,
				 control_state.rotation_angle,
				 control_state.camera_distance, tri);

		for (int i = 0; i < triangle_count; i++) {
			c_rasterizer_draw_triangle_solid(renderer, tri[i],
							 (wf_texture_t *)tex);
		}

		control_state.triangle_count = triangle_count;

		wf_platform_present_framebuffer(platform,
						renderer->color_buffer);

		wf_platform_begin_ui(platform);

		poll_all_input(&input, ctx);

		mu_begin(ctx);
		wf_control_create_panel(ctx, &control_state);
		mu_end(ctx);

		mu_render_commands(sdl_renderer, ctx);

		wf_platform_end_ui(platform);

		SDL_RenderPresent(sdl_renderer);

		if (!control_state.paused)
			control_state.rotation_angle +=
				control_state.rotation_speed;
	}
#ifdef WF_DEBUG
	wf_texture_destroy_checkerboard(tex);
#endif
	c_renderer_destroy(renderer);

	free(obj.vertices);
	free(obj.faces);
	free(obj.uvs);
	free(normalized_obj_vertices);
	free(tri);

	wf_font_destroy();
	wf_control_destroy(ctx);
	wf_platform_shutdown(platform);

	return 0;
}

vec2i_t m_vec2i_edge(vec2i_t a, vec2i_t b)
{
	vec2i_t ret = { .x = (b.x - a.x), .y = (b.y - a.y) };
	return ret;
}
