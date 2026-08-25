#version 330

in float vertex_height;
flat in int vertex_type;
in vec2 vertex_texture_coordinates;
flat in vec3 vertex_normal;

uniform sampler2D GrassSampler;
uniform sampler2D SandSampler;
uniform sampler2D MountainSampler;
uniform sampler2D RockSampler;

out vec4 color;

void main()
{
    if (vertex_height > 0.05) {
        if (vertex_normal.y >= 0.9) {
            // Green plains
            vec4 material_color = texture(GrassSampler, vertex_texture_coordinates);
            color = material_color;
        } else if (vertex_normal.y >= 0.8) {
            // Brown mountain
            vec4 material_color = texture(MountainSampler, vertex_texture_coordinates);
            color = material_color;
        } else if (vertex_normal.y >= 0) {
            // Grey mountain
            vec4 material_color = texture(RockSampler, vertex_texture_coordinates);
            color = material_color;
        } else {
            color = vec4(0, 0, 0, 1);
        }
    } else {
        // Yellow beach
        vec4 material_color = texture(SandSampler, vertex_texture_coordinates);
        color = material_color;
    }
}
