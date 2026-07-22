#version 330

#define PI             3.14159265359
#define WAVE_LENGTH    5.0
#define WAVE_AMPLITUDE 0.15

// Il vertex shader riceve in input gli attributi dei vertici
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in int  type;

uniform mat4  Model2World;
uniform mat4  World2Camera;
uniform float Time;

out float vertex_height;
flat out int   vertex_type;

float generate_offset(float x, float z)
{
    float radians_x = (x / WAVE_LENGTH + Time) * 2.0 * PI;
    float radians_z = (z / WAVE_LENGTH + Time) * 2.0 * PI;

    return WAVE_AMPLITUDE * 0.5 * (sin(radians_z) + cos(radians_x));
}

vec3 apply_distortion(vec3 vertex)
{
    float x_distortion = generate_offset(vertex.x, vertex.z);
    float y_distortion = generate_offset(vertex.x, vertex.z);
    float z_distortion = generate_offset(vertex.x, vertex.z);

    return vertex + vec3(0, y_distortion, 0);
}

void main()
{
    vec3 p = position;
    // If the vertex is water I simulate wave effect
    vertex_type = type;
    if (vertex_type == 1) {
        p = apply_distortion(p);
    }

    gl_Position = World2Camera * Model2World * vec4(p, 1.0);

    vertex_height = p.y;
}