#include <m_util.h>

int m_det2i(vec2i_t a, vec2i_t b) {
	return (a.x * b.y - a.y * b.x);
}
