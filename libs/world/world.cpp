#include <iostream>
#include <algorithm>

#include "world.h"
#include "../noise/noise_generator.h"
#include "../utils/utils.h"
#include "../transform/transform.h"

bool World::is_falloff_enabled()
{
    return enable_falloff;
}

void World::set_falloff(bool falloff)
{
    enable_falloff = falloff;
}

bool World::init()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

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

    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<GLvoid *>(offsetof(struct Vertex, normal)));
    glEnableVertexAttribArray(4);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return shader.init();
}

float World::get_vertex_falloff(float x, float z)
{
   float i = x / (float)width * 2 - 1;
   float j = z / (float)height * 2 - 1;
   
   float value = glm::max(glm::abs(i), glm::abs(j));
   return evaluate(value);
}

float World::evaluate(float value)
{
    float a = 3;
    float b = 2.2f;

    return glm::pow(value, a) / (glm::pow(value, a) + glm::pow(b - b * value, a));
}

float World::get_point_height(float x, float z, NoiseGenerator* noise_generator)
{
    float vertex_noise = noise_generator->get_noise(x, z);
    
    if (!enable_falloff)
    {
        return vertex_noise;
    }

    float falloff = get_vertex_falloff(x, z);

    float vertex_height = vertex_noise - falloff * 1;
    glm::mix(vertex_noise, -0.05f, falloff);
    return vertex_height;
}

void World::regenerate_mesh(NoiseGenerator* noise_generator)
{
    std::vector<Vertex> vertices;
    for (int x = 0; x < height; x++)
    {
        for (int z = 0; z < width; z++)
        {
            int base = 6 * (x * width + z);

            glm::vec3 sw(x,     get_point_height(x, z, noise_generator), z);
            glm::vec3 se(x + 1, get_point_height(x + 1, z, noise_generator), z);
            glm::vec3 ne(x + 1, get_point_height(x + 1, z - 1, noise_generator), z - 1);
            glm::vec3 nw(x,     get_point_height(x, z - 1, noise_generator), z - 1);

            glm::vec3 first_face_normal = get_face_normal(sw, se, ne);
            glm::vec3 second_face_normal = get_face_normal(ne, nw, sw);

            // First triangle
            vertices.push_back(Vertex(sw, VERTEX_GRID, first_face_normal, glm::vec2(x, z)));
            vertices.push_back(Vertex(se, VERTEX_GRID, first_face_normal, glm::vec2(x + 1, z)));
            vertices.push_back(Vertex(ne, VERTEX_GRID, first_face_normal, glm::vec2(x + 1, z - 1)));

            // Second triangle
            vertices.push_back(Vertex(ne, VERTEX_GRID, second_face_normal, glm::vec2(x + 1, z - 1)));
            vertices.push_back(Vertex(nw, VERTEX_GRID, second_face_normal, glm::vec2(x, z - 1)));
            vertices.push_back(Vertex(sw, VERTEX_GRID, second_face_normal, glm::vec2(x, z)));
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(Vertex),
        vertices.data(),
        GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void World::render(LocalTransform* modelT, Camera* camera)
{
    shader.enable();

    shader.set_model_transform(modelT->T());
    shader.set_camera_transform(camera->CP());

    shader.set_texture_sampler("GrassSampler", 1);
    shader.set_texture_sampler("SandSampler", 2);
    shader.set_texture_sampler("MountainSampler", 3);
    shader.set_texture_sampler("RockSampler", 4);

    unsigned long n_vertices = static_cast<unsigned long>(6) * width * height;
    
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, n_vertices);

    glBindVertexArray(0);
}
