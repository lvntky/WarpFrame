#include <wf_obj_parser.h>
#include <stdio.h>
#include <stdlib.h>

static int parse_face_index(const char *token)
{
	int index = 0;

	/*
		Supports:
		f 1 2 3
		f 1/1 2/2 3/3
		f 1/1/1 2/2/2 3/3/3
		f 1//1 2//2 3//3
	*/

	if (sscanf(token, "%d", &index) != 1) {
		return -1;
	}

	return index - 1;
}

#define WF_MAX_LINE_LEN 2048

const wf_obj_parsed_t *wf_obj_parse(char *path)
{
	wf_obj_parsed_t *parsed;
	FILE *fp = fopen(path, "r");

	if (fp == NULL) {
		fprintf(stderr, "file %s not found", path);
	}

	int v_count = 0;
	int f_count = 0;

	char line[WF_MAX_LINE_LEN];
	while (fgets(line, WF_MAX_LINE_LEN, fp)) {
		if (line[0] == 'v' && line[1] == ' ') {
			v_count++;
		} else if (line[0] == 'f' && line[1] == ' ') {
			f_count++;
		}
	}

	if (v_count == 0 || f_count == 0) {
		fprintf(stderr, "no geomethrical shape found in %s", path);
		goto out;
	}

	parsed = malloc(sizeof(wf_obj_parsed_t));
	vec4f_t *vlist = malloc(v_count * sizeof(vec4f_t));
	int *flist = malloc(f_count * 3 * sizeof(int));

	rewind(fp);

	int vindex = 0;
	int findex = 0;

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
				flist[findex++] = parse_face_index(a);
				flist[findex++] = parse_face_index(b);
				flist[findex++] = parse_face_index(c);
			}
		}
	}

	parsed->vertex_count = v_count;
	parsed->vertices = vlist;
	parsed->face_count = f_count;
	parsed->faces = flist;
out:
	return parsed;
}


void wf_obj_debug_print(const wf_obj_parsed_t *o)
{
	if (o == NULL) {
		printf("wf_obj: NULL\n");
		return;
	}

	printf("wf_obj: %d vertices, %d faces\n",
	       o->vertex_count, o->face_count);

	for (int i = 0; i < o->vertex_count; i++) {
		const vec4f_t *v = &o->vertices[i];
		printf("  v[%d] = (% .4f, % .4f, % .4f, % .2f)\n",
		       i, v->x, v->y, v->z, v->w);
	}

	for (int f = 0; f < o->face_count; f++) {
		int i0 = o->faces[f * 3 + 0];
		int i1 = o->faces[f * 3 + 1];
		int i2 = o->faces[f * 3 + 2];
		printf("  f[%d] = %d %d %d", f, i0, i1, i2);


		if (i0 >= 0 && i0 < o->vertex_count &&
		    i1 >= 0 && i1 < o->vertex_count &&
		    i2 >= 0 && i2 < o->vertex_count) {
			printf("  ->  (% .2f % .2f % .2f) (% .2f % .2f % .2f) (% .2f % .2f % .2f)\n",
			       o->vertices[i0].x, o->vertices[i0].y, o->vertices[i0].z,
			       o->vertices[i1].x, o->vertices[i1].y, o->vertices[i1].z,
			       o->vertices[i2].x, o->vertices[i2].y, o->vertices[i2].z);
		} else {
			printf("  -> [INVALID INDEX]\n");
		}
	}
}

vec4f_t *wf_obj_normalize(wf_obj_parsed_t *obj)
{
	if (!obj || obj->vertex_count == 0)
		return NULL;

	vec4f_t *normalized = malloc(obj->vertex_count * sizeof(vec4f_t));
	
	float min_x = obj->vertices[0].x, max_x = obj->vertices[0].x;
	float min_y = obj->vertices[0].y, max_y = obj->vertices[0].y;
	float min_z = obj->vertices[0].z, max_z = obj->vertices[0].z;


	for (int i = 1; i < obj->vertex_count; i++) {
		vec4f_t v = obj->vertices[i];
		if (v.x < min_x) min_x = v.x;
		if (v.x > max_x) max_x = v.x;
		if (v.y < min_y) min_y = v.y;
		if (v.y > max_y) max_y = v.y;
		if (v.z < min_z) min_z = v.z;
		if (v.z > max_z) max_z = v.z;
	}


	float cx = (min_x + max_x) * 0.5f;
	float cy = (min_y + max_y) * 0.5f;
	float cz = (min_z + max_z) * 0.5f;


	float size_x = max_x - min_x;
	float size_y = max_y - min_y;
	float size_z = max_z - min_z;
	float size = size_x;
	if (size_y > size) size = size_y;
	if (size_z > size) size = size_z;

	if (size == 0.0f) return NULL;
	
	float inv = 1.0f / size;

	
	for (int i = 0; i < obj->vertex_count; i++) {
		normalized[i].x = (obj->vertices[i].x - cx) * inv;
		normalized[i].y = (obj->vertices[i].y - cy) * inv;
		normalized[i].z = (obj->vertices[i].z - cz) * inv;
	}

	return normalized;
}
