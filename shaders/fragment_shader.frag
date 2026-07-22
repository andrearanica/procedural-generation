#version 330

in float vertex_height;
flat in int vertex_type;
in vec2 vertex_texture_coordinates;

uniform sampler2D WaterSampler;
uniform sampler2D GrassSampler;
uniform sampler2D SandSampler;
uniform sampler2D MountainSampler;
uniform sampler2D RockSampler;

out vec4 color;

void main()
{
    if (vertex_type == 0) {
        // Grid vertex
        if (vertex_height >= 0.8) {
            // Grey mountain
            vec4 material_color = texture(RockSampler, vertex_texture_coordinates);
            color = material_color;
        } else if (vertex_height >= 0.5) {
            // Brown mountain
            vec4 material_color = texture(MountainSampler, vertex_texture_coordinates);
            color = material_color;
        } else if (vertex_height >= 0) {
            // Green plains
            vec4 material_color = texture(GrassSampler, vertex_texture_coordinates);
            color = material_color;
        } else {
            // Yellow beach
            vec4 material_color = texture(SandSampler, vertex_texture_coordinates);
            color = material_color;
        }
    } else if (vertex_type == 1) {
        // Water vertex
        vec4 material_color = texture(WaterSampler, vertex_texture_coordinates);
        color = material_color;
        return;

        color = vec4(0.11, 0.63, 0.92, 1);
    }
}
