#include "lcd.h"
#include "gui.h"

bool Lcd::init()
{
    LCD_Init();
	model_data.set(ModelData::DataName::STATE, true);
	return true;
}

void Lcd::accept(IVisitor* visitor, ModelDataMode mode)
{
	visitor->visit(static_cast<IOutputModel*>(this), mode);
}


void Lcd::run()
{
}

void Lcd::close()
{
	GUI_Fill(0, 0, LCD_W - 1, LCD_H - 1, BLACK);
	model_data.set(ModelData::DataName::STATE, false);
}

void Lcd::set_model_data(const ModelData& data)
{
	if (data.get_model_type() != model_data.get_model_type())
	{
		return;
	}

	bool old_enabled = false;
	bool new_enabled = false;
	model_data.get(ModelData::DataName::STATE, old_enabled);
	data.get(ModelData::DataName::STATE, new_enabled);
	model_data = data;
	if (old_enabled != new_enabled)
	{
		apply_enabled(new_enabled);
	}
}

void Lcd::apply_enabled(bool enabled)
{
	if (enabled)
	{
		LCD_Init();
	}
	else
	{
		GUI_Fill(0, 0, LCD_W - 1, LCD_H - 1, BLACK);
	}
}

void Lcd::clear(uint16_t color)
{
	GUI_Fill(0, 0, LCD_W - 1, LCD_H - 1, color);
}

void Lcd::draw_point(uint16_t x, uint16_t y, uint16_t color)
{
	GUI_Draw_Point(x, y, color);
}

void Lcd::fill(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y, uint16_t color)
{
	GUI_Fill(start_x, start_y, end_x, end_y, color);
}

void Lcd::draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	GUI_Draw_Line(x1, y1, x2, y2, color);
}

void Lcd::draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	GUI_Draw_Rectangle(x1, y1, x2, y2, color);
}

void Lcd::fill_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	GUI_Draw_Fill_Rectangle(x1, y1, x2, y2, color);
}

void Lcd::draw_circle(int center_x, int center_y, uint16_t color, uint16_t radius, bool filled)
{
	GUI_Circle(center_x, center_y, color, radius, filled ? 1 : 0);
}

void Lcd::show_english_char(uint16_t x, uint16_t y, uint16_t foreground, uint16_t background,
                            uint8_t character, uint8_t size, uint8_t mode)
{
	GUI_Show_English_Char(x, y, foreground, background, character, size, mode);
}

void Lcd::show_int(uint16_t x, uint16_t y, uint16_t foreground, uint16_t background,
                   int32_t value, uint8_t length, uint8_t size, uint8_t mode)
{
	GUI_Show_Int_Num(x, y, foreground, background, value, length, size, mode);
}

void Lcd::show_chinese(uint16_t x, uint16_t y, uint16_t foreground, uint16_t background,
                       const char *text, uint8_t size, uint8_t mode)
{
	GUI_Show_Chinese_Char(x, y, foreground, background, text, size, mode);
}

void Lcd::show_string(uint16_t x, uint16_t y, uint16_t foreground, uint16_t background,
                      const char *text, uint8_t size, uint8_t mode)
{
	GUI_Show_Str(x, y, foreground, background, text, size, mode);
}

void Lcd::show_string_centered(uint16_t x, uint16_t y, uint16_t foreground, uint16_t background,
                               const char *text, uint8_t size, uint8_t mode)
{
	GUI_Str_Center(x, y, foreground, background, text, size, mode);
}

void Lcd::draw_bitmap(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t *pixels)
{
	GUI_Drawbmp16(x, y, width, height, pixels);
}

void Lcd::draw_bitmap_zoomed(int16_t x, int16_t y, const uint8_t *pixels,
                             uint16_t source_width, uint16_t source_height,
                             uint16_t width, uint16_t height)
{
	Gui_Drawbmp_Zoom(x, y, pixels, source_width, source_height, width, height);
}
