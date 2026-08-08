#ifndef WF_TILE_MANAGER_H_
#define WF_TILE_MANAGER_H_

#define WF_TILE_SIZE 16

typedef struct wf_tile {
	int x;
	int y;
	int id;
} wf_tile_t;

typedef struct wf_grid {
	wf_tile_t *tiles;
	int count;
} wf_grid_t;

int wf_tile_col_num(int width);
int wf_tile_row_num(int height);
wf_grid_t wf_tile_create_grid(int sw, int sh);

#endif //WF_TILE_MANAGER_H_
