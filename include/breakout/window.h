#pragma once

#include <stdbool.h>

#include <GLFW/glfw3.h>

typedef struct {
    GLFWwindow *handle;
} Window;

void window_init_system(void);
void window_shutdown_system(void);

Window window_create(int width, int height, const char *title);
bool window_should_close(Window window);
void window_clear(void);
void window_swap_buffers(Window window);
void window_poll_events(void);
