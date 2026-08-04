#version 330

in float vertex_height;
flat in int vertex_type;
in vec2 vertex_texture_coordinates;
flat in vec3 vertex_normal;

out vec4 color;

uniform sampler2D BitmapFontSampler;

void main()
{
    vec4 material_color = texture(BitmapFontSampler, vertex_texture_coordinates);
    color = material_color;
}
