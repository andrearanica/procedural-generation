#version 330

// Il vertex shader riceve in input gli attributi dei vertici
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in float type;

uniform mat4 Model2World;
uniform mat4 World2Camera;

out float vertex_height;
out float vertex_type;

void main()
{
    gl_Position = World2Camera * Model2World * vec4(position, 1.0);
    vertex_height = position.y;
    vertex_type = type; 
}