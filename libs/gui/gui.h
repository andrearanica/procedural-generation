#ifndef __GUI_H
#define __GUI_H

#include "../world/vertex.h"

#include <string>

enum WidgetType {
    BUTTON, LABEL
};

class Gui
{
    private:
        std::vector<Vertex> vertices;
        // Creates the vertices to draw the given quad
        void add_quad(glm::vec2 start_point, glm::vec2 end_point);

    public:
        Gui()
        {
            vertices = std::vector<Vertex>();
        }

        void add_label(glm::vec2 point, std::string text);

        void render();
};

#endif
