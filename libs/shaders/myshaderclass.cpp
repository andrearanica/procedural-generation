#include "myshaderclass.h"
#include "../utils/utils.h"

void MyShaderClass::set_model_transform(const glm::mat4 &transform) {
  glUniformMatrix4fv(_model_transform_location, 1, GL_FALSE, const_cast<float *>(&transform[0][0]));       
}

void MyShaderClass::set_camera_transform(const glm::mat4 &transform) {
  glUniformMatrix4fv(_camera_transform_location, 1, GL_FALSE, const_cast<float *>(&transform[0][0]));       
}

void MyShaderClass::set_time(float time) {
  glUniform1f(_time_location, time);
}

void MyShaderClass::set_water_texture_sampler(int sampler_id) {
  glUniform1i(_water_texture_sampler_location, sampler_id);
}

void MyShaderClass::set_grass_texture_sampler(int sampler_id) {
  glUniform1i(_grass_texture_sampler_location, sampler_id);
}

void MyShaderClass::set_sand_texture_sampler(int sampler_id) {
  glUniform1i(_sand_texture_sampler_location, sampler_id);
}

bool MyShaderClass::load_shaders() {
  return  add_shader(GL_VERTEX_SHADER,"./shaders/vertex_shader.vert") &&
          add_shader(GL_FRAGMENT_SHADER,"./shaders/fragment_shader.frag");
}

bool MyShaderClass::load_done() {
  _model_transform_location  =      get_uniform_location("Model2World");
  _camera_transform_location =      get_uniform_location("World2Camera");
  _time_location             =      get_uniform_location("Time");
  _water_texture_sampler_location = get_uniform_location("WaterSampler");
  _grass_texture_sampler_location = get_uniform_location("GrassSampler");
  _sand_texture_sampler_location  = get_uniform_location("SandSampler");

  return  (_model_transform_location  !=      INVALID_UNIFORM_LOCATION) &&
          (_camera_transform_location !=      INVALID_UNIFORM_LOCATION) &&
          (_time_location             !=      INVALID_UNIFORM_LOCATION) &&
          (_water_texture_sampler_location != INVALID_UNIFORM_LOCATION) &&
          (_grass_texture_sampler_location != INVALID_UNIFORM_LOCATION) &&
          (_sand_texture_sampler_location  != INVALID_UNIFORM_LOCATION);
}
