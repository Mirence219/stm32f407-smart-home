#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>
#include "i_functional_model.h"
#include "key.h"
#include "model_data.h"

class Button : public IFunctionalModel {
private:
	ModelData model_data;
	GPIO_TypeDef* port;
	uint16_t pin;
	uint8_t active_level;
	uint8_t last_raw_state;
	bool initialized;
	void set_enabled(bool enabled);

public:
	Button(ModelType model_type, GPIO_TypeDef* port, uint16_t pin, uint8_t active_level);
	bool init() override;
	void accept(IVisitor* visitor, ModelDataMode mode) override;
	ModelData& get_model_data() override { return model_data; }
	void set_model_data(const ModelData& data) override;
	void update() override;
};

#endif
