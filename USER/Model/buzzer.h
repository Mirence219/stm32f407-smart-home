#ifndef BUZZER_H
#define BUZZER_H

#include "stm32f4xx.h"
#include "i_output_model.h"
#include "model_data.h"

class Buzzer : public IOutputModel {
private:
	ModelData model_data{ModelType::BUZZER};
	GPIO_TypeDef *port;
	uint16_t pin;
	void apply_enabled(bool enabled);

public:
	Buzzer(GPIO_TypeDef *port, uint16_t pin);
	bool init() override;
	void accept(IVisitor* visitor, ModelDataMode mode) override;
	ModelData& get_model_data() override { return model_data; }
	void set_model_data(const ModelData& data) override;
};

#endif
