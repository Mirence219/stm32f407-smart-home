#ifndef MODEL_DATA_H
#define MODEL_DATA_H

#include <stdint.h>

enum class ModelType: uint8_t{
        BUTTON0,
        BUTTON1,
        BUTTON2,
        BUTTON3,
        BUZZER,
        LED0,
        LED1,
        LED2,
        LED3,
        ATTITUDE_SENSOR,
        FAN,
        FINGERPRINT_RECOGNITION,
        INTELLIGENT_VOICE,
        LCD,
        LIGHT_SENSOR,
        PRESSURE_SENSOR,
        RFBLED,
        RFID,
        SMART_DOOR_LOCK,
        STEERING_GEAR,
        TEMPERATURE_AND_HUMIDITY_SENSOR,
        ULTRASONIC_SENSOR,
        WIFI,
        TYPE_COUNT,
        UNDEFINED
};

class ModelData
{
public:
    enum class DataName: uint8_t {
        ENABLE,
        ACCEL,
        GYRO,
        READY,
        SPEED,
        FINGER_ID,
        HAS_FINGER,
        CMD_ID,
        STATE,
        LIGHT_INTENSITY,
        PRESSURE,
        DISTANCE,
        HAS_CARD,
        CARD_ID,
        RESERVE,
        TEMPERATURE,
        HUMIDITY,
        RECV_BUF,
        RECV_LEN,
        RSSI,
        CONNECTED,
        ATTACHED,
        TYPE_COUNT,
        UNDEFINED
    };

private:
    enum class DataType: uint8_t {
        INT,
        BOOL,
        FLOAT,
        BYTES
    };

    static constexpr uint8_t MAX_DATA_COUNT = 8;
    static constexpr uint8_t MAX_BYTE_COUNT = 64;
    static const DataType DATATYPEMAP[static_cast<uint8_t>(DataName::TYPE_COUNT)];
    static const DataName MODELFIELDMAP[static_cast<uint8_t>(ModelType::TYPE_COUNT)][MAX_DATA_COUNT];

    union DataValue
    {
        uint32_t u32;
        bool b;
        float f;
    };
    ModelType model_type;
    DataName name_list[MAX_DATA_COUNT];
    DataValue value_list[MAX_DATA_COUNT];
    DataName byte_name;
    uint8_t byte_value[MAX_BYTE_COUNT];
    uint8_t byte_length;

    bool find_data_index(DataName name, uint8_t& index) const;
    void mark_ready();

public:
    ModelData();
    ModelData(ModelType model_type);
    ModelType get_model_type() const;
    bool set(DataName name, uint32_t val);
    bool set(DataName name, bool val);
    bool set(DataName name, float val);
    bool set_bytes(DataName name, const uint8_t *data, uint8_t length);
    bool get(DataName name, uint32_t& out) const;
    bool get(DataName name, bool& out) const;
    bool get(DataName name, float& out) const;
    const uint8_t *get_bytes(DataName name, uint8_t& length) const;
};

#endif
