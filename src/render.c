#include "breakout/render.h"

#include <cglm/cam.h>
#include <cglm/struct/affine-pre.h>
#include <cglm/struct/affine.h>

#include "breakout/texture.h"

#include "glad/glad.h"

static unsigned int create_quad_mesh(void) {
    // clang-format off

    static const float vertices[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
    };

    // clang-format on

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

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

    return vao;
}

static mat4s create_projection_matrix(void) {
    mat4s matrix;
    glm_ortho(0.0f, 300.0f, 300.0f, 0.0f, 1.0f, -1.0f, matrix.raw);
    return matrix;
}

Renderer renderer_init(void) {
    const ShaderProgram program = shader_program_create("assets/shaders/texture");
    const unsigned int vao = create_quad_mesh();
    const vec3s draw_color = {{1.0f, 1.0f, 1.0f}};

    shader_program_set_uniform_mat4(program, "u_projection", create_projection_matrix());

    return (Renderer){
        .program = program,
        .vao = vao,
        .draw_color = draw_color,
    };
}

static mat4s compute_model(Rect rect) {
    const mat4s scaling = glms_scale_make((vec3s){{rect.width, rect.height, 0}});
    const mat4s model = glms_translate(scaling, (vec3s){{rect.x, rect.y, 0}});
    return model;
}

void renderer_draw_sprite(Renderer renderer, Texture texture, Rect rect) {
    const mat4s model = compute_model(rect);

    shader_program_use(renderer.program);
    glBindVertexArray(renderer.vao);
    texture_bind(texture);

    shader_program_set_uniform_mat4(renderer.program, "u_model", model);
    shader_program_set_uniform_vec3(renderer.program, "u_sprite_color", renderer.draw_color);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    shader_program_unuse();
    glBindVertexArray(0);
    texture_unbind();
}
