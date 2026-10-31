#ifndef USER_MODEL_LCD_H
#define USER_MODEL_LCD_H

#include <stdint.h>

#include "i_output_model.h"
#include "model_data.h"

class Lcd : public IOutputModel {
private:
	ModelData model_data{ModelType::LCD};
	void apply_enabled(bool enabled);

public:
	bool init() override;
	void accept(IVisitor* visitor, ModelDataMode mode) override;
	ModelData& get_model_data() override { return model_data; }
	void set_model_data(const ModelData& data) override;
	void run();
	void close();

	void clear(uint16_t color);
	void draw_point(uint16_t x, uint16_t y, uint16_t color);
	void fill(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y, uint16_t color);
	void draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
	void draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
	void fill_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
	void draw_circle(int center_x, int center_y, uint16_t color, uint16_t radius, bool filled);
	void show_english_char(uint16_t x, uint16_t y, uint16_t foreground, uint16_t background,
	                       uint8_t character, uint8_t size, uint8_t mode);
	void show_int(uint16_t x, uint16_t y, uint16_t foreground, uint16_t background,
	              int32_t value, uint8_t length, uint8_t size, uint8_t mode);
	void show_chinese(uint16_t x, uint16_t y, uint16_t foreground, uint16_t background,
	                  const char *text, uint8_t size, uint8_t mode);
	void show_string(uint16_t x, uint16_t y, uint16_t foreground, uint16_t background,
	                 const char *text, uint8_t size, uint8_t mode);
	void show_string_centered(uint16_t x, uint16_t y, uint16_t foreground, uint16_t background,
	                          const char *text, uint8_t size, uint8_t mode);
	void draw_bitmap(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t *pixels);
	void draw_bitmap_zoomed(int16_t x, int16_t y, const uint8_t *pixels,
	                        uint16_t source_width, uint16_t source_height,
	                        uint16_t width, uint16_t height);
};

#endif
