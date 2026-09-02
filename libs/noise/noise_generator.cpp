#include <math.h>
#include <iostream>
#include <algorithm>

#include "noise_generator.h"

float NoiseGenerator::get_seed()
{
    return seed;
}

void NoiseGenerator::set_seed(float s)
{
    seed = s;
}

float NoiseGenerator::get_amplitude()
{
    return amp;
}

void NoiseGenerator::adjust_amplitude(float delta)
{
    amp = std::max(0.5f, amp + delta);
}

float NoiseGenerator::get_frequency()
{
    return freq;
}

void NoiseGenerator::adjust_frequency(float delta)
{
    freq = freq + delta;
    freq = std::max(freq, 0.1f);
    freq = std::min(freq, 0.9f);
}

// Pseudorandom and deterministic hashing function
vector2 NoiseGenerator::randomGradient(int ix, int iz) {
    // No precomputed gradients mean this works for any number of grid coordinates
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2; 

    unsigned a = ix + seed, b = iz + seed;
    a *= 3284157443;
 
    b ^= a << s | a >> w - s;
    b *= 1911520717;
 
    a ^= b << s | b >> w - s;
    a *= 2048419325;
    float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]
    
    // Create the vector from the angle
    vector2 v;
    v.x = sin(random);
    v.z = cos(random);
 
    return v;
}

float NoiseGenerator::dotGridGradient(int ix, int iz, float x, float z) {
    vector2 gradient = randomGradient(ix, iz);

    float dx = x - (float)ix;
    float dz = z - (float)iz;

    return (dx * gradient.x + dz * gradient.z);
}

float NoiseGenerator::interpolate(float a0, float a1, float w) {
    return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
}

float NoiseGenerator::perlin(float x, float z) {
    int x0 = (int)x;
    int z0 = (int)z;
    int x1 = x0 + 1;
    int z1 = z0 + 1;

    float sx = x - (float)x0;
    float sz = z - (float)z0;

    float n0 = dotGridGradient(x0, z0, x, z);
    float n1 = dotGridGradient(x1, z0, x, z);
    float ix0 = interpolate(n0, n1, sx);

    n0 = dotGridGradient(x0, z1, x, z);
    n1 = dotGridGradient(x1, z1, x, z);
    float ix1 = interpolate(n0, n1, sx);

    float value = interpolate(ix0, ix1, sz);

    return value;
}

float NoiseGenerator::get_noise(float x, float z) {
    // I create temp variables to prevent overwriting the class ones
    float temp_freq = freq;
    float temp_amp = amp;
    
    float noise = 0;
    for (int i = 0; i < 12; i++) {
        float perlin = NoiseGenerator::perlin(x * temp_freq, z * temp_freq);
        noise += perlin * temp_amp;
        temp_freq *= 2;
        temp_amp /= 2;
    }
    noise *= 1.2;

    if (noise > 1.0f) {
        noise = 1.0f;
    } else if (noise < -1.0f) {
        noise = -1.0f;
    }

    return noise;
}
