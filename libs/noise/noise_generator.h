#ifndef NOISE_GENERATOR_H
#define NOISE_GENERATOR_H

typedef struct {
    float x, z;
} vector2;

class NoiseGenerator {
    private:
        float freq, amp, seed, n_octaves;
        vector2 randomGradient(int ix, int iz);

        float dotGridGradient(int ix, int iz, float x, float z);
        float interpolate(float a0, float a1, float w);
        float perlin(float x, float z);

    public:
        NoiseGenerator(float freq, float amp, float seed, float n_octaves) : freq(freq), amp(amp), seed(seed), n_octaves(n_octaves) {}
        NoiseGenerator(float freq, float amp) : freq(freq), amp(amp) {
            seed = 0;
            n_octaves = 12;
        }

        float get_noise(float x, float z);

        float get_frequency();
        void adjust_frequency(float freq);

        float get_amplitude();
        void adjust_amplitude(float amp);

        float get_seed();
        void set_seed(float seed);

        float get_octaves();
        void adjust_octaves(float delta);
};



#endif
