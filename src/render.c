#include "breakout/render.h"

#include <cglm/struct/affine-pre.h>
#include <cglm/struct/affine.h>

#include <glad/glad.h>

void renderer_init(Renderer *renderer) {
    // clang-format off

    const float vertices[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
    };

    // clang-format on

    glGenVertexArrays(1, &renderer->vao);
    glBindVertexArray(renderer->vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float[4]), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float[4]), (void *)sizeof(float[2]));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

static mat4s compute_model(Rect rect) {
    const mat4s scaling = glms_scale_make((vec3s){{rect.width, rect.height, 0}});
    const mat4s model = glms_translate(scaling, (vec3s){{rect.x, rect.y, 0}});
    return model;
}

void renderer_draw_sprite(Renderer renderer, Rect rect) {
    const mat4s model = compute_model(rect);

    (void)renderer;
    (void)model;
}
