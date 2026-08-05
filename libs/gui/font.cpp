#include "font.h"

std::tuple<glm::vec2, glm::vec2> Font::get_char_uv(char c)
{
    glm::vec2 uv_min, uv_max;
    if (c >= 32 && c <= 126)
    {
        int position = c - 32;

        float row = (int)(position / bitmap_columns);
        float column = (int)(position % bitmap_columns);

        float u_min = column / bitmap_columns;
        float v_min = 1 - ((row + 1) / bitmap_rows);

        float u_max = (column + 1) / bitmap_columns;
        float v_max = 1 - (row / bitmap_rows);

        uv_min = glm::vec2(u_min, v_min);
        uv_max = glm::vec2(u_max, v_max);
    }

    return std::make_tuple(uv_min, uv_max);
}
