#ifndef PRESSURE_SENSOR_H
#define PRESSURE_SENSOR_H

#include "i_input_model.h"
#include "model_data.h"

class PressureSensor : public IInputModel {
private:
	ModelData model_data{ModelType::PRESSURE_SENSOR};

public:
	bool init() override;
	void accept(IVisitor* visitor, ModelDataMode mode) override;
	ModelData& get_model_data() override { return model_data; }
	void update() override;
};

#endif
