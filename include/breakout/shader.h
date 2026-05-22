#pragma once

typedef struct {
    unsigned int id;
} ShaderProgram;

ShaderProgram shader_program_create(const char *vertex_path, const char *fragment_path);
void shader_program_use(ShaderProgram program);
void shader_program_unuse(void);
