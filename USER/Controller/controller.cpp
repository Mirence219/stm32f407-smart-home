#include "controller.h"

Controller::Controller(ModelManager* model_manager)
    : model_visitor(model_manager, &model_snap_shot)
{
}

void Controller::read_model_data()
{
    model_visitor.read_model_data();
}

void Controller::write_model_data()
{
    model_visitor.write_model_data();
}

void Controller::update_models()
{
    model_visitor.update_models();
}

ModelSnapShot* Controller::get_model_snap_shot()
{
    return &model_snap_shot;
}

GuiState* Controller::get_gui_state()
{
    return &gui_state;
}

//全局核心业务！
void Controller::execute_logic()
{
    button_logic();

    ModelData fan_data = model_snap_shot.get(ModelType::FAN);
    uint8_t fan_level = gui_state.get_fan_level();
    if (gui_state.get_auto_cooling_enabled())
    {
        ModelData sensor_data = model_snap_shot.get(ModelType::TEMPERATURE_AND_HUMIDITY_SENSOR);
        bool attached = false;
        float temperature = 0.0f;
        if (sensor_data.get(ModelData::DataName::ATTACHED, attached) && attached &&
            sensor_data.get(ModelData::DataName::TEMPERATURE, temperature))
        {
            if (temperature >= 32.0f)
            {
                fan_level = 3;
            }
            else if (temperature >= 30.0f)
            {
                fan_level = 2;
            }
            else if (temperature >= 28.0f)
            {
                fan_level = 1;
            }
            else
            {
                fan_level = 0;
            }
        }
        else
        {
            fan_level = 0;
        }
    }
    fan_data.set(ModelData::DataName::ENABLE, fan_level != 0);
    fan_data.set(ModelData::DataName::SPEED, static_cast<float>(fan_level));
    model_snap_shot.update(fan_data);

    ModelData Lock_data = model_snap_shot.get(ModelType::SMART_DOOR_LOCK);
    Lock_data.set(ModelData::DataName::ENABLE, gui_state.get_lock_enabled());
    model_snap_shot.update(Lock_data);

    float light_intensity = 0.0f;
    bool light_attached = false;
    ModelData light_sensor_data = model_snap_shot.get(ModelType::LIGHT_SENSOR);
    const bool has_light_value =
        light_sensor_data.get(ModelData::DataName::ATTACHED, light_attached) &&
        light_attached &&
        light_sensor_data.get(ModelData::DataName::LIGHT_INTENSITY, light_intensity);

    for (uint8_t i = 0; i < 4; ++i)
    {
        bool enabled = gui_state.get_led_enabled(i);
        if (gui_state.get_auto_lighting_enabled() && has_light_value)
        {
            static const float LIGHT_THRESHOLDS[4] = {800.0f, 400.0f, 150.0f, 50.0f};
            enabled = light_intensity < LIGHT_THRESHOLDS[i];
        }
        else if (gui_state.get_auto_lighting_enabled())
        {
            enabled = false;
        }

        ModelData led_data = model_snap_shot.get(
            static_cast<ModelType>(static_cast<uint8_t>(ModelType::LED0) + i));
        led_data.set(ModelData::DataName::ENABLE, enabled);
        model_snap_shot.update(led_data);
    }
}

//按钮检测松开
bool Controller::check_button_enabled(ModelType button_type)
{
    ModelData button_data = model_snap_shot.get(button_type);
    bool button_ready = false;
    bool button_enabled = false;
    if (!button_data.get(ModelData::DataName::READY, button_ready) ||
        !button_ready ||
        !button_data.get(ModelData::DataName::ENABLE, button_enabled))
    {
        return false;
    }

    if (!button_data.set(ModelData::DataName::READY, false) ||
        !model_snap_shot.update(button_data))
    {
        return false;
    }

    return !button_enabled;
}

//按钮输入逻辑
void Controller::button_logic()
{
    if (check_button_enabled(ModelType::BUTTON0))
    {
        gui_state.handle_input_signal(GuiInputSignal::HOME);
    }
    else if (check_button_enabled(ModelType::BUTTON1))
    {
        gui_state.handle_input_signal(GuiInputSignal::TAB);
    }
    else if (check_button_enabled(ModelType::BUTTON2))
    {
        gui_state.handle_input_signal(GuiInputSignal::BACK);
    }
    else if (check_button_enabled(ModelType::BUTTON3))
    {
        gui_state.handle_input_signal(GuiInputSignal::SELECT);
    }
}