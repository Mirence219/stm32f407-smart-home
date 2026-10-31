#ifndef TEXT_H
#define TEXT_H

#include "widget.h"
#include "model_data.h"

class ModelSnapShot;

enum class TextDataFormat : uint8_t {
    BOOL,
    UINT32,
    FLOAT
};

class Text : public Widget {
private:
    uint16_t rendered_background_color = 0;
    uint8_t rendered_font_size = 0;
    uint8_t rendered_mode = 0;
    ModelType bound_model_type = ModelType::UNDEFINED;
    ModelData::DataName bound_data_name = ModelData::DataName::UNDEFINED;
    TextDataFormat bound_data_format = TextDataFormat::BOOL;
    const char* bound_label = 0;
    char display_text[48] = {};
    bool data_bound = false;

protected:
    bool has_style_changed(const PagePainter& painter) const override;
    void save_style_state(const PagePainter& painter) override;

public:
    uint16_t background_color = 0;
    uint8_t font_size = 16;
    uint8_t mode = 0;

public:
    void bind_model_data(ModelType model_type, ModelData::DataName data_name,
                         TextDataFormat format, const char* label);
    void update_model_data(const ModelSnapShot* model_snap_shot);
protected:
    void render(PagePainter& painter) override;
};

#endif
