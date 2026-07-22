#version 330

in float vertex_height;
flat in int vertex_type;

out vec4 color;

void main()
{
    // TODO use uniforms instead of constant value
    if (vertex_type == 0) {
        if (vertex_height >= 0.8) {
            // Grey mountain
            color = vec4(0.5, 0.5, 0.5, 1.0);
        } else if (vertex_height >= 0.5) {
            // Brown mountain
            color = vec4(0.5, 0.25, 0, 1.0);
        } else if (vertex_height >= 0) {
            // Green plains
            color = vec4(0.48, 0.98, 0, 1.0);
        } else {
            // Yellow beach
            color = vec4(1.0, 1.0, 0, 1.0);
        }
    } else if (vertex_type == 1) {
        color = vec4(0, 0, 1, 1);
    }
}