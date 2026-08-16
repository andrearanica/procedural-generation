#version 330

#define PI             3.14159265359
#define WAVE_LENGTH    3.0
#define WAVE_AMPLITUDE 0.05

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in int  type;
layout (location = 3) in vec2 texture_coordinates;
layout (location = 4) in vec3 normal;

uniform mat4 Projection;

flat out int vertex_type;
out vec2 vertex_texture_coordinates;

void main()
{
    gl_Position = Projection * vec4(position, 1);
    vertex_type = type;
    vertex_texture_coordinates = texture_coordinates;
}
