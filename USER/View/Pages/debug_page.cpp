#include "debug_page.h"
#include "ili9486.h"

namespace {
struct InputFieldDescription {
    ModelType model_type;
    ModelData::DataName data_name;
    TextDataFormat format;
    const char* label;
};

const InputFieldDescription INPUT_FIELDS[] = {
    {ModelType::BUTTON0, ModelData::DataName::ENABLE, TextDataFormat::BOOL, "B0 PRESSED"},
    {ModelType::BUTTON1, ModelData::DataName::ENABLE, TextDataFormat::BOOL, "B1 PRESSED"},
    {ModelType::BUTTON2, ModelData::DataName::ENABLE, TextDataFormat::BOOL, "B2 PRESSED"},
    {ModelType::BUTTON3, ModelData::DataName::ENABLE, TextDataFormat::BOOL, "B3 PRESSED"},
    {ModelType::ATTITUDE_SENSOR, ModelData::DataName::ATTACHED, TextDataFormat::BOOL, "IMU ATTACHED"},
    {ModelType::ATTITUDE_SENSOR, ModelData::DataName::ACCEL, TextDataFormat::FLOAT, "IMU ACCEL"},
    {ModelType::ATTITUDE_SENSOR, ModelData::DataName::GYRO, TextDataFormat::FLOAT, "IMU GYRO"},
    //{ModelType::ATTITUDE_SENSOR, ModelData::DataName::READY, TextDataFormat::BOOL, "IMU READY"},
    {ModelType::LIGHT_SENSOR, ModelData::DataName::ATTACHED, TextDataFormat::BOOL, "LIGHT ATTACHED"},
    {ModelType::LIGHT_SENSOR, ModelData::DataName::LIGHT_INTENSITY, TextDataFormat::FLOAT, "LIGHT VALUE"},
    //{ModelType::LIGHT_SENSOR, ModelData::DataName::READY, TextDataFormat::BOOL, "LIGHT READY"},
    {ModelType::PRESSURE_SENSOR, ModelData::DataName::ATTACHED, TextDataFormat::BOOL, "PRESS ATTACHED"},
    {ModelType::PRESSURE_SENSOR, ModelData::DataName::PRESSURE, TextDataFormat::FLOAT, "PRESS VALUE"},
    //{ModelType::PRESSURE_SENSOR, ModelData::DataName::READY, TextDataFormat::BOOL, "PRESS READY"},
    {ModelType::TEMPERATURE_AND_HUMIDITY_SENSOR, ModelData::DataName::ATTACHED, TextDataFormat::BOOL, "TH ATTACHED"},
    {ModelType::TEMPERATURE_AND_HUMIDITY_SENSOR, ModelData::DataName::TEMPERATURE, TextDataFormat::FLOAT, "TEMP"},
    {ModelType::TEMPERATURE_AND_HUMIDITY_SENSOR, ModelData::DataName::HUMIDITY, TextDataFormat::FLOAT, "HUMIDITY"},
    //{ModelType::TEMPERATURE_AND_HUMIDITY_SENSOR, ModelData::DataName::READY, TextDataFormat::BOOL, "TH READY"},
    {ModelType::ULTRASONIC_SENSOR, ModelData::DataName::ATTACHED, TextDataFormat::BOOL, "US ATTACHED"},
    {ModelType::ULTRASONIC_SENSOR, ModelData::DataName::DISTANCE, TextDataFormat::BOOL, "DISTANCE"},
    //{ModelType::ULTRASONIC_SENSOR, ModelData::DataName::READY, TextDataFormat::BOOL, "US READY"},
    {ModelType::FAN, ModelData::DataName::ATTACHED, TextDataFormat::FLOAT, "FAN ATTECHED"},
    {ModelType::SMART_DOOR_LOCK, ModelData::DataName::ATTACHED, TextDataFormat::BOOL, "LOCK ATTECHED"},
    //{ModelType::STEERING_GEAR, ModelData::DataName::ATTACHED, TextDataFormat::BOOL, "SG ATTECHED"},
};
}

void DebugPage::init(ModelSnapShot* model_snap_shot)
{
    set_max_index(0);

    bg.color = WIDGET_COLOR_BLACK;
    add_widget(&bg);

    title.x = 8;
    title.y = 4;
    title.color = WIDGET_COLOR_YELLOW;
    title.background_color = WIDGET_COLOR_BLACK;
    title.font_size = 12;
    title.mode = 1;
    title.text = "INPUT MODEL SNAPSHOT";
    add_widget(&title);

    for (uint8_t i = 0; i < INPUT_FIELD_COUNT; ++i)
    {
        Text& field = input_fields[i];
        field.x = 8;
        field.y = static_cast<uint16_t>(22 + i * 18);
        field.width = 304;
        field.color = WIDGET_COLOR_WHITE;
        field.background_color = WIDGET_COLOR_BLACK;
        field.font_size = 12;
        field.mode = 0;
        field.bind_model_data(INPUT_FIELDS[i].model_type,
                              INPUT_FIELDS[i].data_name,
                              INPUT_FIELDS[i].format,
                              INPUT_FIELDS[i].label);
        add_widget(&field);
    }

    update(model_snap_shot);
}

void DebugPage::update(ModelSnapShot* model_snap_shot)
{
    for (uint8_t i = 0; i < INPUT_FIELD_COUNT; ++i)
    {
        input_fields[i].update_model_data(model_snap_shot);
    }
}
