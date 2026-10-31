#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "widget.h"

class Background : public Widget {
public:
    uint16_t width = LCD_WIDTH;
    uint16_t height = LCD_HEIGHT;
    void render(PagePainter& painter) override;
};

#endif
