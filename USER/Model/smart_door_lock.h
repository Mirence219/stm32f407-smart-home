#ifndef SMART_DOOR_LOCK_H
#define SMART_DOOR_LOCK_H

#include "stm32f4xx.h"
#include "i_output_model.h"
#include "model_data.h"

class SmartDoorLock : public IOutputModel {
private:
	ModelData model_data{ModelType::SMART_DOOR_LOCK};
	GPIO_TypeDef *port;
	uint16_t pin;
	void apply_enabled(bool enabled);

public:
	SmartDoorLock(GPIO_TypeDef *port, uint16_t pin);
	bool init() override;
	void accept(IVisitor* visitor, ModelDataMode mode) override;
	ModelData& get_model_data() override { return model_data; }
	void set_model_data(const ModelData& data) override;
};

#endif
