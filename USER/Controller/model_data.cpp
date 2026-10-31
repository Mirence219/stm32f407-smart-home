#include "model_data.h"
#include <string.h>

//数据名称与数据类型映射表
const ModelData::DataType ModelData::DATATYPEMAP[
    static_cast<uint8_t>(ModelData::DataName::TYPE_COUNT)] = {
        DataType::BOOL,  // ENABLE
        DataType::FLOAT, // ACCEL
        DataType::FLOAT, // GYRO
        DataType::BOOL,  // READY
        DataType::FLOAT, // SPEED
        DataType::INT,   // FINGER_ID
        DataType::BOOL,  // HAS_FINGER
        DataType::INT,   // CMD_ID
        DataType::BOOL,  // STATE
        DataType::FLOAT, // LIGHT_INTENSITY
        DataType::FLOAT, // PRESSURE
        DataType::FLOAT, // DISTANCE
        DataType::BOOL,  // HAS_CARD
        DataType::BYTES, // CARD_ID
        DataType::BOOL,  // RESERVE
        DataType::FLOAT, // TEMPERATURE
        DataType::FLOAT, // HUMIDITY
        DataType::BYTES, // RECV_BUF
        DataType::INT,   // RECV_LEN
        DataType::INT,   // RSSI
        DataType::BOOL,  // CONNECTED
        DataType::BOOL   // ATTACHED
    };

//模型类型与数据名称映射表
const ModelData::DataName ModelData::MODELFIELDMAP[
    static_cast<uint8_t>(ModelType::TYPE_COUNT)][ModelData::MAX_DATA_COUNT] = {
        {DataName::ATTACHED, DataName::ENABLE, DataName::READY, DataName::UNDEFINED,
         DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED}, // BUTTON0
        {DataName::ATTACHED, DataName::ENABLE, DataName::READY, DataName::UNDEFINED,
         DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED}, // BUTTON1
        {DataName::ATTACHED, DataName::ENABLE, DataName::READY, DataName::UNDEFINED,
         DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED}, // BUTTON2
        {DataName::ATTACHED, DataName::ENABLE, DataName::READY, DataName::UNDEFINED,
         DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED}, // BUTTON3
        {DataName::ATTACHED, DataName::ENABLE, DataName::READY, DataName::UNDEFINED,
         DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED}, // BUZZER
        {DataName::ATTACHED, DataName::ENABLE, DataName::READY, DataName::UNDEFINED,
         DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED}, // LED0
        {DataName::ATTACHED, DataName::ENABLE, DataName::READY, DataName::UNDEFINED,
         DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED}, // LED1
        {DataName::ATTACHED, DataName::ENABLE, DataName::READY, DataName::UNDEFINED,
         DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED}, // LED2
        {DataName::ATTACHED, DataName::ENABLE, DataName::READY, DataName::UNDEFINED,
         DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED}, // LED3
        {DataName::ATTACHED, DataName::ACCEL, DataName::GYRO, DataName::READY,
         DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED}, // ATTITUDE_SENSOR
        {DataName::ATTACHED, DataName::ENABLE, DataName::SPEED, DataName::READY,
         DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED}, // FAN
        {DataName::ATTACHED, DataName::ENABLE, DataName::FINGER_ID, DataName::HAS_FINGER,
         DataName::READY, DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED}, // FINGERPRINT_RECOGNITION
        {DataName::ATTACHED, DataName::ENABLE, DataName::CMD_ID, DataName::READY,
         DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED}, // INTELLIGENT_VOICE
        {DataName::ATTACHED, DataName::STATE, DataName::READY, DataName::UNDEFINED,
         DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED}, // LCD
        {DataName::ATTACHED, DataName::LIGHT_INTENSITY, DataName::READY, DataName::UNDEFINED,
         DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED}, // LIGHT_SENSOR
        {DataName::ATTACHED, DataName::PRESSURE, DataName::READY, DataName::UNDEFINED,
         DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED}, // PRESSURE_SENSOR
        {DataName::ATTACHED, DataName::ENABLE, DataName::READY, DataName::UNDEFINED,
         DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED}, // RFBLED
        {DataName::ATTACHED, DataName::ENABLE, DataName::CARD_ID, DataName::HAS_CARD,
         DataName::READY, DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED}, // RFID
        {DataName::ATTACHED, DataName::ENABLE, DataName::READY, DataName::UNDEFINED,
         DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED}, // SMART_DOOR_LOCK
        {DataName::ATTACHED, DataName::ENABLE, DataName::RESERVE, DataName::READY,
         DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED}, // STEERING_GEAR
        {DataName::ATTACHED, DataName::TEMPERATURE, DataName::HUMIDITY, DataName::READY,
         DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED}, // TEMPERATURE_AND_HUMIDITY_SENSOR
        {DataName::ATTACHED, DataName::DISTANCE, DataName::READY, DataName::UNDEFINED,
         DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED, DataName::UNDEFINED}, // ULTRASONIC_SENSOR
        {DataName::ATTACHED, DataName::ENABLE, DataName::RECV_BUF, DataName::RECV_LEN,
         DataName::RSSI, DataName::CONNECTED, DataName::READY, DataName::UNDEFINED} // WIFI
    };

ModelData::ModelData()
    : model_type(ModelType::UNDEFINED), name_list(), value_list(),
      byte_name(DataName::UNDEFINED), byte_value(), byte_length(0)
{
    for (uint8_t i = 0; i < MAX_DATA_COUNT; ++i)
    {
        name_list[i] = DataName::UNDEFINED;
    }
}

