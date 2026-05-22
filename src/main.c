#include "glad/glad.h"

#include "breakout/shader.h"
#include "breakout/window.h"

// clang-format off

static const float vertices[] = {
    -0.5f,  0.5f,
     0.5f,  0.5f,
    -0.5f, -0.5f,
     0.5f,  0.5f,
    -0.5f, -0.5f,
     0.5f, -0.5f,
};

// clang-format on

int main(void) {
    window_init_system();

    const Window window = window_create(800, 600, "Breakout");
    const ShaderProgram program = shader_program_create("assets/shaders/quad");

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float[2]), 0);

    while (!window_should_close(window)) {
        window_clear();

        shader_program_use(program);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        shader_program_unuse();

        window_swap_buffers(window);
        window_poll_events();
    }

    window_shutdown_system();
}
