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

/* Float vector types */

typedef struct vec2f {
	float x;
	float y;
} vec2f_t;

typedef struct vec3f {
	float x;
	float y;
	float z;
} vec3f_t;

typedef struct vec4f {
	float x;
	float y;
	float z;
	float w; // homogeneous coordinate, for 3D translations
} vec4f_t;

typedef struct mat4f {
	float m[4][4];
} mat4f_t;

#endif //M_TYPE_H_
