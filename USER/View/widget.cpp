#include "widget.h"
#include "page_painter.h"

//FNV-1a 32位哈希算法：检测字符变化
uint32_t Widget::get_text_hash() const
{
    uint32_t hash = 2166136261u;
    if (text == 0)
    {
        return hash;
    }

    const unsigned char* character = reinterpret_cast<const unsigned char*>(text);
    while (*character != '\0')
    {
        hash ^= *character++;
        hash *= 16777619u;
    }
    return hash;
}

bool Widget::has_style_changed(const PagePainter& painter) const
{
    (void)painter;
    return false;
}

void Widget::save_style_state(const PagePainter& painter)
{
    (void)painter;
}

void Widget::render_if_changed(PagePainter& painter, bool force)
{
    const uint32_t current_text_hash = get_text_hash();
    const bool changed = force || !has_rendered ||
        rendered_x != x || rendered_y != y ||
        rendered_width != width || rendered_height != height ||
        rendered_color != color || rendered_text != text ||
        rendered_text_hash != current_text_hash ||
        has_style_changed(painter);

    if (!changed)
    {
        return;
    }

    render(painter);
    rendered_x = x;
    rendered_y = y;
    rendered_width = width;
    rendered_height = height;
    rendered_color = color;
    rendered_text = text;
    rendered_text_hash = current_text_hash;
    save_style_state(painter);
    has_rendered = true;
}
