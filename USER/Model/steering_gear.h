#ifndef STEERING_GEAR_H
#define STEERING_GEAR_H

#include "i_output_model.h"
#include "model_data.h"

class SteeringGear : public IOutputModel {
private:
	ModelData model_data{ModelType::STEERING_GEAR};
	void apply_enabled(bool enabled);

public:
	bool init() override;
	void accept(IVisitor* visitor, ModelDataMode mode) override;
	ModelData& get_model_data() override { return model_data; }
	void set_model_data(const ModelData& data) override;
};

#endif
