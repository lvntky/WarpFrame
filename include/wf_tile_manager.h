#ifndef WF_TILE_MANAGER_H_
#define WF_TILE_MANAGER_H_
#include <c_rasterizer_type.h>

#define WF_TILE_SIZE 8

typedef struct wf_tile {
	int x;
	int y;
	int id;
	c_rasterizer_triangle_t
		*tri; // temporary, switch with id+global triangle list
} wf_tile_t;

typedef struct wf_grid {
	wf_tile_t *tiles;
	int count;
} wf_grid_t;

int wf_tile_col_num(int width);
int wf_tile_row_num(int height);
wf_grid_t wf_tile_create_grid(int sw, int sh);
void wf_tile_destroy_tile(wf_tile_t *tile);

#endif //WF_TILE_MANAGER_H_
