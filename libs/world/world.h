#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "glm/glm.hpp"
#include "GL/glew.h"

#include "../noise/noise_generator.h"
#include "vertex.h"
#include "water.h"
#include "../shaders/world_shader.h"
#include "../transform/transform.h"
#include "../camera/camera.h"

class World {
    private:
        float get_vertex_distance_from_world_center(float x, float z);
        WorldShader shader;
    
    public:
        NoiseGenerator noise_generator;
        int width;
        int height;

        World(int width, int height, float seed, float freq, float amp) : noise_generator(freq, amp, seed) {
            this->width = width;
            this->height = height;
        }

        World(int width, int height, float seed) : noise_generator(1.0, 1.0, seed) {
            this->width = width;
            this->height = height;
        }

        World(int width, int height) : noise_generator(1.0, 1.0) {
            this->width = width;
            this->height = height;
        }

        // Initializes the world shader
        bool init();
        void render(LocalTransform* modelT, Camera* camera);
        float get_point_height(float x, float z);
};

#endif
