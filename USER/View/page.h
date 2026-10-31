#ifndef PAGE_H
#define PAGE_H

#include <stdint.h>

class Widget;
class ModelSnapShot;
class GuiState;

class Page
{
public:
    static constexpr uint8_t MAX_WIDGET = 32;
    Widget* widgets[MAX_WIDGET] = {};
    uint8_t widget_count = 0;
    uint16_t max_index = 0;
    GuiState* gui_state = 0;

    void add_widget(Widget* w);
    void set_max_index(uint16_t index);
    uint16_t get_max_index() const;
    void set_gui_state(GuiState* state);
    virtual void init(ModelSnapShot* model_snap_shot);
    virtual void update(ModelSnapShot* model_snap_shot);
};

#endif