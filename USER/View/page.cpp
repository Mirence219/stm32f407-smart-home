#include "page.h"

void Page::add_widget(Widget* w)
{
    if (w != 0 && widget_count < MAX_WIDGET)
    {
        widgets[widget_count++] = w;
    }
}

void Page::set_max_index(uint16_t index)
{
    max_index = index;
}

uint16_t Page::get_max_index() const
{
    return max_index;
}

void Page::set_gui_state(GuiState* state)
{
    gui_state = state;
}

void Page::init(ModelSnapShot* model_snap_shot)
{
}

void Page::update(ModelSnapShot* model_snap_shot)
{
}