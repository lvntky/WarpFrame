# WarpFrame

![first render](./docs/first_render.gif)

**WarpFrame** is a PS1-inspired software renderer written in C.

It renders 3D geometry on the CPU without relying on modern GPU graphics APIs such as OpenGL, Vulkan, or DirectX. The project focuses on understanding the classic 3D rendering pipeline by implementing the core stages manually: transformation, projection, rasterization, depth testing, and framebuffer presentation.

WarpFrame is designed as a low-level graphics programming project with a retro visual direction inspired by early 3D console games.

## Overview

Modern graphics programming often hides most of the rendering pipeline behind GPU APIs and shader systems. WarpFrame takes the opposite approach.

The renderer exposes the fundamental steps of 3D rendering directly in C:

```text
3D Model Data
    -
Vertex Transformation
    -
Projection
    -
Viewport Mapping
    -
Triangle Rasterization
    -
Depth Testing
    -
Framebuffer Output
    -
SDL2 Presentation
```

The goal is not only to display 3D objects, but to understand how 3D data becomes pixels on the screen.

## Visual Direction

WarpFrame is inspired by the visual characteristics of PlayStation 1 era 3D games.

This includes:

* low resolution rendering
* low-poly geometry
* visible triangle structure
* limited precision transformations
* affine texture distortion
* unstable vertex movement
* simple lighting
* retro color and depth artifacts

These effects are not treated as bugs. They are part of the intended aesthetic.

## Core Concepts

### Software Rendering

WarpFrame performs rendering on the CPU.

Instead of sending triangles to the GPU, the renderer manually processes vertices, fills triangles, calculates depth values, and writes pixels into a color buffer.

This makes the renderer slower than hardware rendering, but much more transparent and educational.

### Framebuffer

The renderer owns an internal framebuffer.

A framebuffer is simply a block of memory where each element represents a pixel on the screen.

After WarpFrame draws into this memory, the platform layer presents it through SDL2.

### Triangle Rasterization

Triangles are the basic primitive of the renderer.

A 3D model is eventually converted into triangles. Each triangle is transformed, projected, mapped to screen coordinates, and then rasterized into pixels.

WarpFrame uses edge functions and barycentric coordinates to determine whether a pixel is inside a triangle.

### Depth Buffer

A depth buffer stores the depth value of each pixel.

When multiple triangles overlap on the screen, the depth buffer decides which pixel is closer to the camera.

Without a depth buffer, farther triangles could incorrectly appear in front of nearer triangles.

### Projection

Projection converts 3D positions into 2D screen-space positions.

WarpFrame uses perspective projection to make distant objects appear smaller and nearby objects appear larger.

This is one of the key steps that turns raw 3D coordinates into a believable 3D image.

### Viewport Transformation

After projection, normalized coordinates are converted into screen coordinates.

This process maps abstract 3D output into actual pixel positions inside the internal framebuffer.

## Architecture

WarpFrame is organized around a small number of clear layers.

```text
Application
    |
    v
Renderer
    |
    v
Rasterizer
    |
    v
Math / Utility
    |
    v
Platform Layer
```

## Platform Layer

The platform layer handles operating-system-facing responsibilities.

It is responsible for:

* creating the window
* initializing SDL2
* handling keyboard input
* tracking frame timing
* presenting the framebuffer to the screen

The platform layer does not know how triangles are rendered. It only displays the final framebuffer produced by the renderer.

## Renderer

The renderer controls the rendering process.

It is responsible for:

* storing the color buffer
* storing the depth buffer
* clearing buffers each frame
* transforming vertices
* projecting geometry
* preparing triangles for rasterization
* submitting triangles to the rasterizer

The renderer acts as the main bridge between 3D scene data and low-level pixel drawing.

## Rasterizer

The rasterizer converts triangles into pixels.

It is responsible for:

* computing triangle bounding boxes
* evaluating edge functions
* calculating barycentric coordinates
* interpolating depth values
* writing visible pixels into the color buffer

The rasterizer is one of the most important parts of WarpFrame because it is where mathematical geometry becomes visible pixels.

## Math Layer

The math layer contains the basic types and operations needed for 3D rendering.

Common types include:

```c
vec2
vec3
vec4
mat4
```

Common operations include:

* vector addition
* vector subtraction
* matrix multiplication
* identity matrix creation
* translation matrices
* rotation matrices
* projection matrices
* determinant calculations

This layer keeps the renderer independent from external math libraries.

## Typical Frame Flow

A normal frame in WarpFrame follows this process:

```text
1. Poll input
2. Clear color buffer
3. Clear depth buffer
4. Update camera or model transform
5. Transform model vertices
6. Project vertices into clip space
7. Perform perspective divide
8. Convert coordinates to screen space
9. Rasterize triangles
10. Perform depth testing
11. Write pixels into framebuffer
12. Present framebuffer through SDL2
```

This structure mirrors the classic graphics pipeline, but implemented manually in C.

## Build

WarpFrame uses C and SDL2.

### Requirements

* C compiler
* Make
* SDL2 development libraries

On Fedora:

```bash
sudo dnf install gcc make SDL2-devel
```

On Debian/Ubuntu:

```bash
sudo apt install build-essential libsdl2-dev
```

### Compile

```bash
make
```

### Run

```bash
./warpframe
```

## Project Structure

A typical WarpFrame source layout may look like this:

```text
include/
    platform_sdl.h
    c_renderer.h
    c_rasterizer.h
    m_type.h
    m_util.h

src/
    platform_sdl.c
    c_renderer.c
    c_rasterizer.c
    m_util.c
    main.c
```

## Design Principles

WarpFrame follows a few simple design principles:

* keep the pipeline visible
* avoid unnecessary abstraction
* keep rendering logic separate from platform code
* prefer explicit C code
* make every rendering step debuggable
* build the renderer incrementally
* keep the project close to how old software renderers worked

## Why Software Rendering?

Software rendering is useful because it makes the rendering pipeline understandable.

With a GPU API, many important details are hidden. With software rendering, every pixel is the result of code that exists inside the project.

This makes WarpFrame valuable for learning:

* how triangles are filled
* how depth works
* how projection works
* how 3D coordinates become 2D pixels
* how old renderers and early 3D consoles behaved
* how performance problems appear at the pixel level

## Why PS1 Style?

The PlayStation 1 had a distinctive 3D look because of hardware limitations and rendering shortcuts.

WarpFrame uses that style as a creative and technical target.

Instead of chasing photorealism, WarpFrame focuses on:

* strong silhouettes
* simple geometry
* atmospheric low-poly scenes
* visible rendering artifacts
* nostalgic visual instability
* readable, stylized 3D environments

This makes the renderer suitable for experiments with retro horror, dungeon crawlers, soulslike prototypes, and low-poly 3D scenes.

## Acknowledgements
- [OpenGL Rendering Pipeline](https://www.songho.ca/opengl/gl_pipeline.html)

## License

License information will be added according to the intended distribution model of the project.
