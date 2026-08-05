#ifndef __GUI_H
#define __GUI_H

#include "../world/vertex.h"
#include "./widgets/widget.h"
#include "font.h"

#include <memory>
#include <string>

enum WidgetType {
    BUTTON, LABEL
};

class Gui
{
    private:
        Font font;
        std::vector<std::unique_ptr<Widget>> widgets;
        std::vector<Vertex> vertices;

    public:
        Gui() : font(5, 19)
        {
            vertices = std::vector<Vertex>();
        }

        void add_label(glm::vec2 position, std::string text, float text_size);

        void render();
        void handle_mouse_click(int x, int y);
};

#endif
