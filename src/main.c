#include "glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "breakout/window.h"

int main(void) {
    window_init_system();

    const Window window = window_create(800, 600, "Breakout");

    int width, height, nr_channels;
    stbi_uc *const data = stbi_load("textures/awesomeface.png", &width, &height, &nr_channels, 0);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    while (!window_should_close(window)) {
        window_clear();
        window_swap_buffers(window);
        window_poll_events();
    }

    glDeleteTextures(1, &texture);
    stbi_image_free(data);
    window_shutdown_system();
}
