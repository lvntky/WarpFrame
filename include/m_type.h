#ifndef M_TYPE_H_
#define M_TYPE_H_

typedef struct vec2i {
	int x;
	int y;
} vec2i_t;

typedef struct vec3i {
	int x;
	int y;
	int z;
} vec3i_t;

typedef struct vec4i {
	int x;
	int y;
	int z;
	int w; // homogeneouse coordinate, for 3d translations
} vec4i_t;

typedef struct mat4i {
	vec4i_t column1;
	vec4i_t column2;
	vec4i_t column3;
	vec4i_t column4;
} mat4i_t;

#endif //M_TYPE_H_
