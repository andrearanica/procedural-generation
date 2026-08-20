#ifndef WATER_H
#define WATER_H

#include "../shaders/water_shader.h"
#include "../transform/transform.h"
#include "../camera/camera.h"

class WaterGenerator {
    private:
        glm::vec3 position;
        float width, height;
        WaterShader shader;

    public:
        WaterGenerator(glm::vec3 position, float width, float height) {
            this->position = position;
            this->width = width;
            this->height = height;
        }

        bool init();
        void render(LocalTransform* modelT, Camera* camera, float time);
};

#endif
