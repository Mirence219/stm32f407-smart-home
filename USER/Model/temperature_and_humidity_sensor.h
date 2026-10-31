#ifndef TEMPERATURE_AND_HUMIDITY_SENSOR_H
#define TEMPERATURE_AND_HUMIDITY_SENSOR_H

#include "stm32f4xx.h"
#include "i_input_model.h"
#include "model_data.h"

class TemperatureAndHumiditySensor : public IInputModel {
private:
	ModelData model_data{ModelType::TEMPERATURE_AND_HUMIDITY_SENSOR};
	GPIO_TypeDef* port;
	uint16_t pin;
	uint32_t last_sample_ms;

public:
	TemperatureAndHumiditySensor(GPIO_TypeDef* port, uint16_t pin);
	bool init() override;
	void accept(IVisitor* visitor, ModelDataMode mode) override;
	ModelData& get_model_data() override { return model_data; }
	void update() override;
};

#endif
