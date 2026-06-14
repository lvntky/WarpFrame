#ifndef M_UTIL_H_
#define M_UTIL_H_

#include <m_type.h>

int m_det2i(vec2i_t a, vec2i_t b);
mat4i_t *m_mat4i_create();
void m_mat4i_destroy(mat4i_t *mat);
#endif //M_UTIL_H_

