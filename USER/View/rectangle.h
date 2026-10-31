#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "widget.h"

class Rectangle : public Widget {
public:
    void render(PagePainter& painter) override;
};

#endif
