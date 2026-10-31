#ifndef VIEW_H
#define VIEW_H

#include "page_painter.h"
#include "page1.h"
#include "page2.h"
#include "page3.h"
#include "page4.h"
#include "debug_page.h"
#include "model_snap_shot.h"
#include "GuiState.h"

class View {
private:
    PagePainter page_painter;
    ModelSnapShot* model_snap_shot;
    GuiState* gui_state;
    Page1 page1;
    Page2 page2;
    Page3 page3;
    Page4 page4;
    DebugPage debug_page;
    Page* rendered_page;
    Page& get_current_page();
    void sync_focus_range();

public:
    View(Lcd *lcd, ModelSnapShot* model_snap_shot, GuiState* gui_state);
    void handle_input_signal(GuiInputSignal signal);
    void show();
    void show_debug();
};

#endif
