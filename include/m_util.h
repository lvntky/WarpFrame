#ifndef M_UTIL_H_
#define M_UTIL_H_

#include <m_type.h>

int m_det2i(vec2i_t a, vec2i_t b);
mat4i_t *m_mat4i_create();
void m_mat4i_destroy(mat4i_t *mat);

mat4f_t m_mat4f_identity();
vec4f_t m_mat4f_mul_vec4f(mat4f_t mat, vec4f_t vec);
#endif //M_UTIL_H_

