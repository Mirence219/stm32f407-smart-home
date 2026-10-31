#include "background.h"
#include "page_painter.h"

void Background::render(PagePainter& painter)
{
    if (width == 0 || height == 0)
    {
        return;
    }

    painter.fill_rectangle(x, y, x + width, y + height, color);
}
