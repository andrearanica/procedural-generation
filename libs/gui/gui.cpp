#include "gui.h"

#include "glm/glm.hpp"
#include "GL/glew.h"

#include <vector>

void Gui::add_quad(glm::vec2 start_point, glm::vec2 end_point, glm::vec2 uv_min, glm::vec2 uv_max)
{
    // FIXME use window coordinates instead of canonical view volume ones
    Vertex sw = Vertex(glm::vec3(start_point.x, start_point.y, 0), uv_min);
    Vertex se = Vertex(glm::vec3(end_point.x, start_point.y, 0), glm::vec2(uv_max.x, uv_min.y));
    Vertex ne = Vertex(glm::vec3(end_point.x, end_point.y, 0), uv_max);
    Vertex nw = Vertex(glm::vec3(start_point.x, end_point.y, 0), glm::vec2(uv_min.x, uv_max.y));

    vertices.push_back(sw);
    vertices.push_back(se);
    vertices.push_back(ne);
    vertices.push_back(nw);
}

void Gui::add_label(glm::vec2 start_point, std::string text)
{
    // 36 caratteri
    float letter_quad_dim = 0.2;
    for (int i = 0; i < text.size(); i++)
    {
        char letter = text[i];
        glm::vec2 quad_start_position = start_point + glm::vec2(letter_quad_dim * i, 0);
        glm::vec2 quad_end_position = quad_start_position + glm::vec2(letter_quad_dim, 0.3);

        glm::vec2 uv_min, uv_max;
        if (letter >= 65 && letter <= 90)
        {
            // Upper letters
            uv_min = glm::vec2((float)(letter - 65) / 36, 0);
            uv_max = glm::vec2((float)(letter - 65 + 1) / 36, 1);
        }

        add_quad(quad_start_position, quad_end_position, uv_min, uv_max);
    }
}

void Gui::render()
{
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
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
    glBindVertexArray(VAO);

    glDrawArrays(GL_QUADS, 0, vertices.size());

    glBindVertexArray(0);
}
