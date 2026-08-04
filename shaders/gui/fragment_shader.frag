#version 330

in float vertex_height;
flat in int vertex_type;
in vec2 vertex_texture_coordinates;
flat in vec3 vertex_normal;

out vec4 color;

void main()
{
    if (vertex_type == 0)
    {
        color = vec4(1, 1, 1, 1);
    }
    else if (vertex_type == 1)
    {
        color = vec4(1, 0, 0, 1);
    }
}
