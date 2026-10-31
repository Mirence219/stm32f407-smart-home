#ifndef MODEL_LED_H
#define MODEL_LED_H

#include "led_gpio.h"
#include "i_output_model.h"
#include "model_data.h"

class Led : public IOutputModel {
private:
	ModelData model_data;
	GPIO_TypeDef* port;
	uint16_t pin;
	void write_output(bool enabled);

public:
	Led(ModelType model_type, GPIO_TypeDef* port, uint16_t pin);
	bool init() override;
	void accept(IVisitor* visitor, ModelDataMode mode) override;
	ModelData& get_model_data() override { return model_data; }
	void set_model_data(const ModelData& data) override;
};

#endif
