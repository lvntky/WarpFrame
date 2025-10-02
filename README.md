
# warpframe

**warpframe** is a modern C++23 experiment in building a **retro software GPU** that mimics the PlayStation 1’s quirks while pushing modern CPUs with threads, SIMD, and cache-aware design.

It is not an emulator. It is not OpenGL. It is a handcrafted pipeline: vertices → clipper → tile bins → raster → framebuffer. Every pixel is touched by your CPU.

---

## Why warpframe?

Because GPUs are black boxes. If you’ve ever asked yourself:

- *How does a vertex become a pixel?*  
- *Why did the PS1’s textures wobble and warp?*  
- *What happens when you rasterize with only integers and affine math?*  

…then warpframe is your microscope. It’s a fast, hackable, low-level playground.

---

## Features (work in progress)

- **Pure CPU rasterizer** (no OpenGL, no Vulkan).  
- **PS1-style quirks**:  
  - Affine texture mapping (toggle vs perspective-correct).  
  - 15-bit RGB output with ordered dithering.  
  - Integer vertex snap for that unmistakable jitter.  
- **Modern tricks**:  
  - Multithreaded tiling renderer.  
  - SIMD hot loops (SSE2 baseline, AVX2 path).  
  - Frame-arena allocator, job system, cache-friendly layouts.  
- **ImGui HUD** for live toggles, metrics, frame timings.  
- **Tiny dependency footprint**: SDL2, ImGui, fmt, stb, tinyobjloader.  

---

## Pipeline Diagram

```
   [OBJ/GLTF] → [Vertex Shader (CPU)] → [Clipping] → [Tile Binning]
           → [Rasterizer: spans, barycentrics, z-buffer]
           → [Texture sampling / shading]
           → [Dither / quantize 15-bit]
           → [Framebuffer (RGBA8)]
           → [SDL2 Present]
```

---

## Screenshots

*(insert GIF/WebM of spinning textured cube with affine wobble vs perspective-correct toggle here)*

---

## Getting Started

Clone and build:

```bash
git clone https://github.com/yourname/warpframe
cd warpframe
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
./build/warpframe
```

Run helper scripts (Linux/macOS):

```bash
scripts/dev.sh      # Debug + run
scripts/release.sh  # Release + run
scripts/test.sh     # Run unit tests
scripts/bench.sh    # Run microbenchmarks
scripts/format.sh   # clang-format sources
```

Windows: use `scripts/dev.sh` under Git-Bash or run CMake manually in PowerShell.

---

## Roadmap

- [x] Framebuffer + SDL2 present loop  
- [x] Wireframe rendering  
- [ ] Filled triangles with depth buffer  
- [ ] Tile binning + multithreaded rasterizer  
- [ ] Affine texturing + perspective toggle  
- [ ] Dithering + fixed-point math pipeline  
- [ ] SIMD accelerated spans  
- [ ] Scene format, camera controls, demo assets  
- [ ] Benchmarks, docs, public release  

Full detailed roadmap is in [`warpframe_todo.md`](./warpframe_todo.md).

---

## Why It’s Different

Most software rasterizers try to look like OpenGL. warpframe doesn’t. It embraces **imperfections**:

- PS1-style affine warping.  
- Precision loss by design.  
- Dithered color output.  

Yet, it also embraces **modern CPUs**: threads, vectorization, cache-friendly data layouts.

This isn’t nostalgia. It’s a study in how to **abuse a CPU like a GPU**.

---

## Performance

warpframe aims to be fast enough to push 100k+ textured triangles at 60 FPS on a modern desktop CPU.  

Benchmarks are tracked in CI. Expect charts soon.

---

## Tech Stack

- **C++23** with `std::jthread`, `std::barrier`, `std::simd`.  
- **SDL2** for window, input, texture blitting.  
- **Dear ImGui** for HUD/UI.  
- **fmt**, **stb**, **tinyobjloader**.  
- **CMake + CPM** for dependency management.  

---

## Contributing

This is a work in progress. PRs, issues, and experiments welcome.  
If you want to hack on rasterizers, bring your profiler.

---

## License

MIT. Free to use, fork, and experiment.

---

## Star This Project

If you find warpframe interesting, educational, or just enjoy seeing triangles burn your CPU cycles, please star the repo. Stars tell me to keep going, and help others discover it.

