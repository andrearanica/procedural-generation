#include "world.h"

#include <iostream>

void draw_face(int x, int z, GLuint* VAO);

void World::create_grid(GLuint* VAO) {
    Vertex vertices[6 * width * height];
    
    for (int x = 0; x < height; x++) {
        for (int z = 0; z < width; z++) {
            int base = 6 * (x * width + z);
            vertices[base+0] = Vertex(glm::vec3(  x,-1.0f, z  ), glm::vec3(1, 0, 0));
            vertices[base+1] = Vertex(glm::vec3(x+1,-1.0f, z  ), glm::vec3(1, 0, 0));
            vertices[base+2] = Vertex(glm::vec3(x+1,-1.0f, z-1), glm::vec3(1, 0, 0));
            vertices[base+3] = Vertex(glm::vec3(x+1,-1.0f, z-1), glm::vec3(0, 0, 1));
            vertices[base+4] = Vertex(glm::vec3(  x,-1.0f, z-1), glm::vec3(0, 0, 1));
            vertices[base+5] = Vertex(glm::vec3(  x,-1.0f, z),   glm::vec3(0, 0, 1));

            std::cout << "Punto iniziale: " << x << ",-1," << z << std::endl;
        }
    }
    glGenVertexArrays(1, VAO);
    glBindVertexArray(*VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
        reinterpret_cast<GLvoid*>(offsetof(struct Vertex, position)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
        reinterpret_cast<GLvoid*>(offsetof(struct Vertex, color)));
    glEnableVertexAttribArray(1);
}

void draw_face(int x, int z, GLuint* VAO) {
    /* Faccia front
    Vertex Vertices[6] = {
        Vertex(glm::vec3(-1.0f,-1.0f, 1.0f)),
        Vertex(glm::vec3( 1.0f,-1.0f, 1.0f)),
        Vertex(glm::vec3( 1.0f,-1.0f,-1.0f)),
        Vertex(glm::vec3( 1.0f,-1.0f,-1.0f)),
        Vertex(glm::vec3(-1.0f,-1.0f,-1.0f)),
        Vertex(glm::vec3(-1.0f,-1.0f, 1.0f)),
    };
    */
}
