#include <vector>
#include <iostream>

#include "glm/glm.hpp"
#include "GL/glew.h"

#include "water.h"
#include "vertex.h"

void WaterGenerator::render()
{
    std::vector<Vertex> vertices;
    for (int z = 0; z < (height + 1); z++)
    {
        // Terrain vertices
        for (int x = 0; x < (width + 1); x++)
        {
            Vertex v(glm::vec3(position.x + x, -0.05, position.z + z), VERTEX_WATER);
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

            // CCW order: remember that Z+ is towards the camera
            indices.push_back(sw);
            indices.push_back(ne);
            indices.push_back(se);

            indices.push_back(sw);
            indices.push_back(nw);
            indices.push_back(ne);
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