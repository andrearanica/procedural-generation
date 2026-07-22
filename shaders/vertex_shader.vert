#version 330

// Il vertex shader riceve in input gli attributi dei vertici
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in int  type;

uniform mat4  Model2World;
uniform mat4  World2Camera;
uniform float Time;

out float vertex_height;
flat out int   vertex_type;

void main()
{
    gl_Position = World2Camera * Model2World * vec4(position, 1.0);
    vertex_height = position.y;
    vertex_type = type;

    // If the vertex is water I simulate wave effect
    if (vertex_type == 1)
    {
        float s = sin(Time);
        if (s < 0)
        {
            s = -s;
        }
        gl_Position.y += s / 10;
    }
}