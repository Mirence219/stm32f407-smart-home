#include "button_widget.h"
#include "page_painter.h"

bool ButtonWidget::has_style_changed(const PagePainter& painter) const
{
    const bool focused = index >= 0 && painter.gui_state != 0 &&
        painter.gui_state->get_focus_index() == index;
    return rendered_index != index ||
        rendered_border_color != border_color ||
        rendered_focus_color != focus_color ||
        rendered_focus_border_width != focus_border_width ||
        rendered_text_color != text_color ||
        rendered_font_size != font_size ||
        rendered_focused != focused;
}

void ButtonWidget::save_style_state(const PagePainter& painter)
{
    rendered_index = index;
    rendered_border_color = border_color;
    rendered_focus_color = focus_color;
    rendered_focus_border_width = focus_border_width;
    rendered_text_color = text_color;
    rendered_font_size = font_size;
    rendered_focused = index >= 0 && painter.gui_state != 0 &&
        painter.gui_state->get_focus_index() == index;
}

void ButtonWidget::render(PagePainter& painter)
{
    if (width == 0 || height == 0)
    {
        return;
    }

    const uint16_t right = static_cast<uint16_t>(x + width - 1);
    const uint16_t bottom = static_cast<uint16_t>(y + height - 1);
    painter.fill_rectangle(x, y, right, bottom, color);
    painter.draw_rectangle(x, y, right, bottom, border_color);
    if (text != 0 && text[0] != '\0')
    {
        const uint16_t text_y = static_cast<uint16_t>(y + (height > font_size ? (height - font_size) / 2 : 0));
        painter.draw_text(x + 8, text_y, text_color, color, text, font_size, 1);
    }

    //焦点边框
    if (index < 0 || painter.gui_state == 0 || painter.gui_state->get_focus_index() != index)
    {
        return;
    }

    uint16_t highlight_width = focus_border_width;
    const uint16_t max_highlight_width = (width < height ? width : height) / 2;
    if (highlight_width > max_highlight_width)
    {
        highlight_width = max_highlight_width;
    }

    for (uint16_t i = 0; i < highlight_width; ++i)
    {
        painter.draw_rectangle(x + i, y + i, right - i, bottom - i, focus_color);
    }
}
