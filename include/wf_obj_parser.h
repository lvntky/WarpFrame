#ifndef WF_OBJ_PARSER_H_
#define WF_OBJ_PARSER_H_

#include <m_type.h>

typedef struct wf_face_t {
	int v[3];
	int uv[3];
} wf_face_t;

typedef struct wf_obj_parsed {
	int vertex_count;
	vec4f_t *vertices;

	int uv_count;
	vec2f_t *uvs;

	int face_count;
	wf_face_t *faces;

} wf_obj_parsed_t;

wf_obj_parsed_t wf_obj_parse(char *path);
void wf_obj_debug_print(const wf_obj_parsed_t *o);
vec4f_t *wf_obj_normalize(const wf_obj_parsed_t *obj);

#endif // WF_OBJ_PARSER_H_
