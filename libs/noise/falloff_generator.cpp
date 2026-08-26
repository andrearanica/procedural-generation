#include "falloff_generator.h"
#include "glm/glm.hpp"

float FalloffGenerator::get_vertex_falloff(float x, float z, float world_width, float world_height)
{
   float i = x / (float)world_width * 2 - 1;
   float j = z / (float)world_height * 2 - 1;
   
   float value = glm::max(glm::abs(i), glm::abs(j));
   return evaluate(value);
}

float FalloffGenerator::evaluate(float value)
{
    float a = 3;
    float b = 2.2f;

    return glm::pow(value, a) / (glm::pow(value, a) + glm::pow(b - b * value, a));
}