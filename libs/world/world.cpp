#include <iostream>
#include <algorithm>

#include "world.h"
#include "../noise/noise_generator.h"
#include "../utils/utils.h"

float World::get_vertex_distance_from_world_center(Vertex vertex)
{
    glm::vec3 world_center = glm::vec3(width / 2, 0, height / 2);

    float dx = vertex.position.x - world_center.x;
    float dz = vertex.position.z - world_center.z;

    float distance = std::sqrt(dx * dx + dz * dz);
    float max_distance = glm::length(world_center);

    float attenuation = pow(glm::clamp(distance / max_distance, 0.0f, 1.0f), 3);
    return attenuation;
}

void World::render()
{
    std::vector<Vertex> vertices;
    for (int z = 0; z < (height + 1); z++)
    {
        // Terrain vertices
        for (int x = 0; x < (width + 1); x++)
        {
            glm::vec2 texture_coordinates = glm::vec2(x, z);
            Vertex v(glm::vec3(x, 0, z), VERTEX_GRID, texture_coordinates);

            float vertex_noise = noise_generator.get_noise(x, z);
            float falloff = get_vertex_distance_from_world_center(v);

            v.position.y = vertex_noise - falloff;
            vertices.push_back(v);
        }
    }

    std::vector<unsigned int> indices;
    for (int z = 0; z < height; z++)
    {
        for (int x = 0; x < width; x++)
        {
            int sw = z * (width + 1) + x;
            int se = sw + 1;
            int nw = (z + 1) * (width + 1) + x;
            int ne = nw + 1;

            glm::vec3 normal;

            // CCW order: remember that Z+ is towards the camera
            indices.push_back(sw);
            indices.push_back(ne);
            indices.push_back(se);

            normal = get_face_normal(vertices[sw].position, vertices[ne].position, vertices[se].position);

            vertices[sw].normal += normal;
            vertices[se].normal += normal;
            vertices[nw].normal += normal;

            indices.push_back(sw);
            indices.push_back(nw);
            indices.push_back(ne);

            normal = get_face_normal(vertices[sw].position, vertices[nw].position, vertices[ne].position);

            vertices[sw].normal += normal;
            vertices[nw].normal += normal;
            vertices[ne].normal += normal;
        }
    }

    int n_inverted = 0;
    for (int z = 0; z < height; z++)
    {
        for (int x = 0; x < width; x++)
        {
            int sw_index = z * (width + 1) + x;
            int se_index = sw_index + 1;
            int nw_index = (z + 1) * (width + 1) + x;
            int ne_index = nw_index + 1;

            Vertex sw = vertices[sw_index];
            Vertex se = vertices[se_index];
            Vertex nw = vertices[nw_index];
            Vertex ne = vertices[ne_index];

            sw.normal = glm::normalize(sw.normal);
            se.normal = glm::normalize(se.normal);
            nw.normal = glm::normalize(nw.normal);
            ne.normal = glm::normalize(ne.normal);

            if (sw.normal.y < 0) {
                std::cout << "Normale invertita! Numero: " << n_inverted << std::endl;
                n_inverted++;
            }
        }
    }

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO, EBO;

    // First I fill the VBO with the vertices
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(Vertex),
        vertices.data(),
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
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(unsigned int),
        &indices[0],
        GL_STATIC_DRAW);

    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, 6 + 6 * width * height, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);

    water_generator.render();
}
