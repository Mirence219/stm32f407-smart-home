#include "rectangle.h"
#include "page_painter.h"

void Rectangle::render(PagePainter& painter)
{
    if (width == 0 || height == 0)
    {
        return;
    }

    painter.fill_rectangle(x, y, x + width - 1, y + height - 1, color);
}
