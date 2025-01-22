# WarpFrame

WarpFrame is a rendering engine designed to replicate the visual quirks and limitations of PlayStation 1-era graphics. It provides an authentic low-poly, wobbly-texture experience that defined the early 3D gaming era. The engine utilizes OpenGL, GLFW, and GLM to recreate the unique rendering artifacts of the PS1, such as texture warping, vertex jitter, and affine texture mapping.

## Project Overview

The name "WarpFrame" is inspired by the characteristic texture warping and vertex instability present in PlayStation 1 graphics. Due to the absence of floating-point precision in the PS1 hardware, textures often appeared distorted and inconsistent as objects moved. This renderer aims to faithfully recreate these effects while allowing for customization and experimentation.

## Features

- **Affine Texture Mapping**: Removes perspective correction, replicating the classic PS1 texture distortion.
- **Vertex Snapping**: Simulates the fixed-point arithmetic of the PS1, causing slight vertex jitter.
- **16-Bit Color Depth Simulation**: Reduces colors to mimic the visual style of PS1 graphics.
- **Low-Resolution Rendering**: Allows rendering at a reduced resolution and upscaling to replicate a retro aesthetic.
- **Fixed-Function Pipeline Emulation**: Recreates the rendering pipeline of early 3D hardware.
- **Dithering Effects**: Simulates PS1-style dithering to enhance color depth limitations.
- **Software Rendering Mode (Upcoming)**: Implements a software rasterization pipeline for accuracy.
- **Post-Processing Effects**: Includes options for CRT filters, scanlines, and other retro effects.

## Project Structure

```
WarpFrame/
│-- CMakeLists.txt
│-- conanfile.txt
│-- src/
│   │-- main.cpp
│   │-- renderer.cpp
│   │-- renderer.h
│   │-- texture.cpp
│   │-- texture.h
│-- shaders/
│   │-- vertex.glsl
│   │-- fragment.glsl
│-- assets/
│   │-- textures/
│   │   │-- texture.png
│   │-- models/
│   │   │-- model.obj
│-- build/  (Generated by CMake)
│-- external/ (Optional for manual dependencies)
│-- docs/ (Documentation & developer notes)
```

## Dependencies

WarpFrame uses Conan for project-wise dependency management. The following libraries are required:

- **GLFW**: Provides window management and input handling.
- **GLEW**: Loads OpenGL function pointers dynamically.
- **GLM**: Offers mathematics utilities, including vector and matrix operations.
- **stb_image (Upcoming)**: Handles image loading for textures.
- **ImGui (Upcoming)**: Will be integrated for debugging and UI support.

## Installation and Build Process

1. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/WarpFrame.git
   cd WarpFrame
   ```
2. Install dependencies using Conan:
   ```sh
   conan install . --build=missing
   ```
3. Generate build files using CMake:
   ```sh
   mkdir build && cd build
   cmake ..
   ```
4. Compile the project:
   ```sh
   cmake --build .
   ```
5. Run the executable:
   ```sh
   ./WarpFrame
   ```

## Development Roadmap

WarpFrame is an evolving project, with several planned improvements and features:

- Improved PS1-style vertex jitter emulation
- Implementation of a software rasterizer
- Enhanced texture filtering techniques
- Additional rendering effects inspired by retro consoles
- Expanded asset support for different model and texture formats
- Debugging tools and UI integration with ImGui

## Contribution Guidelines

Contributions to WarpFrame are welcome. If you would like to contribute, please follow these steps:

1. Fork the repository.
2. Create a feature branch for your changes.
3. Commit your code with clear and concise messages.
4. Submit a pull request with a detailed description of your changes.

Bug reports, feature suggestions, and documentation improvements are also appreciated.

## License

WarpFrame is released under the MIT License. This means you are free to use, modify, and distribute the project as long as proper attribution is given.

## Additional Resources

For more information on PS1 graphics limitations and rendering techniques, refer to the following resources:

- PlayStation 1 GPU Technical Overview
- Affine Texture Mapping and Perspective Correction
- Fixed-Point Arithmetic in Retro Consoles
