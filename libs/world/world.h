#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "glm/glm.hpp"
#include "GL/glew.h"

/**
  Structure which contains the vertex attributes
*/
struct Vertex {
  // Spatial coordinates
  glm::vec3 position;

  // Colour
  glm::vec3 color;

  Vertex(float x, float y, float z) {
      position = glm::vec3(x,y,z);
      color = glm::vec3(0, 0, 255);
  }

  Vertex(float x, float y, float z, float r, float g, float b) {
      position = glm::vec3(x, y, z);
      color = glm::vec3(r, g, b);
  }

  Vertex() : position(0), color(0, 0, 0) {}

  Vertex(const glm::vec3 &xyz) : position(xyz), color(0, 0, 255) {}

  Vertex(const glm::vec3 &xyz, const glm::vec3 &rgb) : position(xyz), color(rgb) {}
};

class World {
    public:
        int width;
        int height;

        World(int width, int height) {
            this->width = width;
            this->height = height;
        }

        void create_grid(GLuint* VAO);
};

#endif
