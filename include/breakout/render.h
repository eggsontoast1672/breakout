#pragma once

#include <cglm/types-struct.h>

typedef struct {
    float x;
    float y;
    float width;
    float height;
} Rect;

typedef struct {
    // Shader shader;
    unsigned int vao;
    vec3s draw_color;
} Renderer;

void renderer_init(Renderer *renderer);
void renderer_draw_sprite(Renderer renderer, Rect rect);
