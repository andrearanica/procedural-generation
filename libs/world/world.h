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
        int width;
        int height;

        World(int width, int height) {
            this->width = width;
            this->height = height;
        }

        // Initializes the world shader
        bool init();
        void render(LocalTransform* modelT, Camera* camera, NoiseGenerator* noise_generator);
        float get_point_height(float x, float z, NoiseGenerator* noise_generator);
};

#endif
