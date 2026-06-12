#ifndef M_TYPE_H_
#define M_TYPE_H_

typedef struct vec2i {
	int x;
	int y;
} vec2i_t;

typedef struct trianglei {
	vec2i_t pa; // point a 
	vec2i_t pb; // point b
	vec2i_t pc; // point c

	vec2i_t z;
	
} trianglei_t;

#endif //M_TYPE_H_
