#ifndef WF_CONTROL_H
#define WF_CONTROL_H

#include <microui.h>

typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} wf_control_color_t;

typedef struct {
	int wireframe;
	int backface_cull;
	int shading_mode;
	int paused;
	float rotation_speed;
	float rotation_angle;
	float camera_distance;
	int triangle_count;
	float fps;
	wf_control_color_t bg_color;
} wf_control_state_t;

mu_Context *wf_control_initialize(void);
void wf_control_destroy(mu_Context *ctx);
void wf_control_create_panel(mu_Context *ctx, wf_control_state_t *state);
void wf_control_reset_state(wf_control_state_t *state);

#endif
