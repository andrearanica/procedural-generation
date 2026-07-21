#ifndef VERTEX_H
#define VERTEX_H

#include "glm/glm.hpp"

enum VertexType {
    VERTEX_GRID, VERTEX_WATER
};

/**
  Structure which contains the vertex attributes
*/
struct Vertex {
  // Spatial coordinates
  glm::vec3 position;

  // Colour
  glm::vec3 color;

  // Type of the vertex
  VertexType type;

  Vertex(float x, float y, float z) {
      position = glm::vec3(x,y,z);
      color = glm::vec3(1, 1, 1);
  }

  Vertex(float x, float y, float z, float r, float g, float b) {
      position = glm::vec3(x, y, z);
      color = glm::vec3(r, g, b);
  }

  Vertex() : position(0), color(0, 0, 0), type(VERTEX_GRID) {}

  Vertex(const glm::vec3 &xyz) : position(xyz), color(1, 1, 1), type(VERTEX_GRID) {}

  Vertex(const glm::vec3 &xyz, VertexType type) : position(xyz), color(1, 1, 1), type(type) {}

  Vertex(const glm::vec3 &xyz, const glm::vec3 &rgb) : position(xyz), color(rgb), type(VERTEX_GRID) {}
};

#endif
