#include "gui_shader.h"
#include "../utils/utils.h"

void GuiShader::set_texture_sampler(std::string uniform_name, int sampler_id) {
  GLint location = get_uniform_location(uniform_name);
  glUniform1i(location, sampler_id);
}

bool GuiShader::load_shaders() {
  return  add_shader(GL_VERTEX_SHADER,"./shaders/gui/vertex_shader.vert") &&
          add_shader(GL_FRAGMENT_SHADER,"./shaders/gui/fragment_shader.frag");
}

bool GuiShader::load_done() {
  _bitmap_font_sampler_location = get_uniform_location("BitmapFontSampler");

  return (_bitmap_font_sampler_location != INVALID_UNIFORM_LOCATION);
}
