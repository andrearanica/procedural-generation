#include <vector>
#include <iostream>

#include "glm/glm.hpp"
#include "GL/glew.h"

#include "water.h"
#include "vertex.h"
#include "../transform/transform.h"
#include "../camera/camera.h"

bool Water::init()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // First I fill the VBO with the vertices
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
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

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return shader.init();
}

void Water::regenerate_mesh()
{
    std::vector<Vertex> vertices;
    for (int z = 0; z < (height + 1); z++)
    {
        // Terrain vertices
        for (int x = 0; x < (width + 1); x++)
        {
            glm::vec2 texture_coordinates = glm::vec2(x / float(width / 10), z / float(height / 10));
            Vertex v(glm::vec3(position.x + x, -0, position.z + z), VERTEX_WATER, texture_coordinates);

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

    glBindVertexArray(VAO);

    // First I fill the VBO with the vertices
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(Vertex),
        vertices.data(),
        GL_STATIC_DRAW);

    // Finally I fill the EBO with the indices of the faces
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(unsigned int),
        &indices[0],
        GL_STATIC_DRAW);
}

void Water::render(LocalTransform* modelT, Camera* camera, float time)
{  
    shader.enable();

    shader.set_model_transform(modelT->T());
    shader.set_camera_transform(camera->CP());
    shader.set_time(time);

    shader.set_texture_sampler("WaterSampler", 0);

    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, 6 * width * height, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
}