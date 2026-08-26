#ifndef FALLOFF_GENERATOR_H
#define FALLOF_GENERATOR_H

class FalloffGenerator
{
    public:
        static float get_vertex_falloff(float x, float z, float world_width, float world_height);
        static float evaluate(float);
};

#endif
