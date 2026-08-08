#include <wf_control.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

mu_Context *wf_control_initialize(void)
{
	mu_Context *context = malloc(sizeof(mu_Context));
	mu_init(context);
	return context;
}

void wf_control_destroy(mu_Context *ctx)
{
	if (ctx) {
		free(ctx);
	}
}

static int uint8_slider(mu_Context *ctx, unsigned char *value,
			 const char *label)
{
	static float tmp;
	int res;
	mu_push_id(ctx, &value, sizeof(value));
	mu_layout_row(ctx, 2, (int[]){ 60, -1 }, 0);
	mu_label(ctx, label);
	tmp = (float)*value;
	res = mu_slider_ex(ctx, &tmp, 0.0f, 255.0f, 0, "%.0f",
			   MU_OPT_ALIGNCENTER);
	*value = (unsigned char)tmp;
	mu_pop_id(ctx);
	return res;
}

void wf_control_create_panel(mu_Context *ctx, wf_control_state_t *state)
{
	if (mu_begin_window(ctx, "WarpFrame Control",
			    mu_rect(20, 20, 300, 460))) {
		if (mu_header(ctx, "Rendering")) {
			mu_layout_row(ctx, 2, (int[]){ 90, -1 }, 0);
			mu_label(ctx, "Wireframe");
			mu_checkbox(ctx, "", &state->wireframe);

			mu_label(ctx, "Backface Cull");
			mu_checkbox(ctx, "", &state->backface_cull);

			mu_layout_row(ctx, 1, (int[]){ -1 }, 0);
			static const char *modes[] = { "Solid", "Textured",
						       "Depth" };
			mu_label(ctx, "Shading Mode");
			mu_layout_row(ctx, 3, (int[]){ 90, 90, 90 }, 0);
			for (int i = 0; i < 3; i++) {
				int selected = state->shading_mode == i;
				if (selected)
					ctx->style->colors[MU_COLOR_BUTTON] =
						mu_color(80, 120, 200, 255);
				if (mu_button(ctx, modes[i]))
					state->shading_mode = i;
				if (selected)
					ctx->style->colors[MU_COLOR_BUTTON] =
						mu_color(75, 75, 75, 255);
			}
		}

		if (mu_header_ex(ctx, "Transform", MU_OPT_EXPANDED)) {
			mu_layout_row(ctx, 2, (int[]){ 90, -1 }, 0);
			mu_label(ctx, "Rot Speed");
			mu_slider(ctx, &state->rotation_speed, -0.20f, 0.20f);

			mu_label(ctx, "Distance");
			mu_slider(ctx, &state->camera_distance, 1.0f, 10.0f);

			mu_layout_row(ctx, 1, (int[]){ -1 }, 0);
			if (mu_button(ctx, state->paused ? "Resume" : "Pause"))
				state->paused = !state->paused;
		}

		if (mu_header_ex(ctx, "Background", MU_OPT_EXPANDED)) {
			uint8_slider(ctx, &state->bg_color.r, "R");
			uint8_slider(ctx, &state->bg_color.g, "G");
			uint8_slider(ctx, &state->bg_color.b, "B");

			mu_layout_row(ctx, 1, (int[]){ -1 }, 0);
			mu_Rect r = mu_layout_next(ctx);
			mu_draw_rect(ctx, r,
				     mu_color(state->bg_color.r,
					      state->bg_color.g,
					      state->bg_color.b, 255));
		}

		if (mu_header(ctx, "Stats")) {
			mu_layout_row(ctx, 1, (int[]){ -1 }, 0);
			char buf[64];
			snprintf(buf, sizeof(buf), "tris: %d",
				 state->triangle_count);
			mu_label(ctx, buf);
			snprintf(buf, sizeof(buf), "angle: %.2f",
				 state->rotation_angle);
			mu_label(ctx, buf);
			snprintf(buf, sizeof(buf), "fps: %.1f", state->fps);
			mu_label(ctx, buf);
		}

		mu_layout_row(ctx, 1, (int[]){ -1 }, 0);
		if (mu_button(ctx, "Reset"))
			wf_control_reset_state(state);

		mu_end_window(ctx);
	}
}

void wf_control_reset_state(wf_control_state_t *state)
{
	memset(state, 0, sizeof(*state));
	state->rotation_speed = 0.05f;
	state->camera_distance = 2.0f;
	state->bg_color = (wf_control_color_t){ 20, 20, 20 };
	state->backface_cull = 1;
	state->shading_mode = 0;
}
