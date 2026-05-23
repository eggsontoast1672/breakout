#pragma once

#include <cglm/types-struct.h>

#include "breakout/shader.h"
#include "breakout/texture.h"

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

Renderer renderer_init(void);
void renderer_draw_sprite(Renderer renderer, Texture texture, Rect rect);
