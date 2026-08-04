#version 330

in float vertex_height;
flat in int vertex_type;
in vec2 vertex_texture_coordinates;
flat in vec3 vertex_normal;

out vec4 color;

void main()
{
    color = vec4(1, 1, 1, 1);
}
