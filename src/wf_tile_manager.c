#include <wf_tile_manager.h>
#include <stdlib.h>

int wf_tile_col_num(int width)
{
	return width / WF_TILE_SIZE;
}
int wf_tile_row_num(int height)
{
	return height / WF_TILE_SIZE;
}

wf_grid_t wf_tile_create_grid(int sw, int sh)
{
	int col_num = wf_tile_col_num(sw);
	int row_num = wf_tile_row_num(sh);

	wf_tile_t *tiles = malloc(col_num * row_num * sizeof(wf_tile_t));
	int tile_counter = 0;

	for (int row = 0; row < sh; row += WF_TILE_SIZE) {
		for (int col = 0; col < sw; col += WF_TILE_SIZE) {
			wf_tile_t tile = { .id = tile_counter,
					   .x = col,
					   .y = row,
					   .tri = NULL };
			tiles[tile_counter] = tile;
			tile_counter++;
		}
	}

	wf_grid_t grid = { .tiles = tiles, .count = tile_counter };
	return grid;
}

void wf_tile_destroy_tile(wf_tile_t *tile)
{
	if (tile != NULL) {
		free(tile);
	}
}
