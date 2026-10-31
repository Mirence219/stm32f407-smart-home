#include "page3.h"
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

void Page3::init(ModelSnapShot* model_snap_shot)
{
    (void)model_snap_shot;
    set_max_index(5);
    background.width = LCD_W;
    background.height = LCD_H;
    background.color = WIDGET_COLOR_DARK_GREEN;
    init_header(header, background.color);

    title.x = 20;
    title.y = 70;
    title.color = WIDGET_COLOR_YELLOW;
    title.background_color = background.color;
    title.font_size = 32;
    title.mode = 1;
    title.text = "CONTROL";

    static const char* LABELS[6] = {
        "Lock: OFF", "Fan: OFF", "LED 0: OFF",
        "LED 1: OFF", "LED 2: OFF", "LED 3: OFF"
    };
    static const uint16_t POSITIONS_X[2] = {14, 164};
    static const uint16_t POSITIONS_Y[3] = {124, 214, 304};
    for (uint8_t i = 0; i < 6; ++i)
    {
        controls[i].x = POSITIONS_X[i % 2];
        controls[i].y = POSITIONS_Y[i / 2];
        controls[i].width = 142;
        controls[i].height = 66;
        controls[i].index = i;
        controls[i].text = LABELS[i];
        controls[i].font_size = 24;
        controls[i].color = WIDGET_COLOR_TEAL;
        controls[i].border_color = WIDGET_COLOR_WHITE;
        controls[i].focus_color = WIDGET_COLOR_YELLOW;
        controls[i].focus_border_width = 4;
    }

    hint.x = 18;
    hint.y = 402;
    hint.color = WIDGET_COLOR_WHITE;
    hint.background_color = background.color;
    hint.font_size = 16;
    hint.mode = 1;
    hint.text = "Auto mode locks its manual controls";

    add_widget(&background);
    for (uint8_t i = 0; i < 4; ++i) add_widget(&header[i]);
    add_widget(&title);
    for (uint8_t i = 0; i < 6; ++i) add_widget(&controls[i]);
    add_widget(&hint);
    update(model_snap_shot);
}

void Page3::update(ModelSnapShot* model_snap_shot)
{
    (void)model_snap_shot;
    if (gui_state == 0)
    {
        return;
    }

    controls[0].text = gui_state->get_lock_enabled() ? "Lock: ON" : "Lock: OFF";

    if (gui_state->get_auto_cooling_enabled())
    {
        controls[1].text = "Fan: AUTO";
        controls[1].color = WIDGET_COLOR_GRAY;
    }
    else
    {
        static const char* FAN_LABELS[4] = {"Fan: OFF", "Fan: 1", "Fan: 2", "Fan: 3"};
        controls[1].text = FAN_LABELS[gui_state->get_fan_level()];
        controls[1].color = WIDGET_COLOR_TEAL;
    }

    for (uint8_t i = 0; i < 4; ++i)
    {
        static const char* OFF_LABELS[4] = {
            "LED 0: OFF", "LED 1: OFF", "LED 2: OFF", "LED 3: OFF"
        };
        static const char* ON_LABELS[4] = {
            "LED 0: ON", "LED 1: ON", "LED 2: ON", "LED 3: ON"
        };
        static const char* AUTO_LABELS[4] = {
            "LED 0: AUTO", "LED 1: AUTO", "LED 2: AUTO", "LED 3: AUTO"
        };
        controls[i + 2].text = gui_state->get_auto_lighting_enabled()
            ? AUTO_LABELS[i]
            : (gui_state->get_led_enabled(i) ? ON_LABELS[i] : OFF_LABELS[i]);
        controls[i + 2].color = gui_state->get_auto_lighting_enabled()
            ? WIDGET_COLOR_GRAY : WIDGET_COLOR_TEAL;
    }
}
