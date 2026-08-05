#include "widget.h"

void Widget::add_quad(glm::vec2 start_point, glm::vec2 end_point)
{
    // FIXME use window coordinates instead of canonical view volume ones
    Vertex sw = Vertex(glm::vec3(start_point.x, start_point.y, 0));
    Vertex se = Vertex(glm::vec3(end_point.x, start_point.y, 0));
    Vertex ne = Vertex(glm::vec3(end_point.x, end_point.y, 0));
    Vertex nw = Vertex(glm::vec3(start_point.x, end_point.y, 0));

    vertices.push_back(sw);
    vertices.push_back(se);
    vertices.push_back(ne);
    vertices.push_back(nw);
}

void Widget::add_quad_with_texture(glm::vec2 start_point, glm::vec2 end_point, glm::vec2 uv_min, glm::vec2 uv_max)
{
    Vertex sw = Vertex(glm::vec3(start_point.x, start_point.y, 0), uv_min);
    Vertex se = Vertex(glm::vec3(end_point.x, start_point.y, 0), glm::vec2(uv_max.x, uv_min.y));
    Vertex ne = Vertex(glm::vec3(end_point.x, end_point.y, 0), uv_max);
    Vertex nw = Vertex(glm::vec3(start_point.x, end_point.y, 0), glm::vec2(uv_min.x, uv_max.y));

    vertices.push_back(sw);
    vertices.push_back(se);
    vertices.push_back(ne);
    vertices.push_back(nw);
}
