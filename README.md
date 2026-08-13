# WarpFrame

A PS1-style software rasterizer in C. No OpenGL, no Vulkan, no GPU. Every pixel on screen was written by a loop in this repo.

![first render](./docs/show.gif)

![C11](https://img.shields.io/badge/C-C11-blue)
![SDL2](https://img.shields.io/badge/SDL2-presentation%20only-informational)
![platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS%20%7C%20Windows-lightgrey)

SDL2 is used for exactly one thing: blitting a `uint32_t*` to a window. Transformation, clipping, projection, rasterization, depth testing and texturing all happen on the CPU, in code you can step through.

## Why

Modern graphics APIs hide the interesting part. You hand a GPU a vertex buffer and a shader and pixels appear. WarpFrame does the opposite — it makes the pipeline the product.

The PS1 aesthetic is not a filter applied at the end. It falls out of the implementation: affine texture mapping produces the warping, integer vertex snapping produces the wobble, no subpixel precision produces the shimmer. The artifacts are the architecture showing through, which is exactly what makes them worth understanding.

## Features

- Edge-function rasterization with barycentric interpolation
- Z-buffered depth testing
- Perspective projection and viewport mapping
- Affine texture mapping, PS1-accurate warping included
- Tile-based binning with per-tile trivial reject
- OBJ model loading
- Hand-rolled math layer, zero external dependencies beyond SDL2
- microui debug overlay with live pipeline visualization

## Build

Requires a C11 compiler, Make, and SDL2 development headers.

```bash
# Fedora
sudo dnf install gcc make SDL2-devel

# Debian / Ubuntu
sudo apt install build-essential libsdl2-dev

# macOS
brew install sdl2
```

```bash
make
./warpframe assets/model.obj
```

Other targets:

```bash
make debug      # -O0 -g3, debug overlay enabled
make asan       # ASan + UBSan, halts on first error
make release    # -O3
```

## Pipeline

```text
OBJ model
    |
    v
model / view / projection transform
    |
    v
perspective divide
    |
    v
viewport mapping to screen space
    |
    v
tile binning              <- triangles bound to overlapping tiles
    |
    v
edge function coverage    <- per-pixel inside test
    |
    v
barycentric interpolation <- depth, UV
    |
    v
depth test + texture fetch
    |
    v
framebuffer -> SDL2
```

## Tile binning

Rather than rasterizing each triangle across its full bounding box, the screen is divided into fixed-size tiles and each triangle is bound only to the tiles it actually touches.

The overlap test evaluates each of the triangle's three edge functions at a single corner of the tile — the one the edge's normal points toward. If that corner is outside, the whole tile is outside, and the tile is skipped. Three comparisons reject an entire tile.

This is the same trivial-reject scheme Larrabee used, and it is the groundwork for per-tile parallelism: tiles are independent, so they can be handed to separate threads with no synchronization on the framebuffer.

## Architecture

```text
main.c            frame loop, scene setup
c_renderer.c      color/depth buffers, transform, triangle submission
c_rasterizer.c    edge functions, barycentrics, tile binding, pixel writes
wf_tile_manager.c tile grid construction
wf_obj_parser.c   OBJ loading
wf_texture.c      texture sampling
m_util.c          vec2/vec3/vec4/mat4
platform_sdl.c    window, input, frame timing, present
```

The platform layer knows nothing about triangles. The rasterizer knows nothing about SDL. Swapping the presentation backend means touching one file.

## Roadmap

- [ ] Near-plane clipping
- [ ] Perspective-correct texture mapping (as a toggle — affine stays default)
- [ ] Multithreaded tile rasterization
- [ ] Per-tile triangle bins instead of a single binding slot
- [ ] Hierarchical depth buffer
- [ ] SIMD inner loop
- [ ] Vertex lighting
- [ ] Scene format beyond single-OBJ

## Design principles

- Keep the pipeline visible; no abstraction that hides a stage
- Every stage independently debuggable and visualizable
- Explicit C over clever C
- No dependency that could have been a hundred lines

## Acknowledgements

### Rasterization

- Juan Pineda, [*A Parallel Algorithm for Polygon Rasterization*](https://dl.acm.org/doi/10.1145/54852.378457), SIGGRAPH 1988 — the edge function, and the origin of nearly everything in `c_rasterizer.c`. [Overview](https://history.siggraph.org/learning/a-parallel-algorithm-for-polygon-rasterization-by-pineda/)
- Kristoffer Dyrkorn, [*Triangle rasterization in a nutshell*](https://kristoffer-dyrkorn.github.io/triangle-rasterizer/1.html) — Pineda's algorithm built up step by step
- Nicolas Capens, *Advanced Rasterization* — the classic block-based half-space rasterizer ([devmaster archive](https://github.com/dcowden/emcfab/blob/master/applications/slicer/DevMaster.net%20-%20The%20Daily%20Code%20Gem%20%20Advanced%20Rasterization.htm))

### Optimization

- Fabian Giesen, [*Optimizing Software Occlusion Culling*](https://fgiesen.wordpress.com/2013/02/17/optimizing-sw-occlusion-culling-index/) — particularly *Optimizing the basic rasterizer* and *Depth buffers done quick*
- Fabian Giesen, [*A Trip through the Graphics Pipeline 2011*](https://fgiesen.wordpress.com/2011/07/09/a-trip-through-the-graphics-pipeline-2011-index/) — how hardware solves the same problems
- Michael Abrash, [*Rasterization on Larrabee*](https://www.cs.cmu.edu/afs/cs/academic/class/15869-f11/www/readings/abrash09_lrbrast.pdf) — the tile binning architecture this renderer follows

### Tiling and parallelism

- Molnar, Cox, Ellsworth, Fuchs, [*A Sorting Classification of Parallel Rendering*](https://henryfuchs.web.unc.edu/wp-content/uploads/sites/4964/2013/05/A-Sorting-Classification-of-Parallel-Rendering.pdf), IEEE CG&A 1994 — sort-first / sort-middle / sort-last; WarpFrame is sort-middle
- Akenine-Möller & Aila, [*Conservative and Tiled Rasterization Using a Modified Triangle Set-Up*](https://www.semanticscholar.org/paper/Conservative-and-Tiled-Rasterization-Using-a-Set-Up-Akenine-M%C3%B6ller-Aila/92ee37fb6ba0c710bcc53d73ac5a893de76d4211), JGT 2005 — eliminating false positives in the tile overlap test
- Nathan Guillemot, [*Rasterizer notes*](https://nlguillemot.wordpress.com/2016/07/10/rasterizer-notes/)

### Reference implementations

- [rygorous/intel_occlusion_cull](https://github.com/rygorous/intel_occlusion_cull) — binner and SIMD tile rasterizer in one readable codebase
- [Mesa llvmpipe](https://gitlab.freedesktop.org/mesa/mesa) — `src/gallium/drivers/llvmpipe/lp_setup_tri.c`, a production sort-middle binner
- [Song Ho Ahn, OpenGL rendering pipeline](https://www.songho.ca/opengl/gl_pipeline.html)

## License

To be determined.
