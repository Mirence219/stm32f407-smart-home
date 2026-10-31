#include "page1.h"
#include "ili9486.h"

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

void Page1::init(ModelSnapShot* model_snap_shot)
{
    (void)model_snap_shot;
    set_max_index(2);
    background.width = LCD_W;
    background.height = LCD_H;
    background.color = WIDGET_COLOR_NAVY;
    init_header(header, background.color);

    title.x = 16;
    title.y = 82;
    title.color = WIDGET_COLOR_WHITE;
    title.background_color = background.color;
    title.font_size = 36;
    title.mode = 1;
    title.text = "\xd6\xc7\xc4\xdc\xbc\xd2\xbe\xd3\xcf\xb5\xcd\xb3";

    subtitle.x = 20;
    subtitle.y = 132;
    subtitle.color = WIDGET_COLOR_CYAN;
    subtitle.background_color = background.color;
    subtitle.font_size = 16;
    subtitle.mode = 1;
    subtitle.text = "SMART HOME";

    static const char* LABELS[3] = {"Environment", "Control", "Automation"};
    static const uint16_t COLORS[3] = {
        WIDGET_COLOR_TEAL, WIDGET_COLOR_DARK_GREEN, WIDGET_COLOR_PURPLE
    };
    for (uint8_t i = 0; i < 3; ++i)
    {
        navigation[i].x = 20;
        navigation[i].y = static_cast<uint16_t>(190 + i * 82);
        navigation[i].width = 280;
        navigation[i].height = 62;
        navigation[i].index = i;
        navigation[i].text = LABELS[i];
        navigation[i].font_size = 18;
        navigation[i].color = COLORS[i];
        navigation[i].border_color = WIDGET_COLOR_CYAN;
        navigation[i].focus_color = WIDGET_COLOR_YELLOW;
        navigation[i].focus_border_width = 4;
    }

    add_widget(&background);
    for (uint8_t i = 0; i < 4; ++i) add_widget(&header[i]);
    add_widget(&title);
    add_widget(&subtitle);
    for (uint8_t i = 0; i < 3; ++i) add_widget(&navigation[i]);
}
