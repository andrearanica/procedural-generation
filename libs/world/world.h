#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "glm/glm.hpp"
#include "GL/glew.h"

#include "../noise/noise_generator.h"
#include "vertex.h"
#include "water.h"

class World {
    private:
        float get_vertex_distance_from_world_center(float x, float z);

    public:
        WaterGenerator water_generator;
        NoiseGenerator noise_generator;
        int width;
        int height;

        World(int width, int height, float seed, float freq, float amp) : noise_generator(freq, amp, seed), water_generator(glm::vec3(-width / 2, 0, -height / 2), width * 2, height * 2) {
            this->width = width;
            this->height = height;
        }

        World(int width, int height, float seed) : noise_generator(1.0, 1.0, seed), water_generator(glm::vec3(-width / 2, 0, -height / 2), width * 2, height * 2) {
            this->width = width;
            this->height = height;
        }

        World(int width, int height) : noise_generator(1.0, 1.0), water_generator(glm::vec3(-width / 2, 0, -height / 2), width * 2, height * 2) {
            this->width = width;
            this->height = height;
        }

        void render();
        float get_point_height(float x, float z);
};

#endif
