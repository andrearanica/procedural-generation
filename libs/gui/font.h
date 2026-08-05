#ifndef __FONT_H
#define __FONT_H

#include <tuple>

#include "glm/glm.hpp"

class Font
{
    private:
        int bitmap_rows, bitmap_columns;

    public:
        Font()
        {
            this->bitmap_rows = 0;
            this->bitmap_columns = 0;
        }

        Font(int bitmap_rows, int bitmap_columns)
        {
            this->bitmap_rows = bitmap_rows;
            this->bitmap_columns = bitmap_columns;
        }

        std::tuple<glm::vec2, glm::vec2> get_char_uv(char c);
};

#endif