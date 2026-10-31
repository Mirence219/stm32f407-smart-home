#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include "i_input_model.h"
#include "model_data.h"

class LightSensor : public IInputModel {
private:
	ModelData model_data{ModelType::LIGHT_SENSOR};
	uint32_t last_sample_ms = 0;

public:
	bool init() override;
	void accept(IVisitor* visitor, ModelDataMode mode) override;
	ModelData& get_model_data() override { return model_data; }
	void update() override;
};

#endif
