#include "model.h"
#include "Timer.h"

bool Model::init()
{
    Timer_Init(999, 83);
    IModel* all_models[] = {
        &button0,
        &button1,
        &button2,
        &button3,
        &attitude_sensor,
        &fingerprint_recognition,
        &intelligent_voice,
        &light_sensor,
        &pressure_sensor,
        &rfid,
        &temperature_and_humidity_sensor,
        &ultrasonic_sensor,
        &wifi,
        &buzzer,
        &led0,
        &led1,
        &led2,
        &led3,
        &fan,
        &lcd,
        &rfbled,
        &smart_door_lock,
        &steering_gear
    };

    const uint8_t all_model_count = sizeof(all_models) / sizeof(all_models[0]);
    for (uint8_t i = 0; i < all_model_count; ++i)
    {
        if (!all_models[i]->init())
        {
            continue;
        }

        if (!all_models[i]->get_model_data().set(ModelData::DataName::ATTACHED, true))
        {
            return false;
        }

        if (!model_manager.add_model(all_models[i]))
        {
            return false;
        }
    }

    return true;
}

ModelManager* Model::get_model_manager()
{
    return &model_manager;
}

Lcd* Model::get_lcd()
{
    return &lcd;
}

Wifi* Model::get_wifi()
{
    return &wifi;
}