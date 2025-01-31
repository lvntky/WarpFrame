# WarpFrame TODO List

## Basic OpenGL Window
- [x] Create a `Window` class to manage GLFW window and OpenGL context.
- [x] Initialize GLFW and create a window.
- [x] Set up an OpenGL context.
- [x] Implement a basic render loop (clear screen, swap buffers, poll events).

## Initialize GLAD/GLEW
- [x] Add GLAD or GLEW initialization to the `Window` class.
- [x] Verify OpenGL functions are loaded correctly.

## PS1-Like Rendering Features
- [ ] Implement affine texture mapping:
  - [ ] Disable perspective correction.
  - [ ] Use `GL_NEAREST` for texture filtering.
- [ ] Set up low-resolution rendering:
  - [ ] Render to a framebuffer at 320x240.
  - [ ] Upscale to window size using nearest-neighbor filtering.
- [ ] Simulate limited color depth (16-bit RGB565) and dithering.
- [ ] Load and render 3D models:
  - [ ] Use a simple model format (e.g., OBJ).
  - [ ] Render models using indexed drawing (`glDrawElements`).

## PS1-Specific Effects
- [ ] Add vertex wobble to mimic PS1's lack of floating-point precision.
- [ ] Simulate texture warping (affine texture mapping artifacts).
- [ ] Implement flat shading (`glShadeModel(GL_FLAT)`).
- [ ] Optionally disable Z-buffer and use painter's algorithm for polygon sorting.

## Optimization
- [ ] Batch rendering to reduce draw calls.
- [ ] Minimize OpenGL state changes.
- [ ] Use display lists for faster rendering (optional).

## Post-Processing Effects
- [ ] Add scanlines to simulate CRT displays.
- [ ] Implement color bleed (horizontal blur).
- [ ] Apply dithering to simulate limited color depth.

## Testing and Refinement
- [ ] Test with different 3D models.
- [ ] Compare rendering with actual PS1 games.
- [ ] Fix rendering artifacts and optimize performance.

## Additional Features (Optional)
- [ ] Add simple lighting (directional or point lights).
- [ ] Implement skeletal animations.
- [ ] Add audio using OpenAL or SDL_mixer.

## Polish and Release
- [ ] Create a demo showcasing the engine.
- [ ] Write documentation for the engine's API and features.
- [ ] Publish the project on GitHub or another platform.

---

## Example Code Structure
- [ ] Create `Window.h` and `Window.cc` for window management.
- [ ] Add GLAD/GLEW initialization to the `Window` class.
- [ ] Write a `main.cc` file to test the engine.

---

## Compilation
- [ ] Set up a build script (CMake or Makefile).
- [ ] Compile and test the engine on your platform.

---

## Notes
- Use GLAD for modern OpenGL function loading.
- Use GLFW for window and input management.
- Use GLM for vector and matrix math.
