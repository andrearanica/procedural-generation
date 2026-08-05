#ifndef VERTEX_H
#define VERTEX_H

#include "glm/glm.hpp"
#include <vector>
#include <iostream>

enum VertexType
{
  VERTEX_GRID,
  VERTEX_WATER
};

/**
  Structure which contains the vertex attributes
*/
struct Vertex
{
  // Spatial coordinates
  glm::vec3 position;

  // Colour
  glm::vec3 color;

  // Type of the vertex
  int type;

  glm::vec2 texture_coordinates;

  glm::vec3 normal = glm::vec3(0, 0, 0);

  Vertex(float x, float y, float z)
  {
    position = glm::vec3(x, y, z);
    color = glm::vec3(1, 1, 1);
  }

  Vertex(float x, float y, float z, float r, float g, float b)
  {
    position = glm::vec3(x, y, z);
    color = glm::vec3(r, g, b);
  }

  Vertex() : position(0), color(0, 0, 0), type(VERTEX_GRID), texture_coordinates() {}

  Vertex(const glm::vec3 &xyz) : position(xyz), color(1, 1, 1), type(VERTEX_GRID), texture_coordinates() {}

  Vertex(const glm::vec3 &xyz, const glm::vec3 &normal) : position(xyz), normal(xyz), color(1, 1, 1), type(VERTEX_GRID), texture_coordinates() {}

  Vertex(const glm::vec3 &xyz, int type, const glm::vec3 &normal) : position(xyz), normal(normal), color(1, 1, 1), type(type), texture_coordinates() {}

  Vertex(const glm::vec3 &xyz, int type, glm::vec3 normal, glm::vec2 texture_coordinates) : position(xyz), normal(normal), color(1, 1, 1), type(type), texture_coordinates(texture_coordinates) {}

  Vertex(const glm::vec3 &xyz, int type, glm::vec2 texture_coordinates) : position(xyz), color(1, 1, 1), type(type), texture_coordinates(texture_coordinates) {}

  Vertex(const glm::vec3 &xyz, glm::vec2 texture_coordinates) : position(xyz), color(1, 1, 1), type(VERTEX_GRID), texture_coordinates(texture_coordinates) {}
};

#endif
