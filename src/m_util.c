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
	return (mat4f_t){
		.cols[0] = { 1.0f, 0.0f, 0.0f, 0.0f }, //x
		.cols[1] = { 0.0f, 1.0f, 0.0f, 0.0f }, //y
		.cols[2] = { 0.0f, 0.0f, 1.0f, 0.0f }, //z
		.cols[3] = { 0.0f, 0.0f, 0.0f, 1.0f }, //w
	};
}

vec4f_t m_mat4f_mul_vec4f(mat4f_t mat, vec4f_t vec)
{
    vec4f_t out;

    out.x = mat.cols[0].x * vec.x +
            mat.cols[1].x * vec.y +
            mat.cols[2].x * vec.z +
            mat.cols[3].x * vec.w;

    out.y = mat.cols[0].y * vec.x +
            mat.cols[1].y * vec.y +
            mat.cols[2].y * vec.z +
            mat.cols[3].y * vec.w;

    out.z = mat.cols[0].z * vec.x +
            mat.cols[1].z * vec.y +
            mat.cols[2].z * vec.z +
            mat.cols[3].z * vec.w;

    out.w = mat.cols[0].w * vec.x +
            mat.cols[1].w * vec.y +
            mat.cols[2].w * vec.z +
            mat.cols[3].w * vec.w;

    return out;
}
