#ifndef M_UTIL_H_
#define M_UTIL_H_

#include <m_type.h>
#include <wf_e_orientation.h>

int m_det2i(vec2i_t a, vec2i_t b);
mat4i_t *m_mat4i_create();
void m_mat4i_destroy(mat4i_t *mat);

mat4f_t m_mat4f_identity();
vec4f_t m_mat4f_mul_vec4f(mat4f_t mat, vec4f_t vec);
mat4f_t m_mat4f_mul(mat4f_t a, mat4f_t b);

mat4f_t m_mat4f_rotate(float angle, ERotationOrientation orientation);
mat4f_t m_mat4f_transform(vec4f_t transformation);

vec4f_t m_vec4f_mul(vec4f_t a, vec4f_t b);
#endif //M_UTIL_H_

