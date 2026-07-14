#include <iostream>

#include "world.h"
#include "../noise/noise_generator.h"

void World::create_grid(GLuint *VAO)
{
    std::vector<Vertex> vertices;
    for (int z = 0; z < (height + 1); z++)
    {
        for (int x = 0; x < (width + 1); x++)
        {
            Vertex v(glm::vec3(x, 0, z), GRID);
            v.position.y = noise_generator.get_noise(x, z);
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

    glGenVertexArrays(1, VAO);
    glBindVertexArray(*VAO);

    GLuint VBO, EBO;

    // First I fill the VBO with the vertices
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(Vertex),
        vertices.data(), 
        GL_STATIC_DRAW
    );

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
        GL_STATIC_DRAW
    );
}

/*
int base = 6 * (x * width + z);

// First I draw the grid mesh
Vertex sw = Vertex(glm::vec3(x,   0, z), GRID);
Vertex se = Vertex(glm::vec3(x+1, 0, z), GRID);
Vertex ne = Vertex(glm::vec3(x+1, 0, z-1), GRID);
Vertex nw = Vertex(glm::vec3(  x, 0, z-1), GRID);

sw.position.y = noise_generator.get_noise(sw.position.x, sw.position.z);
se.position.y = noise_generator.get_noise(se.position.x, se.position.z);
ne.position.y = noise_generator.get_noise(ne.position.x, ne.position.z);
nw.position.y = noise_generator.get_noise(nw.position.x, nw.position.z);

vertices[base + 0] = sw;
vertices[base + 1] = se;
vertices[base + 2] = ne;
vertices[base + 3] = ne;
vertices[base + 4] = nw;
vertices[base + 5] = sw;

if (sw.position.y < 0 || se.position.y < 0 || ne.position.y < 0 || nw.position.y < 0) {
    continue;
}

if (sw.position.y >= 0.5 || se.position.y >= 0.5 || ne.position.y >= 0.5 || nw.position.y >= 0.5) {
    continue;
}

// Then for each mesh I draw a tree mesh
glm::vec3 center_point = glm::vec3(x + 0.5, 0, z - 0.5);
Vertex tree_sw = Vertex(center_point + glm::vec3(-0.05, 0, 0), OBJECT);
Vertex tree_se = Vertex(center_point + glm::vec3(+0.05, 0, 0), OBJECT);
Vertex tree_ne = Vertex(center_point + glm::vec3(+0.05, 0.5, 0), OBJECT);
Vertex tree_nw = Vertex(center_point + glm::vec3(-0.05, 0.5, 0), OBJECT);

std::cout << tree_sw.type << std::endl;

vertices[base + 6] =  tree_sw;
vertices[base + 7] =  tree_se;
vertices[base + 8] =  tree_ne;
vertices[base + 9] =  tree_ne;
vertices[base + 10] = tree_nw;
vertices[base + 11] = tree_sw;
*/