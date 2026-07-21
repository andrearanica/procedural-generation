#ifndef WATER_H
#define WATER_H

class WaterGenerator {
    private:
        float width, height;

    public:
        WaterGenerator(float width, float height) {
            this->width = width;
            this->height = height;
        }

        void render();
};

#endif
