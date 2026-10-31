#ifndef PAGE_PAINTER_H
#define PAGE_PAINTER_H

#include <stdint.h>
#include "GuiState.h"

class Lcd;
class Page;
class ModelSnapShot;

class PagePainter {
private:
    Lcd *lcd;

public:
    GuiState *gui_state;
    explicit PagePainter(Lcd *lcd, GuiState *gui_state);

    void fill_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
    void draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
    void draw_circle(uint16_t center_x, uint16_t center_y, uint16_t color, uint16_t radius, bool filled);
    void draw_text(uint16_t x, uint16_t y, uint16_t foreground, uint16_t background,
                   const char *text, uint8_t size, uint8_t mode);
    void page_paint(Page& page, ModelSnapShot* model_snap_shot, bool force = false);
};

#endif
