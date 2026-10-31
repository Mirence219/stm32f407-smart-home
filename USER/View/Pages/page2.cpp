#include "page2.h"
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

void init_value_text(Text& text, uint16_t y, uint16_t background_color,
                     ModelType model_type, ModelData::DataName data_name,
                     const char* label)
{
    text.x = 20;
    text.y = y;
    text.width = 280;
    text.color = WIDGET_COLOR_WHITE;
    text.background_color = background_color;
    text.font_size = 24;
    text.mode = 1;
    text.bind_model_data(model_type, data_name, TextDataFormat::FLOAT, label);
}
}

void Page2::init(ModelSnapShot* model_snap_shot)
{
    (void)model_snap_shot;
    set_max_index(0);
    background.width = LCD_W;
    background.height = LCD_H;
    background.color = WIDGET_COLOR_NAVY;
    init_header(header, background.color);

    title.x = 20;
    title.y = 72;
    title.color = WIDGET_COLOR_YELLOW;
    title.background_color = background.color;
    title.font_size = 24;
    title.mode = 1;
    title.text = "ENVIRONMENT";

    init_value_text(temperature, 142, background.color,
                    ModelType::TEMPERATURE_AND_HUMIDITY_SENSOR,
                    ModelData::DataName::TEMPERATURE, "Temperature C");
    init_value_text(humidity, 212, background.color,
                    ModelType::TEMPERATURE_AND_HUMIDITY_SENSOR,
                    ModelData::DataName::HUMIDITY, "Humidity %");
    init_value_text(illumination, 282, background.color,
                    ModelType::LIGHT_SENSOR,
                    ModelData::DataName::LIGHT_INTENSITY, "Illuminance lux");

    hint.x = 20;
    hint.y = 372;
    hint.color = WIDGET_COLOR_SILVER;
    hint.background_color = background.color;
    hint.font_size = 16;
    hint.mode = 1;
    hint.text = "TAB: no selection  BACK: home";

    add_widget(&background);
    for (uint8_t i = 0; i < 4; ++i) add_widget(&header[i]);
    add_widget(&title);
    add_widget(&temperature);
    add_widget(&humidity);
    add_widget(&illumination);
    add_widget(&hint);
    update(model_snap_shot);
}

void Page2::update(ModelSnapShot* model_snap_shot)
{
    temperature.update_model_data(model_snap_shot);
    humidity.update_model_data(model_snap_shot);
    illumination.update_model_data(model_snap_shot);
}
