### **WarpFrame Low-Level To-Do List**  

This list is categorized into **Core Engine**, **Rendering Features**, **Optimization**, **Development Workflow**, and **Miscellaneous Improvements** to systematically build and refine WarpFrame.

---

## **1. Core Engine Development**  
### **1.1 Project Setup & Build System**
- [x] Ensure **Conan** installs dependencies correctly  
- [x] Create a **.gitignore** for `build/` and temporary files  
- [x] Implement **logging utility** for debugging (`logger.cpp`)  
- [ ] Create **basic window handling** using GLFW (`window.cpp`)  
- [ ] Implement **OpenGL context creation** (`gl_context.cpp`)  

---

## **2. Rendering Features**  
### **2.1 PS1-Specific Rendering Artifacts**  
- [ ] Implement **Affine Texture Mapping** (Disable perspective correction in fragment shader)  
- [ ] Implement **Vertex Snapping to Fixed-Point Grid**  
  - [ ] Define a **fixed-point precision** (e.g., 12.4 format)  
  - [ ] Snap **vertex positions** to nearest fixed-point grid location  
- [ ] Implement **16-bit Color Depth Simulation**  
  - [ ] Convert floating-point colors to **RGB565 / RGB555** format  
  - [ ] Quantize colors during rendering  
- [ ] Implement **Low-Resolution Rendering Mode**  
  - [ ] Render to a **lower-resolution framebuffer**  
  - [ ] Scale up using **nearest-neighbor filtering**  

### **2.2 Shader System**  
- [ ] Set up a **shader loader utility** (`shader_loader.cpp`)  
- [ ] Implement **basic vertex and fragment shaders**  
- [ ] Create **separate shader modules** for PS1 effects  
  - [ ] Affine texture mapping  
  - [ ] Dithering simulation  
  - [ ] 16-bit color depth simulation  
- [ ] Implement **uniform management system** for shaders  

### **2.3 Texture Handling**  
- [ ] Load **textures using stb_image** (upcoming)  
- [ ] Implement **nearest-neighbor texture filtering**  
- [ ] Convert **textures to fixed-point coordinates**  
- [ ] Implement **animated texture warping** (based on vertex jitter)  

### **2.4 Fixed-Function Pipeline Emulation**  
- [ ] Implement **fake fixed-function transformations**  
- [ ] Create a **simplified material system**  
- [ ] Implement **basic light-source emulation**  
- [ ] Simulate **lack of Z-buffer precision** (optional feature)  

### **2.5 Dithering Effects**  
- [ ] Implement **Bayer dithering** in fragment shader  
- [ ] Implement **blue noise dithering** as an option  
- [ ] Add dithering to **alpha blending** for transparency effects  

### **2.6 Software Rendering Mode (Upcoming Feature)**  
- [ ] Implement a **CPU-based rasterizer**  
- [ ] Create **basic triangle filling algorithm**  
- [ ] Implement **fixed-point arithmetic for rasterization**  
- [ ] Optimize **triangle scanline rendering**  

---

## **3. Optimization and Performance**  
### **3.1 OpenGL Optimization**  
- [ ] Implement **vertex array objects (VAOs) & vertex buffer objects (VBOs)**  
- [ ] Reduce **draw calls** by batching models  
- [ ] Use **indexed rendering** to minimize vertex duplication  

### **3.2 Memory Optimization**  
- [ ] Implement **texture compression support**  
- [ ] Use **optimized mesh storage formats**  

### **3.3 Frame Timing & Jitter Accuracy**  
- [ ] Simulate **PS1-style inconsistent frame pacing**  
- [ ] Add an option for **fixed or variable timestep**  

---

## **4. Development Workflow Enhancements**  
### **4.1 Debugging Tools**  
- [ ] Integrate **ImGui (upcoming)** for real-time debugging  
- [ ] Display real-time **FPS counter & render stats**  
- [ ] Create a **simple debugging console**  

### **4.2 Asset Management**  
- [ ] Add **support for additional model formats** (e.g., `.obj`, `.dae`)  
- [ ] Implement **basic asset loader system**  

### **4.3 Build System Improvements**  
- [ ] Configure **automated dependency installation**  
- [ ] Set up **cross-platform testing (Windows, Linux, macOS)**  

---

## **5. Miscellaneous Improvements**  
### **5.1 Additional Retro Effects**  
- [ ] Implement **CRT shader** for scanlines & phosphor glow  
- [ ] Add **barrel distortion shader** to simulate CRT curvature  
- [ ] Implement **glitch effects** for authenticity  

### **5.2 Expanded Rendering Features**  
- [ ] Improve **PS1-style vertex jitter emulation**  
- [ ] Implement **hardware-accurate texture clamping**  
- [ ] Add an **option for fog effects**  

### **5.3 Community & Documentation**  
- [ ] Improve **developer documentation**  
- [ ] Write **code comments for clarity**  
- [ ] Create **tutorials for adding new effects**  

---
