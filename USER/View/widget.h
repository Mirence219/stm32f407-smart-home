#ifndef WIDGET_H
#define WIDGET_H

#include <stdint.h>

// RGB565 colors used by the LCD.
#define WIDGET_COLOR_BLACK       0x0000u
#define WIDGET_COLOR_WHITE       0xFFFFu
#define WIDGET_COLOR_RED         0xF800u
#define WIDGET_COLOR_GREEN       0x07E0u
#define WIDGET_COLOR_BLUE        0x001Fu
#define WIDGET_COLOR_YELLOW      0xFFE0u
#define WIDGET_COLOR_CYAN        0x07FFu
#define WIDGET_COLOR_MAGENTA     0xF81Fu
#define WIDGET_COLOR_GRAY        0x8410u
#define WIDGET_COLOR_SILVER      0xC618u
#define WIDGET_COLOR_MAROON      0x8000u
#define WIDGET_COLOR_OLIVE       0x8400u
#define WIDGET_COLOR_DARK_GREEN  0x03E0u
#define WIDGET_COLOR_TEAL        0x0410u
#define WIDGET_COLOR_NAVY        0x000Fu
#define WIDGET_COLOR_PURPLE      0x8010u
#define WIDGET_COLOR_ORANGE      0xFD20u
#define WIDGET_COLOR_BROWN       0x8200u
#define LCD_WIDTH   320
#define LCD_HEIGHT  480

class PagePainter;

class Widget {
private:
    uint16_t rendered_x = 0;
    uint16_t rendered_y = 0;
    uint16_t rendered_width = 0;
    uint16_t rendered_height = 0;
    uint16_t rendered_color = 0;
    const char* rendered_text = 0;
    uint32_t rendered_text_hash = 0;
    bool has_rendered = false;

    uint32_t get_text_hash() const;

protected:
    virtual bool has_style_changed(const PagePainter& painter) const;
    virtual void save_style_state(const PagePainter& painter);

public:
    uint16_t x = 0;
    uint16_t y = 0;
    uint16_t width = 0;
    uint16_t height = 0;
    const char *text = "";
    uint16_t color = 0;

    virtual ~Widget() = default;
    virtual void render(PagePainter& painter) = 0;
    virtual int16_t get_focus_index() const { return -1; }
    void render_if_changed(PagePainter& painter, bool force = false);
};

#endif
