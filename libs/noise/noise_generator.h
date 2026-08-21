#ifndef NOISE_GENERATOR_H
#define NOISE_GENERATOR_H

typedef struct {
    float x, z;
} vector2;

class NoiseGenerator {
    private:
        float freq, amp, seed;
        vector2 randomGradient(int ix, int iz);

        float dotGridGradient(int ix, int iz, float x, float z);
        float interpolate(float a0, float a1, float w);
        float perlin(float x, float z);

    public:
        NoiseGenerator(float freq, float amp, float seed) : freq(freq), amp(amp), seed(seed) {}
        NoiseGenerator(float freq, float amp) : freq(freq), amp(amp) {
            seed = 0;
        }

        float get_noise(float x, float z);

        float get_frequency();
        void adjust_frequency(float freq);

        float get_amplitude();
        void adjust_amplitude(float amp);

        float get_seed();
        void set_seed(float seed);
};



#endif
