#include "text.h"
#include "page_painter.h"
#include "model_snap_shot.h"

namespace {
void append_character(char* destination, uint8_t capacity, uint8_t& length, char value)
{
    if (length + 1 < capacity)
    {
        destination[length++] = value;
        destination[length] = '\0';
    }
}

void append_text(char* destination, uint8_t capacity, uint8_t& length, const char* value)
{
    if (value == 0)
    {
        return;
    }

    while (*value != '\0')
    {
        append_character(destination, capacity, length, *value++);
    }
}

void append_uint32(char* destination, uint8_t capacity, uint8_t& length, uint32_t value)
{
    char digits[10];
    uint8_t digit_count = 0;
    do
    {
        digits[digit_count++] = static_cast<char>('0' + value % 10);
        value /= 10;
    } while (value != 0 && digit_count < sizeof(digits));

    while (digit_count > 0)
    {
        append_character(destination, capacity, length, digits[--digit_count]);
    }
}
}

bool Text::has_style_changed(const PagePainter& painter) const
{
    (void)painter;
    return rendered_background_color != background_color ||
        rendered_font_size != font_size ||
        rendered_mode != mode;
}

void Text::save_style_state(const PagePainter& painter)
{
    (void)painter;
    rendered_background_color = background_color;
    rendered_font_size = font_size;
    rendered_mode = mode;
}

void Text::bind_model_data(ModelType model_type, ModelData::DataName data_name,
                           TextDataFormat format, const char* label)
{
    bound_model_type = model_type;
    bound_data_name = data_name;
    bound_data_format = format;
    bound_label = label;
    data_bound = true;
    text = display_text;
}

void Text::update_model_data(const ModelSnapShot* model_snap_shot)
{
    if (!data_bound)
    {
        return;
    }

    display_text[0] = '\0';
    uint8_t length = 0;
    append_text(display_text, sizeof(display_text), length, bound_label);
    append_text(display_text, sizeof(display_text), length, ": ");

    if (model_snap_shot == 0)
    {
        append_text(display_text, sizeof(display_text), length, "N/A");
        text = display_text;
        return;
    }

    const ModelData data = model_snap_shot->get(bound_model_type);
    bool attached = false;
    if (data.get(ModelData::DataName::ATTACHED, attached) && !attached)
    {
        append_text(display_text, sizeof(display_text), length, "N/A");
        text = display_text;
        return;
    }

    bool bool_value = false;
    uint32_t uint_value = 0;
    float float_value = 0.0f;
    bool value_available = false;

    switch (bound_data_format)
    {
    case TextDataFormat::BOOL:
        value_available = data.get(bound_data_name, bool_value);
        if (value_available)
        {
            append_text(display_text, sizeof(display_text), length, bool_value ? "ON" : "OFF");
        }
        break;
    case TextDataFormat::UINT32:
        value_available = data.get(bound_data_name, uint_value);
        if (value_available)
        {
            append_uint32(display_text, sizeof(display_text), length, uint_value);
        }
        break;
    case TextDataFormat::FLOAT:
        value_available = data.get(bound_data_name, float_value);
        if (value_available)
        {
            if (float_value < 0.0f)
            {
                append_character(display_text, sizeof(display_text), length, '-');
                float_value = -float_value;
            }

            if (float_value > 429496000.0f)
            {
                value_available = false;
            }
            else
            {
                const uint32_t tenths = static_cast<uint32_t>(float_value * 10.0f + 0.5f);
                append_uint32(display_text, sizeof(display_text), length, tenths / 10);
                append_character(display_text, sizeof(display_text), length, '.');
                append_character(display_text, sizeof(display_text), length,
                                 static_cast<char>('0' + tenths % 10));
            }
        }
        break;
    }

    if (!value_available)
    {
        display_text[0] = '\0';
        length = 0;
        append_text(display_text, sizeof(display_text), length, bound_label);
        append_text(display_text, sizeof(display_text), length, ": N/A");
    }

    text = display_text;
}

void Text::render(PagePainter& painter)
{
    if (text == 0 || text[0] == '\0')
    {
        return;
    }

    if (width > 0 && font_size > 0)
    {
        painter.fill_rectangle(x, y, static_cast<uint16_t>(x + width - 1),
                               static_cast<uint16_t>(y + font_size - 1), background_color);
    }

    painter.draw_text(x, y, color, background_color, text, font_size, mode);
}
