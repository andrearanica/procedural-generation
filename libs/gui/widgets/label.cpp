#include "label.h"

void Label::update_vertices()
{
    for (int i = 0; i < text.size(); i++)
    {
        char letter = text[i];
        glm::vec2 quad_start_position = position + glm::vec2(text_size * i, 0);
        glm::vec2 quad_end_position = quad_start_position + glm::vec2(text_size, text_size);

        std::tuple<glm::vec2, glm::vec2> uv = font_manager.get_char_uv(letter);

        glm::vec2 uv_min = std::get<0>(uv);
        glm::vec2 uv_max = std::get<1>(uv);

        add_quad_with_texture(quad_start_position, quad_end_position, uv_min, uv_max);
    }
}