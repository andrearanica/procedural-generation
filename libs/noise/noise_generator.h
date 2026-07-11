#ifndef NOISE_GENERATOR_H
#define NOISE_GENERATOR_H

typedef struct {
    float x, z;
} vector2;

class NoiseGenerator {
    private:
        vector2 randomGradient(int ix, int iz);
        float dotGridGradient(int ix, int iz, float x, float z);
        float interpolate(float a0, float a1, float w);
        float perlin(float x, float z);

        float freq, amp;

    public:
        NoiseGenerator(float freq, float amp) : freq(freq), amp(amp) {}

        float get_noise(float x, float z);
};



#endif
