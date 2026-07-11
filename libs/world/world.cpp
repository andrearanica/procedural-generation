#include <iostream>

#include "world.h"
#include "../noise/noise_generator.h"

void World::create_grid(GLuint* VAO) {
    Vertex vertices[6 * width * height];

    for (int x = 0; x < height; x++) {
        for (int z = 0; z < width; z++) {
            int base = 6 * (x * width + z);

            Vertex sw = Vertex(glm::vec3(x,   0, z));
            Vertex se = Vertex(glm::vec3(x+1, 0, z));
            Vertex ne = Vertex(glm::vec3(x+1, 0, z-1));
            Vertex nw = Vertex(glm::vec3(  x, 0, z-1));

            sw.position.y = noise_generator.get_noise(sw.position.x / width, sw.position.z / height);
            se.position.y = noise_generator.get_noise(se.position.x / width, se.position.z / height);
            ne.position.y = noise_generator.get_noise(ne.position.x / width, ne.position.z / height);
            nw.position.y = noise_generator.get_noise(nw.position.x / width, nw.position.z / height);

            vertices[base+0] = sw;
            vertices[base+1] = se;
            vertices[base+2] = ne;
            vertices[base+3] = ne;
            vertices[base+4] = nw;
            vertices[base+5] = sw;

            float freq = 1;
            float amp = 1;
            float val = noise_generator.get_noise(sw.position.x / width, sw.position.z / height);
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
