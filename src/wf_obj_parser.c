#include <wf_obj_parser.h>
#include <stdio.h>
#include <stdlib.h>

static void parse_face_token(const char *token, int *vertex_index,
			     int *uv_index)
{
	int v = 0;
	int uv = 0;

	/*
	Supports:
	1
	1/1
	1/1/1
	1//1
*/

	if (sscanf(token, "%d/%d", &v, &uv) >= 1) {
		*vertex_index = v - 1;

		if (uv > 0) {
			*uv_index = uv - 1;
		} else {
			*uv_index = -1;
		}

	} else {
		*vertex_index = -1;
		*uv_index = -1;
	}
}

#define WF_MAX_LINE_LEN 2048

wf_obj_parsed_t wf_obj_parse(char *path)
{
	wf_obj_parsed_t parsed;
	FILE *fp = fopen(path, "r");

	if (fp == NULL) {
		fprintf(stderr, "file %s not found", path);
	}

	int v_count = 0;
	int f_count = 0;
	int uv_count = 0;

	char line[WF_MAX_LINE_LEN];
	while (fgets(line, WF_MAX_LINE_LEN, fp)) {
		if (line[0] == 'v' && line[1] == ' ') {
			v_count++;
		} else if (line[0] == 'f' && line[1] == ' ') {
			f_count++;
		} else if (line[0] == 'v' && line[1] == 't') {
			uv_count++;
		}
	}

	if (v_count == 0 || f_count == 0) {
		fprintf(stderr, "no geomethrical shape found in %s", path);
		goto out;
	}

//	parsed = malloc(sizeof(wf_obj_parsed_t));
	vec4f_t *vlist = malloc(v_count * sizeof(vec4f_t));
	wf_face_t *flist = malloc(f_count * sizeof(wf_face_t));
	vec2f_t *uvlist = malloc(uv_count * sizeof(vec2f_t));

	rewind(fp);

	int vindex = 0;
	int findex = 0;
	int uvindex = 0;

	while (fgets(line, WF_MAX_LINE_LEN, fp)) {
		if (line[0] == 'v' && line[1] == ' ') {
			float x, y, z;
			if (sscanf(line, "v %f %f %f", &x, &y, &z) == 3) {
				vlist[vindex++] = (vec4f_t){
					.x = x, .y = y, .z = z, .w = 1.0f
				};
			}
		} else if (line[0] == 'f' && line[1] == ' ') {
			char a[64], b[64], c[64];

			if (sscanf(line, "f %63s %63s %63s", a, b, c) == 3) {
				wf_face_t face;

				parse_face_token(a, &face.v[0], &face.uv[0]);

				parse_face_token(b, &face.v[1], &face.uv[1]);

				parse_face_token(c, &face.v[2], &face.uv[2]);

				flist[findex++] = face;
			}
		} else if (line[0] == 'v' && line[1] == 't') {
			float u, v;
			if (sscanf(line, "vt %f %f", &u, &v) == 2) {
				uvlist[uvindex++] = (vec2f_t){ .x = u, .y = v };
			}
		}
	}

	parsed.vertex_count = v_count;
	parsed.vertices = vlist;
	parsed.face_count = f_count;
	parsed.faces = flist;
	parsed.uv_count = uv_count;
	parsed.uvs = uvlist;
out:
	return parsed;
}

vec4f_t *wf_obj_normalize(const wf_obj_parsed_t *obj)
{
	if (!obj || obj->vertex_count == 0)
		return NULL;

	vec4f_t *normalized = malloc(obj->vertex_count * sizeof(vec4f_t));

	float min_x = obj->vertices[0].x, max_x = obj->vertices[0].x;
	float min_y = obj->vertices[0].y, max_y = obj->vertices[0].y;
	float min_z = obj->vertices[0].z, max_z = obj->vertices[0].z;

	for (int i = 1; i < obj->vertex_count; i++) {
		vec4f_t v = obj->vertices[i];
		if (v.x < min_x)
			min_x = v.x;
		if (v.x > max_x)
			max_x = v.x;
		if (v.y < min_y)
			min_y = v.y;
		if (v.y > max_y)
			max_y = v.y;
		if (v.z < min_z)
			min_z = v.z;
		if (v.z > max_z)
			max_z = v.z;
	}

	float cx = (min_x + max_x) * 0.5f;
	float cy = (min_y + max_y) * 0.5f;
	float cz = (min_z + max_z) * 0.5f;

	float size_x = max_x - min_x;
	float size_y = max_y - min_y;
	float size_z = max_z - min_z;
	float size = size_x;
	if (size_y > size)
		size = size_y;
	if (size_z > size)
		size = size_z;

	if (size == 0.0f)
		return NULL;

	float inv = 1.0f / size;

	for (int i = 0; i < obj->vertex_count; i++) {
		normalized[i].x = (obj->vertices[i].x - cx) * inv;
		normalized[i].y = (obj->vertices[i].y - cy) * inv;
		normalized[i].z = (obj->vertices[i].z - cz) * inv;
	}

	return normalized;
}
