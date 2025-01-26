#include <GLFW/glfw3.h>
#include <iostream>
#include "../include/warpframe/logger/logger.h"

int main() {
    Logger::init();
    Logger::getLogger()->error("WarpFrame initialized.");
    
    /*
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "WarpFrame", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Set the OpenGL viewport size (optional)
    glViewport(0, 0, 800, 600);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Poll and handle events (e.g., input, window events)
        glfwPollEvents();

        // Render here (for now, just clear the screen with a color)
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);  // Set a clear color
        glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen

        // Swap buffers (render to the screen)
        glfwSwapBuffers(window);
    }

    // Clean up and terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();
    */

    return 0;
}

