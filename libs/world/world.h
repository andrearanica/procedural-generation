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
        float evaluate(float value);
        float get_vertex_falloff(float x, float z);
        WorldShader shader;
        GLuint VAO, VBO;
        bool enable_falloff;
        int width;
        int height;
    
    public:
        World(int width, int height) {
            this->width = width;
            this->height = height;
            enable_falloff = true;
        }

        int get_width();
        void adjust_width(int delta);

        int get_height();
        void adjust_height(int delta);

        bool is_falloff_enabled();
        void set_falloff(bool falloff);

        // Initializes the world shader
        bool init();
        void regenerate_mesh(NoiseGenerator* noise_generator);
        void render(LocalTransform* modelT, Camera* camera);
        float get_point_height(float x, float z, NoiseGenerator* noise_generator);
};

#endif
