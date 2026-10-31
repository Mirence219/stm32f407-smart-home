#include "circle.h"
#include "page_painter.h"

bool Circle::has_style_changed(const PagePainter& painter) const
{
    (void)painter;
    return rendered_radius != radius ||
        rendered_border_color != border_color ||
        rendered_filled != filled;
}

void Circle::save_style_state(const PagePainter& painter)
{
    (void)painter;
    rendered_radius = radius;
    rendered_border_color = border_color;
    rendered_filled = filled;
}

void Circle::render(PagePainter& painter)
{
    if (radius == 0)
    {
        return;
    }

    if (filled)
    {
        painter.draw_circle(x + radius, y + radius, color, radius, true);
        if (border_color != color)
        {
            painter.draw_circle(x + radius, y + radius, border_color, radius, false);
        }
    }
    else
    {
        painter.draw_circle(x + radius, y + radius, border_color, radius, false);
    }
}
