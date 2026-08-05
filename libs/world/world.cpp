#include <iostream>
#include <algorithm>

#include "world.h"
#include "../noise/noise_generator.h"
#include "../utils/utils.h"

float World::get_vertex_distance_from_world_center(float x, float z)
{
    glm::vec3 world_center = glm::vec3(width / 2, 0, height / 2);

    float dx = x - world_center.x;
    float dz = z - world_center.z;

    float distance = std::sqrt(dx * dx + dz * dz);
    float max_distance = glm::length(world_center);

    float attenuation = pow(glm::clamp(distance / max_distance, 0.0f, 1.0f), 3);
    return attenuation;
}

float World::get_point_height(float x, float z)
{
    float vertex_noise = noise_generator.get_noise(x, z);
    float falloff = get_vertex_distance_from_world_center(x, z);

    float vertex_height = vertex_noise - falloff;
    if (vertex_height > 0 && (x < 1 || z < 1))
    {
        vertex_height = -1;
    }

    return vertex_height;
}

void World::render()
{
    Vertex vertices[6 * width * height];

    for (int x = 0; x < height; x++)
    {
        for (int z = 0; z < width; z++)
        {
            int base = 6 * (x * width + z);

            glm::vec3 sw(x, get_point_height(x, z), z);
            glm::vec3 se(x + 1, get_point_height(x + 1, z), z);
            glm::vec3 ne(x + 1, get_point_height(x + 1, z - 1), z - 1);
            glm::vec3 nw(x,     get_point_height(x, z - 1), z - 1);

            glm::vec3 first_face_normal = get_face_normal(sw, se, ne);
            glm::vec3 second_face_normal = get_face_normal(ne, nw, sw);

            // First triangle
            vertices[base + 0] = Vertex(sw, VERTEX_GRID, first_face_normal, glm::vec2(x, z));
            vertices[base + 1] = Vertex(se, VERTEX_GRID, first_face_normal, glm::vec2(x + 1, z));
            vertices[base + 2] = Vertex(ne, VERTEX_GRID, first_face_normal, glm::vec2(x + 1, z - 1));

            // Second triangle
            vertices[base + 3] = Vertex(ne, VERTEX_GRID, second_face_normal, glm::vec2(x + 1, z - 1));
            vertices[base + 4] = Vertex(nw, VERTEX_GRID, second_face_normal, glm::vec2(x, z - 1));
            vertices[base + 5] = Vertex(sw, VERTEX_GRID, second_face_normal, glm::vec2(x, z));
        }
    }

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // glDrawArrays(GL_TRIANGLES, 0, 6 * width * height);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        6 * width * height * sizeof(Vertex),
        vertices,
        GL_STATIC_DRAW);

    // Then I set how to retrieve vertex attributes from the Vertex struct
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<GLvoid *>(offsetof(struct Vertex, position)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<GLvoid *>(offsetof(struct Vertex, color)));
    glEnableVertexAttribArray(1);

    glVertexAttribIPointer(2, 1, GL_INT, sizeof(Vertex),
                           (void *)(offsetof(struct Vertex, type)));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<GLvoid *>(offsetof(struct Vertex, texture_coordinates)));
    glEnableVertexAttribArray(3);

    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<GLvoid *>(offsetof(struct Vertex, normal)));
    glEnableVertexAttribArray(4);

    // Finally I fill the EBO with the indices of the faces
    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 6 * width * height);

    glBindVertexArray(0);
}
