
# Warpframe — Project Roadmap / TODO

This document serves as a detailed **roadmap** for building `warpframe`, a PS1-style software GPU in C++23.  
It breaks down milestones, tasks, acceptance criteria, and risks. Treat it as a **project manager’s checklist**.

---

## Phase 0 — Repo & Build Backbone

**Goal:** Clean repo, builds a “hello window” app.

- [ ] Init repo (`main` branch, MIT LICENSE, .editorconfig, .gitignore, .gitattributes).
- [ ] Add minimal SDL2+ImGui first_run app.
- [ ] Add root `CMakeLists.txt` and `cmake/CPM.cmake`.
- [ ] Scripts: `dev.sh`, `release.sh`, `run.sh`, `test.sh`, `bench.sh`, `format.sh`, `tidy.sh`, `clean.sh`.
- [ ] Setup clang-format, clang-tidy configs.
- [ ] CI: basic compile check.

**Acceptance:** `./warpframe` opens window on Win/Linux/macOS.  
**Risks:** SDL static link quirks.

---

## Phase 1 — Core Library Skeleton

**Goal:** Split app/lib, framebuffer in place.

- [ ] Targets: `warpframe_lib`, `warpframe` app.
- [ ] Implement `Framebuffer` (RGBA8 + 16-bit depth).
- [ ] Implement `FrameArena` allocator.
- [ ] Implement `JobSystem` skeleton.
- [ ] Stub `render_frame()`.

**Acceptance:** gradient fills framebuffer and displays via SDL.

---

## Phase 2 — Math & Transforms

- [ ] Add vec2/3/4, mat4, TRS utils.
- [ ] Functions: `look_at()`, `perspective_fov()`, `viewport()`.
- [ ] Unit tests for transforms.

---

## Phase 3 — Geometry & Camera

- [ ] OBJ loader with tinyobjloader.
- [ ] CPU pipeline: world → view → proj → clip → NDC → viewport map.
- [ ] Backface culling toggle.

**Acceptance:** wireframe cube renders.

---

## Phase 4 — Clipping & Binning

- [ ] Implement Sutherland–Hodgman clipping (near plane + viewport).
- [ ] Screen tiling (16×16).  
- [ ] Per-tile triangle bins.

**Acceptance:** meshes clipped properly, binned.

---

## Phase 5 — Rasterizer (single-thread)

- [ ] Edge setup + top-left rule.
- [ ] Z-buffer (16-bit).
- [ ] Flat shading, Gouraud, affine texturing.

---

## Phase 6 — Multithreading

- [ ] Tile workers (JobSystem).  
- [ ] Each tile renders independently.

**Acceptance:** FPS scales with cores.

---

## Phase 7 — PS1 Quirks

- [ ] Affine vs perspective-correct toggle.
- [ ] Sub-pixel snap (jitter).
- [ ] 15-bit output with ordered dithering.

---

## Phase 8 — Texturing

- [ ] stb_image loader for PNG/JPG.  
- [ ] Nearest sampling, clamp/wrap.  
- [ ] Demo textured cube.

---

## Phase 9 — Scene Format & Controls

- [ ] JSON scene loader (mesh, tex, transforms).  
- [ ] Camera orbit/FPS controls.  
- [ ] Screenshot hotkey.

---

## Phase 10 — SIMD & Optimization

- [ ] SIMD edge eval, barycentrics, z-test, fill.  
- [ ] SSE2 baseline, AVX2 path.  
- [ ] Align buffers, SoA attributes.

---

## Phase 11 — Testing & QA

- [ ] Unit tests: math, clipper, raster coverage.  
- [ ] Property tests: random triangles stay in bounds.  
- [ ] Fuzz loaders with libFuzzer.

---

## Phase 12 — Benchmarks & Profiling

- [ ] nanobench microbenchmarks.  
- [ ] Tracy profiling zones.  
- [ ] Perf charts in docs.

---

## Phase 13 — CI/CD & Releases

- [ ] GitHub Actions: Linux/Win/macOS matrix.  
- [ ] Build Debug+Release, run tests.  
- [ ] Upload release zips on tag.

---

## Phase 14 — Docs & Demos

- [ ] README with hero GIF, feature list, build steps.  
- [ ] Doxygen/Sphinx → GitHub Pages.  
- [ ] Demo assets (cube, teapot, room).  
- [ ] Explainer blog in docs/notes.

---

## Phase 15 — Stretch Goals

- [ ] Fixed-point math pipeline.  
- [ ] W-buffer.  
- [ ] PSX .TIM/.TMD loaders.  
- [ ] Animation (keyframes).  

---

## Milestones

- **M1:** App + framebuffer + wireframe cube.  
- **M2:** Filled triangles + Z.  
- **M3:** Tile renderer.  
- **M4:** Texturing + PS1 quirks.  
- **M5:** SIMD + benchmarks + docs + first public release.  

