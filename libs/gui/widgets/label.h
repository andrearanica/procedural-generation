#ifndef __LABEL_H
#define __LABEL_H

#include "widget.h"
#include "../font.h"

class Label : public Widget
{
    private:
        std::string text;
        float text_size;
        Font font_manager;

    protected:
        void update_vertices() override;

    public:
        Label(glm::vec2 position, std::string text, float text_size, Font font_manager)
        {
            this->position = position;
            this->text = text;
            this->text_size = text_size;
            this->font_manager = font_manager;

            update_vertices();
        }
};

#endif
