#ifndef WF_OBJ_PARSER_H_
#define WF_OBJ_PARSER_H_

#include <m_type.h>

typedef struct wf_obj_parsed {
	int vertex_count;
	vec4f_t *vertices;
	int face_count;
	int *faces;
} wf_obj_parsed_t;

wf_obj_parsed_t *wf_obj_parse(char *path);
void wf_obj_debug_print(const wf_obj_parsed_t *o);
void wf_obj_normalize(wf_obj_parsed_t *obj);

#endif //WF_OBJ_PARSER_H_
