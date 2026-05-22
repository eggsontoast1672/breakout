#pragma once

#include <cglm/types-struct.h>

#include "breakout/shader.h"

typedef struct {
    float x;
    float y;
    float width;
    float height;
} Rect;

typedef struct {
    ShaderProgram program;
    unsigned int vao;
    vec3s draw_color;
} Renderer;

void renderer_init(Renderer *renderer);
void renderer_draw_sprite(Renderer renderer, Rect rect);
