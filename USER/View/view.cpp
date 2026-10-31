#include "view.h"

View::View(Lcd *lcd, ModelSnapShot* model_snap_shot, GuiState* gui_state):
    page_painter(lcd, gui_state),
    model_snap_shot(model_snap_shot),
    gui_state(gui_state),
    rendered_page(0)
{
    debug_page.init(model_snap_shot);
    page1.init(model_snap_shot);
    page2.init(model_snap_shot);
    page3.init(model_snap_shot);
    page4.init(model_snap_shot);
    page1.set_gui_state(gui_state);
    page2.set_gui_state(gui_state);
    page3.set_gui_state(gui_state);
    page4.set_gui_state(gui_state);
    sync_focus_range();
}

Page& View::get_current_page()
{
    switch (gui_state->get_page_state())
    {
    case 1:
        return page2;
    case 2:
        return page3;
    case 3:
        return page4;
    default:
        return page1;
    }
}

void View::sync_focus_range()
{
    if (gui_state != 0)
    {
        gui_state->set_max_index(get_current_page().get_max_index());
    }
}

void View::handle_input_signal(GuiInputSignal signal)
{
    if (gui_state == 0)
    {
        return;
    }

    gui_state->handle_input_signal(signal);
    sync_focus_range();
}

void View::show()
{
    if (gui_state == 0)
    {
        return;
    }

    sync_focus_range();
    Page& current_page = get_current_page();
    const bool page_changed = rendered_page != &current_page;

    page_painter.page_paint(current_page, model_snap_shot, page_changed);
    rendered_page = &current_page;
}

void View::show_debug()
{
    const bool page_changed = rendered_page != &debug_page;
    page_painter.page_paint(debug_page, model_snap_shot, page_changed);
    rendered_page = &debug_page;
}
