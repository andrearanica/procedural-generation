#version 330

in float vertex_height;
flat in int vertex_type;
in vec2 vertex_texture_coordinates;
flat in vec3 vertex_normal;

uniform sampler2D WaterSampler;

out vec4 color;

void main()
{
    vec4 material_color = texture(WaterSampler, vertex_texture_coordinates);
    color = material_color;
}
