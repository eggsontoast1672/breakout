#include "breakout/texture.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

typedef struct {
    uint8_t *bytes;
    int width;
    int height;
    int channels;
} TextureData;

static TextureData load_texture_data(const char *path) {
    int width, height, channels;
    uint8_t *const bytes = stbi_load(path, &width, &height, &channels, 0);
    if (bytes == NULL) {
        const char *const message = stbi_failure_reason();
        fprintf(stderr, "Failed to load texture data: %s\n", message);
        exit(1);
    }

    return (TextureData){bytes, width, height, channels};
}

Texture texture_load(const char *path) {
    unsigned int texture;
    const TextureData data = load_texture_data(path);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data.width, data.height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 data.bytes);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    return (Texture){.id = texture};
}

void texture_unload(Texture texture) {
    glDeleteTextures(1, &texture.id);
}

void texture_bind(Texture texture) {
    glBindTexture(GL_TEXTURE_2D, texture.id);
}

void texture_unbind(void) {
    glBindTexture(GL_TEXTURE_2D, 0);
}
