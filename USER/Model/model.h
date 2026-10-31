#ifndef MODEL_H
#define MODEL_H

#include "button.h"
#include "buzzer.h"
#include "led.h"
#include "attitude_sensor.h"
#include "fans.h"
#include "fingerprint_recognition.h"
#include "intelligent_voice.h"
#include "light_sensor.h"
#include "model_manager.h"
#include "lcd.h"
#include "pressure_sensor.h"
#include "rfbled.h"
#include "rfid.h"
#include "smart_door_lock.h"
#include "steering_gear.h"
#include "temperature_and_humidity_sensor.h"
#include "ultrasonic_sensor.h"
#include "wifi.h"

class Model {
private:
    ModelManager model_manager;
    Button button0{ModelType::BUTTON0, GPIOE, GPIO_Pin_4, Bit_RESET};
    Button button1{ModelType::BUTTON1, GPIOE, GPIO_Pin_3, Bit_RESET};
    Button button2{ModelType::BUTTON2, GPIOE, GPIO_Pin_2, Bit_RESET};
    Button button3{ModelType::BUTTON3, GPIOA, GPIO_Pin_0, Bit_SET};
    Buzzer buzzer{GPIOH, GPIO_Pin_7};
    Led led0{ModelType::LED0, GPIOF, GPIO_Pin_9};
    Led led1{ModelType::LED1, GPIOF, GPIO_Pin_10};
    Led led2{ModelType::LED2, GPIOH, GPIO_Pin_14};
    Led led3{ModelType::LED3, GPIOH, GPIO_Pin_15};
    AttitudeSensor attitude_sensor;
    Fan fan{GPIOA, GPIO_Pin_8};
    FingerprintRecognition fingerprint_recognition;
    IntelligentVoice intelligent_voice;
    Lcd lcd;
    LightSensor light_sensor;
    PressureSensor pressure_sensor;
    Rfbled rfbled;
    Rfid rfid;
    SmartDoorLock smart_door_lock{GPIOI, GPIO_Pin_2};
    SteeringGear steering_gear;
    TemperatureAndHumiditySensor temperature_and_humidity_sensor{GPIOA, GPIO_Pin_1};
    UltrasonicSensor ultrasonic_sensor;
    Wifi wifi;

public:
     bool init();
     ModelManager* get_model_manager();
     Lcd* get_lcd();
     Wifi* get_wifi();
};

#endif