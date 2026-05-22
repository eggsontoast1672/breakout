#version 330 core

in vec2 v_tex_coords;

out vec4 f_color;

uniform sampler2D u_image;
uniform vec3 u_sprite_color;

void main() {
    f_color = vec4(u_sprite_color, 1.0f) * texture(u_image, v_tex_coords);
}
