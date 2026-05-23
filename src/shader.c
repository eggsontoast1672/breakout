#include "breakout/shader.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "breakout/debug.h"
#include "breakout/logging.h"

#include "glad/glad.h"

#define MAX_SHADER_PATH 256

static char *get_shader_path(const char *path, GLenum type) {
    const char *suffix;
    switch (type) {
    case GL_VERTEX_SHADER: suffix = "vert"; break;
    case GL_FRAGMENT_SHADER: suffix = "frag"; break;
    default: assert(0 && "unknown shader type");
    }

    static char full_path[MAX_SHADER_PATH];
    snprintf(full_path, sizeof full_path, "%s.%s", path, suffix);
    return full_path;
}

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

static unsigned int create_shader_from_path(const char *path, GLenum type) {
    char *const source = read_file(path);
    const unsigned int shader = create_shader(source, type);
    log_message(LOG_INFO, "Loaded shader '%s' (id %u)\n", path, shader);
    free(source);
    return shader;
}

ShaderProgram shader_program_create(const char *path) {
    const char *const vertex_path = get_shader_path(path, GL_VERTEX_SHADER);
    const unsigned int vertex_shader = create_shader_from_path(vertex_path, GL_VERTEX_SHADER);
    const char *const fragment_path = get_shader_path(path, GL_FRAGMENT_SHADER);
    const unsigned int fragment_shader = create_shader_from_path(fragment_path, GL_FRAGMENT_SHADER);

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

    log_message(LOG_INFO, "Linked program object (id %u)\n", program);

    return (ShaderProgram){.id = program};
}

void shader_program_use(ShaderProgram program) {
    glUseProgram(program.id);
}

void shader_program_unuse(void) {
    glUseProgram(0);
}

void shader_program_set_uniform_mat4(ShaderProgram program, const char *name, mat4s matrix) {
    const int location = glGetUniformLocation(program.id, name);
    DEBUG_VALIDATE(glUniformMatrix4fv(location, 1, GL_FALSE, (float *)matrix.raw));
}

void shader_program_set_uniform_vec3(ShaderProgram program, const char *name, vec3s vector) {
    const int location = glGetUniformLocation(program.id, name);
    DEBUG_VALIDATE(glUniform3fv(location, 1, vector.raw));
}
