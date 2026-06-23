#include <m_util.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int m_det2i(vec2i_t a, vec2i_t b)
{
	return (a.x * b.y - a.y * b.x);
}

mat4i_t *m_mat4i_create()
{
	mat4i_t *mat = calloc(4, sizeof(mat4i_t));
	if (!mat) {
		fprintf(stderr, "unable to create 4x4 matrix mat4i_t.");
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

mat4f_t m_mat4f_identity()
{
	mat4f_t out = { .m = { { 1.0f, 0.0f, 0.0f, 0.0f },
			       { 0.0f, 1.0f, 0.0f, 0.0f },
			       { 0.0f, 0.0f, 1.0f, 0.0f },
			       { 0.0f, 0.0f, 0.0f, 1.0f } } };

	return out;
}

vec4f_t m_mat4f_mul_vec4f(mat4f_t mat, vec4f_t vec)
{
	vec4f_t out;

	out.x = mat.m[0][0] * vec.x + mat.m[0][1] * vec.y +
		mat.m[0][2] * vec.z + mat.m[0][3] * vec.w;

	out.y = mat.m[1][0] * vec.x + mat.m[1][1] * vec.y +
		mat.m[1][2] * vec.z + mat.m[1][3] * vec.w;

	out.z = mat.m[2][0] * vec.x + mat.m[2][1] * vec.y +
		mat.m[2][2] * vec.z + mat.m[2][3] * vec.w;

	out.w = mat.m[3][0] * vec.x + mat.m[3][1] * vec.y +
		mat.m[3][2] * vec.z + mat.m[3][3] * vec.w;

	return out;
}

mat4f_t m_mat4f_mul(mat4f_t a, mat4f_t b)
{
	mat4f_t c;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			c.m[i][j] = a.m[i][j] * b.m[i][j];
		}
	}

	return c;
}

mat4f_t m_mat4f_rotate(float angle, ERotationOrientation orientation)
{
	float c = cosf(angle);
	float s = sinf(angle);

	mat4f_t r = m_mat4f_identity();

	switch (orientation) {
	case ROTATE_X: {
		r.m[1][1] = c;
		r.m[1][2] = -s;
		r.m[2][1] = s;
		r.m[2][2] = c;
		break;
	}
	case ROTATE_Z: {
		r.m[0][0] = c;
		r.m[0][1] = -s;
		r.m[1][0] = s;
		r.m[1][1] = c;
		break;
	}
		// Rotate by y
	default:
		r.m[0][0] = c;
		r.m[0][2] = s;
		r.m[2][0] = -s;
		r.m[2][2] = c;
		break;
	}

	return r;
}
