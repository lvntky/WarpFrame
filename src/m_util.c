#include <m_util.h>
#include <stdlib.h>
#include <stdio.h>

int m_det2i(vec2i_t a, vec2i_t b)
{
	return (a.x * b.y - a.y * b.x);
}

mat4i_t *m_mat4i_create()
{
	mat4i_t *mat = calloc(4, sizeof(mat4i_t));
	if (!mat) {
		fprintf(stderr, "unable to create 4x4 matrix mat4i_t.", NULL);

	}
	return mat;
}

void m_mat4i_destroy(mat4i_t *mat)
{
	if (!mat) {
		return;
	}

	free(mat);
}
