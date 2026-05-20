#include "breakout/window.h"

#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>

void window_init_system(void) {
    if (!glfwInit()) {
        const char *description;
        glfwGetError(&description);
        fprintf(stderr, "Failed to initialize GLFW: %s\n", description);
        exit(1);
    }
}

void window_shutdown_system(void) {
    glfwTerminate();
}

Window window_create(int width, int height, const char *title) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *const window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL) {
        const char *message;
        glfwGetError(&message);
        fprintf(stderr, "Failed to create window: %s\n", message);
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to load OpenGL\n");
        glfwTerminate();
        exit(1);
    }

    return (Window){window};
}

bool window_should_close(Window window) {
    return glfwWindowShouldClose(window.handle);
}

void window_clear(void) {
    glClear(GL_COLOR_BUFFER_BIT);
}

void window_swap_buffers(Window window) {
    glfwSwapBuffers(window.handle);
}

void window_poll_events(void) {
    glfwPollEvents();
}