ModelData::ModelData(ModelType model_type)
    : model_type(model_type), name_list(), value_list(),
      byte_name(DataName::UNDEFINED), byte_value(), byte_length(0)
{
    for (uint8_t i = 0; i < MAX_DATA_COUNT; ++i)
    {
        name_list[i] = DataName::UNDEFINED;
    }

    const uint8_t model_index = static_cast<uint8_t>(model_type);
    if (model_index >= static_cast<uint8_t>(ModelType::TYPE_COUNT))
    {
        this->model_type = ModelType::UNDEFINED;
        return;
    }

    for (uint8_t i = 0; i < MAX_DATA_COUNT; ++i)
    {
        const DataName name = MODELFIELDMAP[model_index][i];
        if (name == DataName::UNDEFINED)
        {
            break;
        }
        name_list[i] = name;

        switch (DATATYPEMAP[static_cast<uint8_t>(name)])
        {
        case DataType::INT:
            value_list[i].u32 = 0;
            break;
        case DataType::BOOL:
            value_list[i].b = false;
            break;
        case DataType::FLOAT:
            value_list[i].f = 0.0f;
            break;
        case DataType::BYTES:
            break;
        }
    }
}

ModelType ModelData::get_model_type() const
{
    return model_type;
}

bool ModelData::find_data_index(DataName name, uint8_t& index) const
{
    const uint8_t name_index = static_cast<uint8_t>(name);
    if (name_index >= static_cast<uint8_t>(DataName::TYPE_COUNT))
    {
        return false;
    }

    for (uint8_t i = 0; i < MAX_DATA_COUNT; ++i)
    {
        if (name_list[i] == name)
        {
            index = i;
            return true;
        }
    }

    return false;
}

void ModelData::mark_ready()
{
    uint8_t ready_index;
    if (find_data_index(DataName::READY, ready_index))
    {
        value_list[ready_index].b = true;
    }
}

bool ModelData::set(DataName name, uint32_t val)
{
    uint8_t index;
    if (!find_data_index(name, index) ||
        DATATYPEMAP[static_cast<uint8_t>(name)] != DataType::INT)
    {
        return false;
    }

    if (value_list[index].u32 != val)
    {
        value_list[index].u32 = val;
        if (name != DataName::READY && name != DataName::ATTACHED)
        {
            mark_ready();
        }
    }
    return true;
}

bool ModelData::set(DataName name, bool val)
{
    uint8_t index;
    if (!find_data_index(name, index) ||
        DATATYPEMAP[static_cast<uint8_t>(name)] != DataType::BOOL)
    {
        return false;
    }

    if (value_list[index].b != val)
    {
        value_list[index].b = val;
        if (name != DataName::READY && name != DataName::ATTACHED)
        {
            mark_ready();
        }
    }
    return true;
}

bool ModelData::set(DataName name, float val)
{
    uint8_t index;
    if (!find_data_index(name, index) ||
        DATATYPEMAP[static_cast<uint8_t>(name)] != DataType::FLOAT)
    {
        return false;
    }

    if (value_list[index].f != val)
    {
        value_list[index].f = val;
        if (name != DataName::READY && name != DataName::ATTACHED)
        {
            mark_ready();
        }
    }
    return true;
}

bool ModelData::set_bytes(DataName name, const uint8_t *data, uint8_t length)
{
    uint8_t index;
    if (!find_data_index(name, index) ||
        DATATYPEMAP[static_cast<uint8_t>(name)] != DataType::BYTES ||
        data == 0 || length > MAX_BYTE_COUNT)
    {
        return false;
    }

    if (byte_name != DataName::UNDEFINED && byte_name != name)
    {
        return false;
    }

    const bool changed = byte_name != name || byte_length != length ||
                         memcmp(byte_value, data, length) != 0;
    memset(byte_value, 0, MAX_BYTE_COUNT);
    memcpy(byte_value, data, length);
    byte_name = name;
    byte_length = length;
    if (changed)
    {
        mark_ready();
    }
    return true;
}

bool ModelData::get(DataName name, uint32_t& out) const
{
    uint8_t index;
    if (!find_data_index(name, index) ||
        DATATYPEMAP[static_cast<uint8_t>(name)] != DataType::INT)
    {
        return false;
    }

    out = value_list[index].u32;
    return true;
}

bool ModelData::get(DataName name, bool& out) const
{
    uint8_t index;
    if (!find_data_index(name, index) ||
        DATATYPEMAP[static_cast<uint8_t>(name)] != DataType::BOOL)
    {
        return false;
    }

    out = value_list[index].b;
    return true;
}

bool ModelData::get(DataName name, float& out) const
{
    uint8_t index;
    if (!find_data_index(name, index) ||
        DATATYPEMAP[static_cast<uint8_t>(name)] != DataType::FLOAT)
    {
        return false;
    }

    out = value_list[index].f;
    return true;
}

const uint8_t *ModelData::get_bytes(DataName name, uint8_t& length) const
{
    uint8_t index;
    if (!find_data_index(name, index) ||
        DATATYPEMAP[static_cast<uint8_t>(name)] != DataType::BYTES)
    {
        length = 0;
        return 0;
    }

    if (byte_name != name)
    {
        length = 0;
        return byte_value;
    }

    length = byte_length;
    return byte_value;
}