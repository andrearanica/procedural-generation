#include "water_shader.h"
#include "../utils/utils.h"

void WaterShader::set_model_transform(const glm::mat4 &transform) {
  glUniformMatrix4fv(_model_transform_location, 1, GL_FALSE, const_cast<float *>(&transform[0][0]));       
}

void WaterShader::set_camera_transform(const glm::mat4 &transform) {
  glUniformMatrix4fv(_camera_transform_location, 1, GL_FALSE, const_cast<float *>(&transform[0][0]));       
}

void WaterShader::set_time(float time) {
  glUniform1f(_time_location, time);
}

void WaterShader::set_texture_sampler(std::string uniform_name, int sampler_id) {
  GLint location = get_uniform_location(uniform_name);
  glUniform1i(location, sampler_id);
}

bool WaterShader::load_shaders() {
  return  add_shader(GL_VERTEX_SHADER,"./shaders/water/vertex_shader.vert") &&
          add_shader(GL_FRAGMENT_SHADER,"./shaders/water/fragment_shader.frag");
}

bool WaterShader::load_done() {
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
