#include <vector>
#include <iostream>

#include "glm/glm.hpp"
#include "GL/glew.h"

#include "water.h"
#include "vertex.h"

void WaterGenerator::render()
{
    std::vector<Vertex> vertices;

    // Water plane vertices
    float water_plane_extension = width * height * 10;
    Vertex sw(glm::vec3(-water_plane_extension, -0.05, -water_plane_extension), VERTEX_WATER);
    Vertex se(glm::vec3(water_plane_extension, -0.05, -water_plane_extension), VERTEX_WATER);
    Vertex nw(glm::vec3(-water_plane_extension, -0.05, water_plane_extension), VERTEX_WATER);
    Vertex ne(glm::vec3(water_plane_extension, -0.05, water_plane_extension), VERTEX_WATER);

    vertices.push_back(sw);
    vertices.push_back(se);
    vertices.push_back(nw);
    vertices.push_back(ne);

    std::vector<unsigned int> indices;
    indices.push_back(0);
    indices.push_back(2);
    indices.push_back(1);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(3);

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

    // Finally I fill the EBO with the indices of the faces
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(unsigned int),
        &indices[0],
        GL_STATIC_DRAW);

    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, 6 * width * height, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
}