#ifndef CIRCLE_H
#define CIRCLE_H

#include "widget.h"

class Circle : public Widget {
private:
    uint16_t rendered_radius = 0;
    uint16_t rendered_border_color = 0;
    bool rendered_filled = false;

protected:
    bool has_style_changed(const PagePainter& painter) const override;
    void save_style_state(const PagePainter& painter) override;

public:
    uint16_t radius = 0;
    uint16_t border_color = 0;
    bool filled = true;

    void render(PagePainter& painter) override;
};

#endif
