#include <vector>
#include <tuple>

#include "gui.h"

#include "glm/glm.hpp"
#include "GL/glew.h"
#include "./widgets/label.h"

void Gui::add_label(glm::vec2 position, std::string text, float text_size)
{
    widgets.push_back(std::make_unique<Label>(position, text, text_size, font));
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

void Gui::handle_mouse_click(int x, int y)
{
}
