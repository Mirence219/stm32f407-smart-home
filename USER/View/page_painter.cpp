#include "page_painter.h"

#include "lcd.h"
#include "page.h"
#include "widget.h"
#include "model_snap_shot.h"

PagePainter::PagePainter(Lcd *lcd, GuiState *gui_state)
    : lcd(lcd), gui_state(gui_state)
{
}

void PagePainter::fill_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    if (lcd != 0)
    {
        lcd->fill_rectangle(x1, y1, x2, y2, color);
    }
}

void PagePainter::draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    if (lcd != 0)
    {
        lcd->draw_rectangle(x1, y1, x2, y2, color);
    }
}

void PagePainter::draw_circle(uint16_t center_x, uint16_t center_y, uint16_t color,
                              uint16_t radius, bool filled)
{
    if (lcd != 0)
    {
        lcd->draw_circle(static_cast<int>(center_x), static_cast<int>(center_y), color, radius, filled);
    }
}

void PagePainter::draw_text(uint16_t x, uint16_t y, uint16_t foreground, uint16_t background,
                            const char *text, uint8_t size, uint8_t mode)
{
    if (lcd != 0 && text != 0)
    {
        lcd->show_string(x, y, foreground, background, text, size, mode);
    }
}

void PagePainter::page_paint(Page& page, ModelSnapShot* model_snap_shot, bool force)
{
    page.update(model_snap_shot);
    for (uint8_t i = 0; i < page.widget_count; i++)
    {
        Widget *widget = page.widgets[i];
        if (widget != 0)
        {
            widget->render_if_changed(*this, force);
        }
    }
}
