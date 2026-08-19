#include <algorithm>

#include "widget.h"

void Widget::add_quad(glm::vec2 start_point, glm::vec2 end_point)
{
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
    Vertex sw = Vertex(glm::vec3(start_point.x, end_point.y, 0), uv_min);
    Vertex se = Vertex(glm::vec3(end_point.x, end_point.y, 0), glm::vec2(uv_max.x, uv_min.y));
    Vertex ne = Vertex(glm::vec3(end_point.x, start_point.y, 0), uv_max);
    Vertex nw = Vertex(glm::vec3(start_point.x, start_point.y, 0), glm::vec2(uv_min.x, uv_max.y));

    vertices.push_back(sw);
    vertices.push_back(se);
    vertices.push_back(ne);
    vertices.push_back(nw);
}

std::tuple<glm::vec2, glm::vec2> Widget::get_box()
{
    std::vector<float> xs, ys;

    for (Vertex vertex : vertices)
    {
        xs.push_back(vertex.position.x);
        ys.push_back(vertex.position.y);
    }

    float max_x = *std::max_element(xs.begin(), xs.end());
    float min_x = *std::min_element(xs.begin(), xs.end());

    float max_y = *std::max_element(ys.begin(), ys.end());
    float min_y = *std::min_element(ys.begin(), ys.end());

    glm::vec2 min = glm::vec2(min_x, min_y);
    glm::vec2 max = glm::vec2(max_x, max_y);

    return std::make_tuple(min, max);
}
