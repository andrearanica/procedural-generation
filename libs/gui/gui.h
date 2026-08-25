#ifndef __GUI_H
#define __GUI_H

#include "../world/vertex.h"
#include "./widgets/widget.h"
#include "font.h"
#include "../shaders/gui_shader.h"
#include "../texture/texture.h"

#include <memory>
#include <string>

enum WidgetType {
    BUTTON, LABEL
};

class Gui
{
    private:
        Font font;
        std::vector<std::unique_ptr<Widget>> widgets;
        GuiShader shader;
        GLuint VAO, VBO;
        Texture2D gui_texture;

    public:
        Gui() : font(5, 19), gui_texture() {}

        void clear();
        void add_label(glm::vec2 position, std::string text, float text_size);
        void add_label(glm::vec2 position, std::string text, float text_size, void (*onclick_function)(int));

        bool init();
        void render(int window_width, int window_height);
        void handle_mouse_click(float x, float y, int button_type);
};

#endif
