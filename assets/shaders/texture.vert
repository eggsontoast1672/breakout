#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 tex_coords;

out vec2 v_tex_coords;

uniform mat4 u_model;
uniform mat4 u_projection;

void main() {
    v_tex_coords = tex_coords;
    gl_Position = u_projection * u_model * vec4(position, 0.0f, 1.0f);
}
