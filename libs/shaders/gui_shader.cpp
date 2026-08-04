#include "gui_shader.h"
#include "../utils/utils.h"

void GuiShader::set_model_transform(const glm::mat4 &transform) {
  glUniformMatrix4fv(_model_transform_location, 1, GL_FALSE, const_cast<float *>(&transform[0][0]));       
}

void GuiShader::set_camera_transform(const glm::mat4 &transform) {
  glUniformMatrix4fv(_camera_transform_location, 1, GL_FALSE, const_cast<float *>(&transform[0][0]));       
}

void GuiShader::set_time(float time) {
  glUniform1f(_time_location, time);
}

void GuiShader::set_texture_sampler(std::string uniform_name, int sampler_id) {
  GLint location = get_uniform_location(uniform_name);
  glUniform1i(location, sampler_id);
}

bool GuiShader::load_shaders() {
  return  add_shader(GL_VERTEX_SHADER,"./shaders/gui/vertex_shader.vert") &&
          add_shader(GL_FRAGMENT_SHADER,"./shaders/gui/fragment_shader.frag");
}

bool GuiShader::load_done() {
  /*
  _water_texture_sampler_location = get_uniform_location("WaterSampler");

  return (_water_texture_sampler_location != INVALID_UNIFORM_LOCATION);
  */
   return true;
}
