#include "breakout/shader.h"

#include <stdio.h>
#include <stdlib.h>

#include "glad/glad.h"

static char *read_file(const char *path) {
    FILE *const file = fopen(path, "r");
    if (file == NULL) {
        perror("Failed to open file");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    const size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *const contents = malloc(size + 1);
    if (contents == NULL) {
        perror("Failed to allocate memory");
        exit(1);
    }

    if (fread(contents, 1, size, file) < size) {
        perror("Failed to read file");
        exit(1);
    }

    contents[size] = '\0';
    fclose(file);
    return contents;
}

static unsigned int create_shader(const char *source, GLenum type) {
    const unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == 0) {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char *const info_log = malloc(length);
        if (info_log == NULL) {
            perror("Failed to allocate memory");
            exit(1);
        }

        glGetShaderInfoLog(shader, length, NULL, info_log);
        fprintf(stderr, "Failed to compile shader: %s", info_log);
        if (info_log[length - 1] != '\n') {
            fprintf(stderr, "\n");
        }

        exit(1);
    }

    return shader;
}

ShaderProgram shader_program_create(const char *vertex_path, const char *fragment_path) {
    char *const vertex_source = read_file(vertex_path);
    char *const fragment_source = read_file(fragment_path);
    const unsigned int vertex_shader = create_shader(vertex_source, GL_VERTEX_SHADER);
    const unsigned int fragment_shader = create_shader(fragment_source, GL_FRAGMENT_SHADER);

    const unsigned int program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    int status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == 0) {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char *const info_log = malloc(length);
        if (info_log == NULL) {
            perror("Failed to allocate memory");
            exit(1);
        }

        glGetProgramInfoLog(program, length, NULL, info_log);
        fprintf(stderr, "Failed to link program: %s", info_log);
        if (info_log[length - 1] != '\n') {
            fprintf(stderr, "\n");
        }

        exit(1);
    }

    return (ShaderProgram){.id = program};
}

void shader_program_use(ShaderProgram program) {
    glUseProgram(program.id);
}

void shader_program_unuse(void) {
    glUseProgram(0);
}
