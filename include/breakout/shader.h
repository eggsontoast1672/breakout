#pragma once

#include <cglm/types-struct.h>

typedef struct {
    unsigned int id;
} ShaderProgram;

ShaderProgram shader_program_create(const char *path);
void shader_program_use(ShaderProgram program);
void shader_program_unuse(void);
void shader_program_set_uniform_mat4(ShaderProgram program, const char *name, mat4s matrix);
void shader_program_set_uniform_int(ShaderProgram program, const char *name, int value);
void shader_program_set_uniform_vec3(ShaderProgram program, const char *name, vec3s vector);
