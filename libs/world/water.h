#ifndef WATER_H
#define WATER_H

class WaterGenerator {
    private:
        glm::vec3 position;
        float width, height;

    public:
        WaterGenerator(glm::vec3 position, float width, float height) {
            this->position = position;
            this->width = width;
            this->height = height;
        }

        void render();
};

#endif
