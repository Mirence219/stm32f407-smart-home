#ifndef BUTTON_WIDGET_H
#define BUTTON_WIDGET_H

#include "widget.h"

class ButtonWidget : public Widget {
private:
    int8_t rendered_index = -1;
    uint16_t rendered_border_color = 0;
    uint16_t rendered_focus_color = 0;
    uint16_t rendered_focus_border_width = 0;
    uint16_t rendered_text_color = 0;
    uint8_t rendered_font_size = 0;
    bool rendered_focused = false;

protected:
    bool has_style_changed(const PagePainter& painter) const override;
    void save_style_state(const PagePainter& painter) override;

public:
    int8_t index = -1;
    uint16_t border_color = 0;
    uint16_t focus_color = 0xFFFF;
    uint16_t focus_border_width = 2;
    uint16_t text_color = 0xFFFF;
    uint8_t font_size = 16;

    void render(PagePainter& painter) override;
    int16_t get_focus_index() const override { return index; }
};

#endif
