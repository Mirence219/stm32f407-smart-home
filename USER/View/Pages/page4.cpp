#include "page4.h"
#include "ili9486.h"
#include "GuiState.h"

namespace {
void init_header(Text* header, uint16_t background_color)
{
    static const char* LABELS[4] = {"Home", "Tab", "Back", "Select"};
    static const uint16_t POSITIONS[4] = {8, 84, 160, 240};
    for (uint8_t i = 0; i < 4; ++i)
    {
        header[i].x = POSITIONS[i];
        header[i].y = 12;
        header[i].width = 72;
        header[i].color = WIDGET_COLOR_CYAN;
        header[i].background_color = background_color;
        header[i].font_size = 24;
        header[i].mode = 1;
        header[i].text = LABELS[i];
    }
}
}

void Page4::init(ModelSnapShot* model_snap_shot)
{
    (void)model_snap_shot;
    set_max_index(1);
    background.width = LCD_W;
    background.height = LCD_H;
    background.color = WIDGET_COLOR_NAVY;
    init_header(header, background.color);

    title.x = 20;
    title.y = 72;
    title.color = WIDGET_COLOR_YELLOW;
    title.background_color = background.color;
    title.font_size = 32;
    title.mode = 1;
    title.text = "AUTOMATION";

    static const char* LABELS[2] = {"Auto cooling: OFF", "Auto lighting: OFF"};
    static const uint16_t POSITIONS_Y[2] = {140, 248};
    static const char* DETAILS[2] = {
        "Fan 1/2/3 at 28/30/32 C",
        "LEDs light below 800/400/150/50 lux"
    };

    for (uint8_t i = 0; i < 2; ++i)
    {
        automation[i].x = 16;
        automation[i].y = POSITIONS_Y[i];
        automation[i].width = 288;
        automation[i].height = 68;
        automation[i].index = i;
        automation[i].text = LABELS[i];
        automation[i].font_size = 24;
        automation[i].color = WIDGET_COLOR_TEAL;
        automation[i].border_color = WIDGET_COLOR_WHITE;
        automation[i].focus_color = WIDGET_COLOR_YELLOW;
        automation[i].focus_border_width = 4;

        description[i].x = 20;
        description[i].y = static_cast<uint16_t>(POSITIONS_Y[i] + 74);
        description[i].width = 288;
        description[i].color = WIDGET_COLOR_SILVER;
        description[i].background_color = background.color;
        description[i].font_size = 16;
        description[i].mode = 1;
        description[i].text = DETAILS[i];
    }

    add_widget(&background);
    for (uint8_t i = 0; i < 4; ++i) add_widget(&header[i]);
    add_widget(&title);
    for (uint8_t i = 0; i < 2; ++i)
    {
        add_widget(&automation[i]);
        add_widget(&description[i]);
    }
    update(model_snap_shot);
}

void Page4::update(ModelSnapShot* model_snap_shot)
{
    (void)model_snap_shot;
    if (gui_state == 0)
    {
        return;
    }

    automation[0].text = gui_state->get_auto_cooling_enabled()
        ? "Auto cooling: ON" : "Auto cooling: OFF";
    automation[1].text = gui_state->get_auto_lighting_enabled()
        ? "Auto lighting: ON" : "Auto lighting: OFF";
    automation[0].color = gui_state->get_auto_cooling_enabled()
        ? WIDGET_COLOR_DARK_GREEN : WIDGET_COLOR_TEAL;
    automation[1].color = gui_state->get_auto_lighting_enabled()
        ? WIDGET_COLOR_DARK_GREEN : WIDGET_COLOR_TEAL;
}
