#ifndef __WIDGET_H
#define __WIDGET_H

#include <vector>

#include "glm/glm.hpp"

#include "../../world/vertex.h"

class Widget
{
    protected:
        glm::vec2 position;
        std::vector<Vertex> vertices;

        virtual void update_vertices() = 0;
        void add_quad(glm::vec2 start_point, glm::vec2 end_point);
        void add_quad_with_texture(glm::vec2 start_point, glm::vec2 end_point, glm::vec2 uv_min, glm::vec2 uv_max);

    public:
        std::vector<Vertex> get_vertices()
        {
            return vertices;
        }
};

#endif
