#include <vector>
#include <tuple>

#include "glm/gtc/matrix_transform.hpp"

#include "gui.h"
#include "glm/glm.hpp"
#include "GL/glew.h"
#include "./widgets/label.h"

bool Gui::init()
{
    gui_texture.load("./textures/font.png");
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    return shader.init();
}

void Gui::clear()
{
    widgets.clear();
}

void Gui::add_label(glm::vec2 position, std::string text, float text_size)
{
    widgets.push_back(std::make_unique<Label>(position, text, text_size, font));
}

void Gui::add_label(glm::vec2 position, std::string text, float text_size, void (*onclick_function)(int))
{
    widgets.push_back(std::make_unique<Label>(position, text, text_size, font, onclick_function));
}

void Gui::render(int window_width, int window_height)
{
    gui_texture.bind(5);

    shader.enable();

    glm::mat4 projection_matrix = glm::ortho(0.0f, (float)window_width, (float)window_height, 0.0f, 1.0f, -1.0f);
    shader.set_projection_transform(projection_matrix);

    shader.set_texture_sampler("BitmapFontSampler", 5);

    std::vector<Vertex> vertices;
    for (const auto &widget : widgets)
    {
        const auto &widget_vertices = widget->get_vertices();
        vertices.insert(vertices.end(), widget_vertices.begin(), widget_vertices.end());
    }

    glBindVertexArray(VAO);
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

void Gui::handle_mouse_click(float x, float y, int button_type)
{
    for (const auto &widget : widgets)
    {
        std::tuple<glm::vec2, glm::vec2> widget_extension = widget->get_box();
        glm::vec2 widget_min = std::get<0>(widget_extension);
        glm::vec2 widget_max = std::get<1>(widget_extension);

        if (widget->onclick_function && widget_min.x <= x && x <= widget_max.x && widget_min.y <= y && y <= widget_max.y)
        {
            widget->onclick_function(button_type);
        }
    }
}
