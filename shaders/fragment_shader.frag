#version 330

in float vertex_height;

out vec4 color;

void main()
{
    if (vertex_height > 0.8) {
        // Grey mountain
        color = vec4(0.5, 0.5, 0.5, 1.0);
    } else if (vertex_height > 0.5) {
        // Brown mountain
        color = vec4(0.5, 0.25, 0, 1.0);
    } else if (vertex_height > 0) {
        // Green plains
        color = vec4(0.48, 0.98, 0, 1.0);
    } else {
        // Blue sea
        color = vec4(0, 0, 1.0, 1.0);
    }
}