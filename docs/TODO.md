# WarpFrame Current TODO

## Phase 0 — Project Foundation
[x] Makefile wildcard build works
[x] src/*.c automatically compiled
[x] Header dependency files generated with -MMD -MP
[x] README.md exists
[x] LICENSE exists
[x] .gitignore exists
[x] build/ output ignored
[x] final binary ignored


## Phase 1 — Platform Layer / SDL2
[x] SDL includes only inside platform layer
[x] wf_platform_t opaque
[x] Window creation works
[x] ESC closes app
[x] Window close button works
[x] Delta time works
[x] SDL shutdown clean
[x] CPU framebuffer presented through SDL


## Phase 2 — CPU Framebuffer
[x] color_buffer allocated
[x] depth_buffer allocated
[x] renderer init/shutdown
[x] renderer clean/begin frame
[x] clear color buffer every frame
[x] clear depth buffer every frame
[x] present CPU framebuffer through SDL texture


## Phase 3 — Rasterizer Basics
[x] put_pixel
[x] solid triangle drawing
[x] triangle bounding box
[x] clamp bbox to screen
[x] barycentric inside test
[x] offscreen triangle safety


## Phase 4 — Depth Buffer
[x] add z to rasterizer vertex
[x] barycentric z interpolation
[x] per-pixel depth test
[x] near pixels overwrite far pixels
[x] draw order no longer determines visibility


## Phase 4.5 — OBJ Model Pipeline
[x] parse OBJ vertex lines: v x y z
[x] parse OBJ face lines: f i j k
[x] convert OBJ 1-based indices to C 0-based indices
[x] store vertices separately from face indices
[x] normalize model into centered unit box
[x] return normalized vertex copy without mutating source OBJ
[x] create transformed vertex copy from normalized vertices
[x] fix memcpy size bug: vertex_count * sizeof(vec4f_t)
[x] translate model in front of camera with z += 5
[x] project vertices using x / z and y / z
[x] viewport transform
[x] build screen-space triangle list from face indices
[x] render OBJ model on screen
[x] render teapot successfully
[x] per-pixel depth interpolation
[x] raw z used for depth test
[x] automatic depth debug normalization
[x] backface culling using screen-space signed area
[x] immutable OBJ source data
[x] stable per-face colors from face index
[x] rotating immutable OBJ model around Y axis

[ ] near-plane handling for z too close / behind camera
[ ] proper triangle clipping
[ ] avoid rebuilding colors every frame if not needed
[ ] replace per-frame malloc/free with reusable buffers


## Phase 5 — 3D Math / Matrix Pipeline
[x] vec3 type
[x] vec4 type
[x] mat4 type
[x] manual Y-axis rotation
[x] manual translation
[x] perspective divide
[x] viewport transform

[x] mat4_identity
[x] mat4_mul
[x] mat4_mul_vec4
[ ] mat4_rotation_y
[ ] mat4_translation
[ ] mat4_perspective
[ ] replace manual rotate_y with matrix rotation
[ ] replace manual z += 5 with translation matrix
[ ] create model matrix
[ ] create view matrix
[ ] create projection matrix
[ ] use model-view-projection pipeline
[ ] render same rotating teapot through matrix pipeline


## Phase 6 — Basic PS1 Look
[x] internal low resolution
[x] nearest-neighbor upscale
[x] visible low-res framebuffer aesthetic

[ ] vertex snapping
[ ] snap amount setting
[ ] toggle vertex snapping
[ ] optional affine warping look
[ ] color crush / limited palette
[ ] dithering


## Phase 7 — Renderer Buffer Cleanup
[ ] create renderer-owned transformed_vertices buffer
[ ] create renderer-owned projected_vertices buffer
[ ] create renderer-owned screen_vertices buffer
[ ] create renderer-owned triangle buffer
[ ] allocate buffers once
[ ] reuse buffers every frame
[ ] remove per-frame malloc/free from object_to_screen
[ ] shutdown frees all renderer-owned buffers


## Phase 8 — Tile System / Single Thread
[ ] create tile type
[ ] create tile grid
[ ] tile size = 32
[ ] 320x240 -> 10x8 tile grid
[ ] compute tile bounds
[ ] clear tile triangle lists every frame
[ ] compute triangle bbox
[ ] bin triangle into touched tiles
[ ] render tiles sequentially
[ ] rasterizer clamps drawing to tile bounds
[ ] tile grid overlay


## Phase 9 — Thread Pool
[ ] define job function type
[ ] define job struct
[ ] create thread pool type
[ ] spawn worker threads
[ ] implement job queue
[ ] mutex-protect queue
[ ] condition variable wakeup
[ ] pending job counter
[ ] wait for all jobs
[ ] graceful shutdown
[ ] test with non-render jobs first


## Phase 10 — Threaded Tile Rendering
[ ] create one render job per tile
[ ] pass tile bounds and triangle list to each job
[ ] workers rasterize only inside their tile
[ ] no framebuffer locks needed
[ ] wait for all tile jobs before present
[ ] debug overlay: tile worker ownership
[ ] compare single-threaded vs threaded output
