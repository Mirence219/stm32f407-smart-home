#ifndef FINGERPRINT_RECOGNITION_H
#define FINGERPRINT_RECOGNITION_H

#include <stdint.h>

#include "i_functional_model.h"
#include "model_data.h"

class FingerprintRecognition : public IFunctionalModel {
private:
	ModelData model_data{ModelType::FINGERPRINT_RECOGNITION};

public:
	bool init() override;
	void accept(IVisitor* visitor, ModelDataMode mode) override;
	ModelData& get_model_data() override { return model_data; }
	void set_model_data(const ModelData& data) override
	{
		if (data.get_model_type() == model_data.get_model_type())
		{
			model_data = data;
		}
	}
	void update() override;
};

#endif
