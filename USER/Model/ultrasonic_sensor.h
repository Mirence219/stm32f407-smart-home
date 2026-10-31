#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include "i_input_model.h"
#include "model_data.h"

class UltrasonicSensor : public IInputModel {
private:
	ModelData model_data{ModelType::ULTRASONIC_SENSOR};

public:
	bool init() override;
	void accept(IVisitor* visitor, ModelDataMode mode) override;
	ModelData& get_model_data() override { return model_data; }
	void update() override;
};

#endif
